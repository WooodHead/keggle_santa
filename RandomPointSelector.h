//
// Created by alexey on 27.12.15.
//

#ifndef KEGGLE_SANTA_RANDOMPOINTSELECTOR_H
#define KEGGLE_SANTA_RANDOMPOINTSELECTOR_H

#include <vector>
#include <random>

#include "Gift.h"
#include "Solution.h"

using namespace std;

struct MoveData{
    RouteID from_route_id;
    IntType from_point_pos;

    RouteID to_route_id;
    IntType to_point_pos;
};

class RandomPointSelector{
public:
    RandomPointSelector(Solution* _sol)
	{
        sol = _sol;
		default_random_engine = std::default_random_engine(r_device());
	}

	inline
    vector<GiftID> selectNPnts(const vector<GiftID> & ids, IntType cnt){
		std::set<GiftID> res_set;
		for (int i = 0; i < cnt; ++i) {
            auto p = selectRandomPoint(ids);
			res_set.insert(p);
		}

		std::vector<GiftID> res(res_set.begin(), res_set.end());
		return res;
	}

	inline
    GiftID selectRandomPoint(const vector<GiftID> & ids){
		std::uniform_int_distribution<int> uniform_dist(
			0,
			ids.size()-1
		);
		int v = uniform_dist(default_random_engine);

		auto iter = ids.begin();
		std::advance(iter, v);

		return *iter;
	}



    MoveData RandomMove(){
        std::uniform_int_distribution<int> route_gen(
            0,
            sol->routes.size()-1
        );

        MoveData res;

        RouteID r1 = route_gen(default_random_engine);
        RouteID r2 = route_gen(default_random_engine);

        assert(r1 != r2);

        std::uniform_int_distribution<int> gift_gen1(
            0,
            sol->routes[r1].size()-1
        );
        int pos1 = gift_gen1(default_random_engine);

        std::uniform_int_distribution<int> gift_gen2(
            0,
            sol->routes[r2].size()-1
        );
        int pos2 = gift_gen2(default_random_engine);

        res.from_route_id = r1;
        res.from_point_pos = pos1;
        res.to_route_id = r2;
        res.to_point_pos = pos2;

        return res;
    }

private:
	std::random_device r_device;
	std::default_random_engine default_random_engine;

    Solution * sol;
    //vector<GiftID> ids;
};

#endif //KEGGLE_SANTA_RANDOMPOINTSELECTOR_H

