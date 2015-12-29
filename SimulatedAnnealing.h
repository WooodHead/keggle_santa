
#ifndef KEGGLE_SANTA_SIMULATEDANNEALING_H
#define KEGGLE_SANTA_SIMULATEDANNEALING_H


#include "Solution.h"
#include "NNSearcher.h"
#include "RandomPointSelector.h"


class SwapMove{
public:


    RouteID route_from= -1;
    IntType from_pos = -1;

    RouteID route_to = -1;
    IntType to_pos = -1;

    GiftID p = -1;
};

class SimulatedAnnealing
{
public:
	SimulatedAnnealing(Solution &sol)
		: sol(sol),
			nnsearcher(sol.gl_gift_data)
	{
		gift_ids = GenerateIDvector(sol.gl_gift_data);
        rand_selector = new RandomPointSelector(&sol);
	}

	void work(){
        auto iter_cnt = 10000;
		auto iter_n = 0;
		while (iter_n<iter_cnt){

            auto move = neighbourhood_search();
            MakeMove(move);

			++iter_n;
		}
	}
private:
	nnsearch::NNSearcher nnsearcher;
	Solution& sol;
	RandomPointSelector* rand_selector;
	vector<GiftID> gift_ids;

    void MakeMove(SwapMove move){
        Route & p_r = sol.routes[move.route_from];
        Route & nn_r = sol.routes[move.route_to];

        GiftID p = p_r[move.from_pos];

        p_r.remove(move.from_pos);
        nn_r.insert(move.to_pos, p);
        p_r.BuildIndexes(sol.gift_add_info);
        nn_r.BuildIndexes(sol.gift_add_info);
    }


    SwapMove neighbourhood_search(){
        SwapMove res;
        FloatType max_diff = numeric_limits<FloatType>::min();

        auto g_ids = rand_selector->selectNPnts(gift_ids, 10);
        for(auto p: g_ids){
            auto p_route_id = sol.GetRouteID(p);

            auto nn_ids_all = nnsearcher.FindNN(p, 50);
            auto nn_ids  = rand_selector->selectNPnts(
                        nn_ids_all,
                        20);


            for(auto nn_p: nn_ids){
                auto nn_p_route_id=sol.GetRouteID(nn_p);


                Route & p_r = sol.routes[p_route_id];
                Route & nn_r = sol.routes[nn_p_route_id];

                auto p_r_idex = sol.gift_add_info[p].route_pos;
                auto nn_r_idex = sol.gift_add_info[nn_p].route_pos;

                if(nn_r_idex >= nn_r.size()){
                    auto k = 3;
                }

                auto new_weight = nn_r.Weight() + sol.GetGift(p).Weight();
                if(new_weight<=sleigh_weight_limit){

                auto remove_v = p_r.EstRemoveNode(p_r_idex);
                auto add_v = nn_r.EstAddNode(nn_r_idex, p);

                auto diff = remove_v - add_v;
                if(diff > max_diff ){

                    // kapacb
                    //res = {p_route_id, p_r_idex, nn_p_route_id, nn_r_idex, p};
                    max_diff = diff;

//                    p_r.remove(p_r_idex);
//                    nn_r.insert(nn_r_idex, p);
//                    p_r.BuildIndexes(sol.gift_add_info);
//                    nn_r.BuildIndexes(sol.gift_add_info);
                }
                }

            }
        }
       return res;
    }
};


#endif //KEGGLE_SANTA_SIMULATEDANNEALING_H
