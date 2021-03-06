//
// Created by alexey on 27.12.15.
//

#ifndef KEGGLE_SANTA_SOLUTION_H
#define KEGGLE_SANTA_SOLUTION_H

#include <functional>
#include <iostream>
#include <cassert>

#include "Gift.h"
#include "Route.h"


class Solution
{
public:
    Solution(const vector<Gift> &gl_gift_data);

    FloatType Distance(GiftID g1, GiftID g2){
        auto loc1 = gl_gift_data[g1].Loc();
        auto loc2 = gl_gift_data[g2].Loc();
        return Dist(loc1, loc2);
    }

    Route & GetRoute(RouteID route_id);

    RouteID GetRouteID(GiftID gift_id){
        return gift_to_route_index[gift_id];
    }
    const Gift & GetGift(GiftID gift_id){
        return this->gl_gift_data[gift_id];
    }

    RouteID BFGetRouteForGift(GiftID gift_id);

    GlobalGiftData Gifts() const;
    const vector<Route>& Routes()const;


	GlobalGiftData gl_gift_data;

	vector<Route> routes;
	vector<RouteID> gift_to_route_index;

    vector<GiftIndexData> gift_add_info;
};


using GenerateFuncType = std::function<vector<Route>(GlobalGiftData giftData)>;

FloatType evaluate_solution(const Solution & sol);

Solution StartingSolution(GlobalGiftData giftData, const vector<Route> & routes);
Solution StartingSolution(GlobalGiftData giftData, GenerateFuncType func);

void CompareSolutions(const Solution & sol1, const Solution & sol2);
//Solution StartingSolution(GlobalGiftData giftData);






#endif //KEGGLE_SANTA_SOLUTION_H
