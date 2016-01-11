#ifndef KEGGLE_SANTA_GIFT_H
#define KEGGLE_SANTA_GIFT_H

#include <vector>
#include <set>
#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <algorithm>

#include "types.h"
#include "Location.h"
#include "phantom_types.h"

using namespace std;

//class Gift;






using GiftIDMap = vector<RouteID>;
using RouteIDMap = vector<GiftID>;


/// Index = gift_id
/// Value = vehicla_id

//using SolutionOutput = vector<IntType>;


class Gift;

using GiftTuple = tuple<IntType, FloatType, FloatType, FloatType>;
//using Route = vector<IntType>;




using GiftData = vector<Gift>;
using GlobalGiftData = const vector<Gift> &;

struct GiftIndexData{
	int route_pos = -1;
	FloatType dist_from_start = -1.0;
};



class Gift
{
public:

	Gift(IntType id, FloatType latitude, FloatType longitude, FloatType weight)
		: id(id), weight(weight), loc(latitude, longitude)
	{ }

	Gift(IntType id,
			 FloatType x, FloatType y, FloatType z,
			 FloatType weight)
		: id(id), weight(weight), loc(x, y, z)
	{ }


	IntType ID() const
	{
		return id;
	}

	FloatType Weight() const
	{
		return weight;
	}

	const Location & Loc() const{
		return loc;
	}
private:
	IntType id;
	FloatType weight;
	Location loc;
};


//inline
//void SortDistanceByWeight(GlobalGiftData data,
//						  vector<GiftID>& gift_ids,
//						  const Location& loc){
//	std::sort(
//		gift_ids.begin(),
//        gift_ids.end(), [&data, &loc](const auto & id1,
//                                      const auto & id2){
//			auto data1 = data[id1];
//			auto data2 = data[id2];

//			auto d1 = Dist(loc, data1.Loc());
//			auto d2 = Dist(loc, data2.Loc());

//			auto v1 = d1/data1.Weight();
//			auto v2 = d2/data2.Weight();

//            if (v1<v2)
//              return true;
//            else
//              return false;
//		});
//}


inline
vector<GiftID> GenerateIDvector(GlobalGiftData gifts)
{
    vector<GiftID> res(gifts.size());
    for (int i = 0; i < gifts.size(); ++i)
        res.at(i) = gifts.at(i).ID();
    return res;
}

inline
set<GiftID> GenerateIDset(GlobalGiftData gifts){
    set<GiftID> res;
    for (int i = 0; i < gifts.size(); ++i){
        auto id = gifts.at(i).ID();
        res.insert(id);
    };
    return res;
}







#endif //KEGGLE_SANTA_GIFT_H
