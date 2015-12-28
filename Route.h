//
// Created by alexey on 26.12.15.
//

#ifndef KEGGLE_SANTA_ROUTE_H
#define KEGGLE_SANTA_ROUTE_H

#include <vector>
#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <string>

#include "Gift.h"
#include "const.h"

using namespace std;


class Route{
public:
	Route(GlobalGiftData gift_data)
		: gift_data(gift_data)
	{ }

    //Route(Route const &) = delete;
    void operator=(Route const &r) = delete;


    void add(GiftID gift_id);
    void add(std::initializer_list<GiftID> gift_id_il);

    void insert(size_t pos, GiftID gift_id);

    void remove(size_t pos);

	inline
	bool can_add(GiftID gift_id){
		return (weight + gift_data[gift_id].Weight())<=sleigh_weight_limit;
	}

    inline
    bool can_add_wlimit(GiftID gift_id, FloatType limit){
        return (weight + gift_data[gift_id].Weight())<=limit;
    }


	inline
	FloatType Weight(){return weight;}

	// iterator implementation
	auto begin() const{
		return this->gift_ids.begin();
	}
	auto end() const{
		return this->gift_ids.end();
	}

	IntType size() const {return gift_ids.size();}
	GiftID operator[](IntType index) const {return gift_ids[index];}




    void BuildIndexes(vector<GiftIndexData> & indexData){
        for (int i = 0; i < this->gift_ids.size(); ++i) {
            auto gift_id = gift_ids[i];
            indexData[gift_id].route_pos = i;
        }
    }

    FloatType EstRemoveNode(IntType index);

    FloatType EstAddNode(size_t pos, GiftID gift_id);
protected:
    const Location & PrevLoc(IntType pos);
    const Location & NextLoc(IntType pos);
private:
	GlobalGiftData gift_data;

	vector<GiftID> gift_ids;
	FloatType weight = 0.0;
};



FloatType route_evaluation(GlobalGiftData g_data,
                           const Route & r);
FloatType evaluate_solution(
        GlobalGiftData g_data,
        const vector<Route> & routes);

IntType
GetGiftIDSCount(const vector<Route> & routes);

vector<GiftID>
GetAllGiftIDS(const vector<Route> & routes);

#endif //KEGGLE_SANTA_ROUTE_H
