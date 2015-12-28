//
// Created by alexey on 26.12.15.
//

#include "Route.h"

FloatType evaluate_solution(GlobalGiftData g_data, const vector<Route> &routes){
    FloatType res = 0.0;
    for(const auto & r: routes){
        res += route_evaluation(g_data, r);
    }
    return res;
}

FloatType route_evaluation(GlobalGiftData g_data, const Route & r){
    FloatType res = 0.0;
    int test_counter = 0;

    FloatType w = sleigh_base_weight;
    for (int i = 0; i < r.size(); ++i) {
        const auto & gift = g_data[r[i]];
        w += gift.Weight();
        ++test_counter;
    }

    auto w_limit = sleigh_weight_limit + sleigh_base_weight;

    // weight > then limit
    assert(w <= w_limit);

    res += w*Dist(north_pole, g_data[r[0]].Loc() );

    test_counter = 0;
    int __size = r.size();
    for (int i = 0; i < __size-1; ++i) {
        const auto & gift = g_data[r[i]];
        const auto & gift_next = g_data[r[i+1]];

        w -= gift.Weight();

        res += w*Dist(gift.Loc(), gift_next.Loc());
        ++test_counter;
    }

    w = sleigh_base_weight;
    res += w*Dist(north_pole, g_data[r[r.size()-1]].Loc() );

    return res;
}

IntType GetGiftIDSCount(const vector<Route> &routes){
    IntType  cnt = 0;
    for(const auto & r: routes)
        for(const auto & g_id: r){
            ++cnt;
        }
    return cnt;
}

vector<GiftID> GetAllGiftIDS(const vector<Route> &routes){
    set<GiftID> res_set;
    for(const auto & r: routes)
        for(const auto & g_id: r)
            res_set.insert(g_id);

    vector<GiftID> res(res_set.begin(), res_set.end());

    return res;
}

void Route::add(GiftID gift_id){
    gift_ids.push_back(gift_id);
    weight += gift_data[gift_id].Weight();
}

void Route::add(std::initializer_list<GiftID> gift_id_il)
{
    for(auto id: gift_id_il)
        add(id);
}

void Route::insert(size_t pos, GiftID gift_id)
{
    auto iter = next(gift_ids.begin(), pos);
    this->gift_ids.insert(iter, gift_id);
}

void Route::remove(size_t pos){
    auto iter = next(gift_ids.begin(),pos);
    gift_ids.erase(iter);
}
