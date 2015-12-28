#include "Solution.h"


Solution StartingSolution(GlobalGiftData giftData, GenerateFuncType func){
    auto routes =  func(giftData);

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
