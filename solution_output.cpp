#include "solution_output.h"




void SolutionOutput::push_back(GiftID gift_id, RouteID route_id){
    SolutionOutputValue item{gift_id, route_id};
    this->items.push_back(item);
}

size_t SolutionOutput::size() const{return this->items.size();}

const SolutionOutputValue &SolutionOutput::operator [](IntType index) const{
    return this->items[index];
}

vector<Route> SolutionOutput::ReadRoutes(GlobalGiftData gifts){
    map<RouteID, Route> r_ids;
    for(auto item: items){
        if(r_ids.find(item.route_id)==r_ids.end()){
            r_ids.insert({item.route_id, Route(gifts)});
        };
        auto it = r_ids.find(item.route_id);
        Route & r = it->second;
        r.add(item.gift_id);
    }

    vector<Route> res;
    for(auto pair: r_ids){
        res.push_back(get<1>(pair));
    }
    return res;
}
