
#ifndef KEGGLE_SANTA_SIMULATEDANNEALING_H
#define KEGGLE_SANTA_SIMULATEDANNEALING_H


#include "Solution.h"
#include "NNSearcher.h"
#include "RandomPointSelector.h"

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
		auto iter_cnt = 500;
		auto iter_n = 0;
		while (iter_n<iter_cnt){

            neighbourhood_search();

			++iter_n;
		}
	}
private:
	nnsearch::NNSearcher nnsearcher;
	Solution& sol;
	RandomPointSelector* rand_selector;
	vector<GiftID> gift_ids;

	FloatType calcMove(GiftID g1, RouteID r1,
										 GiftID g2, RouteID r2){

	}

    void neighbourhood_search(){
        auto g_ids = rand_selector->selectNPnts(gift_ids, 20);

        for(auto p: g_ids){
            auto point_gift = sol.gl_gift_data[p];

            auto p_route_id = sol.gift_to_route_index[p];
            auto nn_ids = nnsearcher.FindNN(p, 200);
            for(auto nn_p: nn_ids){
                auto d = sol.Distance(p, nn_p);

                auto nn_p_route_id=sol.gift_to_route_index[nn_p];

                auto & p_r = sol.routes[p_route_id];
                auto & nn_r = sol.routes[nn_p_route_id];

                auto p_r_idex = sol.gift_add_info[p].route_pos;
                auto nn_r_idex = sol.gift_add_info[nn_p].route_pos;


                auto remove_v = p_r.EstRemoveNode(p_r_idex);
                auto add_v = nn_r.EstAddNode(nn_r_idex, p);
                if(add_v<remove_v){
                    bool b = 1;
                }
            }
        }

        //nnsearcher.FindNN()
    }
};


#endif //KEGGLE_SANTA_SIMULATEDANNEALING_H
