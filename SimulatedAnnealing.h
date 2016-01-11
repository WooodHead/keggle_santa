
#ifndef KEGGLE_SANTA_SIMULATEDANNEALING_H
#define KEGGLE_SANTA_SIMULATEDANNEALING_H


#include "Solution.h"
#include "NNSearcher.h"
#include "RandomPointSelector.h"


class SwapMove{
public:
    SwapMove(RouteID route_from,
             IntType from_pos,
             RouteID route_to,
             IntType to_pos,
             GiftID p): route_from(route_from),
                        from_pos(from_pos),
                        route_to(route_to),
                        to_pos(to_pos),
                        p(p){}

    inline
    bool HasMove(){
        return (route_from >= 0)&&
                (from_pos >= 0)&&
                (route_to >= 0)&&
                (to_pos >= 0)&&
                (p >= 0);
    }

    RouteID route_from = -1;
    IntType from_pos = -1;

    RouteID route_to = -1;
    IntType to_pos = -1;

    GiftID p = -1;


    void MakeMove(Solution & sol){
        Route & p_r = sol.routes[this->route_from];
        Route & nn_r = sol.routes[this->route_to];

        GiftID p = p_r[this->from_pos];
        assert(p == this->p);

        p_r.remove(this->from_pos);
        nn_r.insert(this->to_pos, p);
        //p_r.BuildIndexes(sol.gift_add_info);
        //nn_r.BuildIndexes(sol.gift_add_info);

        sol.gift_to_route_index[p] = this->route_to;
    }
private:
};




//inline
//std::ostream &operator<<(std::ostream &os, SwapMove const &move) {
//    return os << move.to_string();
//}

class IterativeHeuristic{
protected:
    IterativeHeuristic(bool use_console): use_console(use_console){}

    bool use_console;
};

class SimulatedAnnealing: public IterativeHeuristic
{
public:
    using OnMoveFunc = function<void(const SwapMove& move)>;

    SimulatedAnnealing(Solution &sol, bool use_console = false);

    void SetOnMove(OnMoveFunc func){
        on_move = func;
    }

    string to_string(const SwapMove & move){
        stringstream ss;

        auto route_from = move.route_from;
        auto from_pos = move.from_pos;
        auto route_to = move.route_to;
        auto to_pos = move.to_pos;

        const Route& r_from = this->sol.Routes()[route_from];
        const Route& r_to = this->sol.Routes()[route_to];

        ss<<"move:"<<endl
          <<"   route from = "<<route_from<<" pos = "<<from_pos<<endl
          <<"   route to = "<<route_to<<" pos = "<<to_pos<<endl
          <<"       route from size = "<<r_from.size()<<endl
          <<"       route to size = "<<r_to.size()<<endl;

        return ss.str();
    }

    void work(int iter_cnt = 1000){
        //auto iter_cnt = 10000;
		auto iter_n = 0;
		while (iter_n<iter_cnt){

            auto move = neighbourhood_search();


            if(use_console){
                cout << "iter number = " << iter_n << endl;
                if (!move.HasMove())
                    cout << "no move!!!" << endl;
                else
                    cout << to_string(move) << endl;
            };
            if (move.HasMove()){
                MakeMove(move);
                if(on_move)
                    on_move(move);
            };

			++iter_n;
		}
	}
private:
	nnsearch::NNSearcher nnsearcher;
	Solution& sol;
	RandomPointSelector* rand_selector;
	vector<GiftID> gift_ids;

    OnMoveFunc on_move;

    void MakeMove(SwapMove move){
        move.MakeMove(sol);
    }


    SwapMove neighbourhood_search(){
        SwapMove res(-1,-1,-1,-1,-1);
        FloatType max_diff = numeric_limits<FloatType>::min();

//        #pragma ot
        auto g_ids = rand_selector->selectNPnts(gift_ids, 10);
        for(auto p: g_ids){
            auto p_route_id = sol.GetRouteID(p);

            auto nn_ids_all = nnsearcher.FindNN(p, 250);
            auto nn_ids  = rand_selector->selectNPnts(
                        nn_ids_all,
                        75);

            for(auto nn_p: nn_ids){
                auto nn_p_route_id=sol.GetRouteID(nn_p);
                if(p_route_id == nn_p_route_id)
                    continue;


                const Route & p_r = sol.routes[p_route_id];
                const Route & nn_r = sol.routes[nn_p_route_id];

                //auto p_r_idex = sol.gift_add_info[p].route_pos;
                //auto nn_r_idex = sol.gift_add_info[nn_p].route_pos;
                auto p_r_idex = p_r.GetGiftPos(p);
                auto nn_r_idex = nn_r.GetGiftPos(nn_p);
                //sol.BFGetRouteForGift(nn_p)

                if(nn_r_idex >= nn_r.size()){
                    auto k = 3;
                }

                auto new_weight = nn_r.Weight() + sol.GetGift(p).Weight();
                if(new_weight<=sleigh_weight_limit){

                auto remove_v = p_r.EstRemoveNode(p_r_idex);
                auto add_v = nn_r.EstAddNode(nn_r_idex, p);

                auto diff = remove_v - add_v;
                if(diff>0.0)
                if(diff > max_diff ){

                    // kapacb
                    res = SwapMove(                           p_route_id,
                            p_r_idex,
                            nn_p_route_id,
                            nn_r_idex,
                            p);
                    max_diff = diff;

                    }
                }

            }
        }
       return res;
    }
};


#endif //KEGGLE_SANTA_SIMULATEDANNEALING_H
