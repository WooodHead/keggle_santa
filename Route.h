//
// Created by alexey on 26.12.15.
//

#ifndef KEGGLE_SANTA_ROUTE_H
#define KEGGLE_SANTA_ROUTE_H

#include <vector>
#include <algorithm>
#include <cassert>
#include <initializer_list>

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


    const Location & PrevLoc(IntType pos){
        if(pos == 0)
            return north_pole;
        else
            return this->gift_data[gift_ids[pos-1]].Loc();
    }

    const Location & NextLoc(IntType pos){
        if(pos == this->gift_ids.size()-1 )
            return north_pole;
        else
            return this->gift_data[gift_ids[pos+1]].Loc();
    }


	FloatType EstRemoveNode(IntType index){        
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

    FloatType EstAddNode(size_t pos, GiftID gift_id){
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
