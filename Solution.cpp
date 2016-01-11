#include "Solution.h"



Solution StartingSolution(GlobalGiftData giftData, const vector<Route> & routes){
    Solution res(giftData);
    int route_id = 0;
    for (auto r: routes){
        res.routes.push_back(r);
        for (int i = 0; i < r.size(); ++i) {
            auto gift_id = r[i];
            res.gift_to_route_index[gift_id]=route_id;
            //res.gift_add_info[gift_id].route_pos = i;

        };
        r.BuildIndexes(res.gift_add_info);
        ++route_id;
    }
    return res;
}

Solution StartingSolution(GlobalGiftData giftData, GenerateFuncType func){
    auto routes =  func(giftData);
    return StartingSolution(giftData, routes);
}

//Solution StartingSolution(GlobalGiftData giftData){
//    Solution res(giftData);

//    for (int id = 0; id < giftData.size(); ++id) {
//        Route r(giftData);
//        r.add(id);
//        res.routes.push_back(r);

//        res.gift_to_route_index[id]=id;
//        res.gift_add_info[id].dist_from_start = giftData[id].Weight();
//        //res.gift_add_info[id].route_pos = 0;
//    };
//    r.BuildIndexes(res.gift_add_info);

//    return res;
//}

Solution::Solution(const vector<Gift> &gl_gift_data)
    : gl_gift_data(gl_gift_data),
      gift_to_route_index(gl_gift_data.size(), -1),
      gift_add_info(gl_gift_data.size())
{ }

Route &Solution::GetRoute(RouteID route_id){
    return this->routes[route_id];
}

RouteID Solution::BFGetRouteForGift(GiftID gift_id){
    auto i = 0;
    for(auto r: routes){
        if(r.BFContains(gift_id))
            return i;
        ++i;
    }
    return -1;
}

GlobalGiftData Solution::Gifts() const {return gl_gift_data;}

const vector<Route> &Solution::Routes() const {return routes;}

void CompareSolutions(const Solution & sol1, const Solution & sol2)
{
    assert(sol1.Routes().size() == sol2.Routes().size());
    for (int i = 0; i < sol1.Routes().size(); ++i) {
        const Route & r1 = sol1.Routes()[i];
        const Route & r2 = sol2.Routes()[i];

        assert(r1.size() == r2.size());

        for (int j = 0; j < r1.size(); ++j) {
            auto gift_id1 = r1[j];
            auto gift_id2 = r2[j];

            if(gift_id1!=gift_id2){
                cout << "route id = "<<i << " "
                     << "pos = "<< j << " "
                     << "gift_id1 =" << gift_id1 << " "
                     << "gift_id2 =" << gift_id2 << endl;
            }
        }
    }
}

FloatType evaluate_solution(const Solution &sol){
    return evaluate_solution(sol.Gifts(), sol.Routes());
}
