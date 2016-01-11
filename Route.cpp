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

vector<FloatType> routes_eval_values(GlobalGiftData g_data,
                                     const vector<Route> & routes){
    vector<FloatType> res;
    for(const auto & r: routes){
        res.push_back(route_evaluation(g_data, r));
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
    assert(pos < this->gift_ids.size());

    // update weight
    const auto & gift = gift_data[gift_id];
    weight += gift.Weight();

    auto iter = next(gift_ids.begin(), pos);
    this->gift_ids.insert(iter, gift_id);
}

void Route::remove(size_t pos){
    assert(pos < this->gift_ids.size());

    // update weight
    const auto & gift = gift_data[this->gift_ids[pos]];
    weight -= gift.Weight();

    auto iter = next(gift_ids.begin(),pos);
    gift_ids.erase(iter);
}

bool Route::BFContains(GiftID gift_id)
{
    auto it = find(
                this->gift_ids.begin(),
                this->gift_ids.end(),
                gift_id);
    return it != this->gift_ids.end();
}

vector<FloatType> Route::GenWeights()
{
    vector<FloatType> res;
    for(auto g_id: this->gift_ids){
        res.push_back(this->gift_data[g_id].Weight());
    }
    return res;
}

vector<FloatType> Route::GenDistances() const{
    vector<FloatType> res;

    assert(this->gift_ids.size()>0);


    Location l1 = north_pole;
    Location l2 = this->gift_data[gift_ids[0]].Loc();
    res.push_back(Dist(l1,l2));

    for (int i = 1; i < this->gift_ids.size(); ++i) {
        const Location & l1 = this->gift_data[gift_ids[i-1]].Loc();
        const Location & l2 = this->gift_data[gift_ids[i]].Loc();
        res.push_back(Dist(l1,l2));
    }

    l1 = gift_data[gift_ids[gift_ids.size()-1]].Loc();
    l2 = north_pole;
    res.push_back(Dist(l1,l2));

    return res;
}

IntType Route::GetGiftPos(GiftID gift_id) const
{

    auto it = find(
                gift_ids.begin(), gift_ids.end(),
                gift_id);
    assert(it != this->gift_ids.end());

    auto pos = std::distance(gift_ids.begin(), it);
    return pos;
}

FloatType Route::EstRemoveNode(IntType index) const{
    assert(index < this->gift_ids.size());

    auto gift_id = gift_ids[index];
    const auto & gift = gift_data[gift_id];

    gift_id = gift_ids[0];
    auto l1 = north_pole;
    auto l2 = gift_data[gift_id].Loc();

    FloatType dist = Dist(l1,l2);
    for (int i = 1; i <= index; ++i) {
        gift_id = gift_ids[i-1];
        l1 = gift_data[gift_id].Loc();

        gift_id = gift_ids[i];
        l2 = gift_data[gift_id].Loc();

        dist += Dist(l1,l2);
    }

    auto total_weight = this->Weight()+sleigh_base_weight;
    FloatType w0 = total_weight;
    for (int i = 0; i <= index; ++i) {
        w0 -= gift_data[gift_ids[i]].Weight();
    }

    auto node_w = gift.Weight();
    auto prev_loc = PrevLoc(index);
    auto next_loc = NextLoc(index);
    auto loc = gift.Loc();


    auto minus_dist = Dist(prev_loc, loc) + Dist(next_loc, loc);
    auto add_dist = Dist(prev_loc, next_loc);

    auto dist_diff = minus_dist - add_dist;

    return (dist*node_w + (w0)*dist_diff);
}

class RouteAccessException : public exception{
public:
    RouteAccessException(const Route & r, IntType pos): pos(pos), r(r){
        stringstream ss;
        ss << "route size == "
           << r.size()
           << " acess at pos == "
           << pos;
        s =  ss.str();
    }

    virtual const char* what() const noexcept override{
        return s.c_str();
    }
private:
    string s;
    IntType pos;
    const Route & r;
};


class ChangedNodeGiftGetter{
public:
    ChangedNodeGiftGetter(size_t pos, GiftID gift_id):pos(pos), gift_id(gift_id){
    }


private:
    size_t pos;
    GiftID gift_id;
};

FloatType Route::EstChangeNode(size_t pos, GiftID gift_id) const{
    ChangedNodeGiftGetter
}

FloatType Route::EstAddNode(size_t pos, GiftID gift_id) const{
    if(pos>= this->gift_ids.size())
        throw RouteAccessException(*this, pos);

    //assert(pos < this->gift_ids.size());


    auto prev_loc = PrevLoc(pos);
    auto next_loc = gift_data[gift_ids[pos]].Loc();
    auto loc = this->gift_data[gift_id].Loc();
    auto node_w = gift_data[gift_id].Weight();

    auto total_weight = this->Weight()+sleigh_base_weight;
    FloatType w0 = total_weight;
    for (int i = 0; i < pos; ++i) {
        w0 -= gift_data[gift_ids[i]].Weight();
    }


    Location l1(0,0,0);
    Location l2(0,0,0);
    FloatType dist = 0.0;
    if(pos > 0){
        gift_id = gift_ids[0];
        l1 = north_pole;
        l2 = gift_data[gift_id].Loc();

        dist += Dist(l1,l2);
    }
    for (int i = 1; i < pos; ++i) {
        gift_id = gift_ids[i-1];
        l1 = gift_data[gift_id].Loc();

        gift_id = gift_ids[i];
        l2 = gift_data[gift_id].Loc();

        dist += Dist(l1,l2);
    }
    dist += Dist(prev_loc, loc);

    auto minus_dist = Dist(prev_loc, loc) + Dist(next_loc, loc);
    auto add_dist = Dist(prev_loc, next_loc);

    auto dist_diff = abs(minus_dist - add_dist);

    return dist*node_w + (w0)*dist_diff;
}

const Location &Route::PrevLoc(IntType pos) const{
    if(pos == 0)
        return north_pole;
    else
        return this->gift_data[gift_ids[pos-1]].Loc();
}

FloatType Route::Weight() const{
    return weight;
}

FloatType Route::Distance() const
{
    auto distances = GenDistances();
    auto sum = std::accumulate(distances.begin(), distances.end(), 0.0);
    return sum;
}

const Location &Route::NextLoc(IntType pos) const{
    if(pos == this->gift_ids.size()-1 )
        return north_pole;
    else
        return this->gift_data[gift_ids[pos+1]].Loc();
}
