#ifndef KEGGLE_SANTA_SIMPLE_SOLVER_H
#define KEGGLE_SANTA_SIMPLE_SOLVER_H

#include <vector>
#include <set>
#include <random>

#include "Gift.h"
#include "Route.h"

#include "libs/nanoflann-1.1.9/include/nanoflann.hpp"
#include "const.h"

using namespace std;
using namespace nanoflann;

struct PointCloud{
public:

	PointCloud(const vector<IntType> &g_id, const vector<Gift> &g_gifts)
		: g_id(g_id), g_gifts(g_gifts)
	{ }

	inline size_t kdtree_get_point_count() const {
		return g_id.size();
	}

	inline FloatType
	kdtree_distance(const FloatType *p1,
					const size_t idx_p2,size_t /*size*/) const
	{
		auto __id = g_id[idx_p2];
		const auto & gift = g_gifts[__id];
		auto gift_loc = gift.Loc();

		FloatType X,Y,Z;
		GetXYZ(gift_loc, X,Y,Z);

		const FloatType d0=p1[0] - X;
		const FloatType d1=p1[1] - Y;
		const FloatType d2=p1[2] - Z;

		return d0*d0+d1*d1+d2*d2;
	}

	inline FloatType
	kdtree_get_pt(const size_t idx, int dim) const
	{
		auto __id = g_id[idx];
		const auto & gift = g_gifts[__id];
		auto gift_loc = gift.Loc();

		FloatType X,Y,Z;
		GetXYZ(gift_loc, X,Y,Z);

		if (dim==0)
			return X;
		else
		if (dim==1)
			return Y;
		else
			return Z;
	}

	template <class BBOX>
	bool kdtree_get_bbox(BBOX& /*bb*/) const {
		return false;
	}
private:
	const vector<IntType> g_id;
	const vector<Gift> & g_gifts;
};

using GiftKDTree = KDTreeSingleIndexAdaptor<
	L2_Simple_Adaptor<FloatType, PointCloud> ,
	PointCloud,
	3 /* dim */> ;


inline void getPoint(const Location & loc,
					 FloatType *res_arr){
	FloatType X,Y,Z;
	GetXYZ(loc, X,Y,Z);

	res_arr[0] = X;
	res_arr[1] = Y;
	res_arr[2] = Z;
}


class SimpleSolver{
public:
	SimpleSolver(const vector<Gift> &gl_gift_data)
		: gl_gift_data(gl_gift_data)
	{
		gifts_not_in_routes = GenerateIDset(gl_gift_data);
		default_random_engine = std::default_random_engine(r_device());
	}

	vector<Route> generate();

	GiftID selectRandomPoint();
	vector<GiftID> selectNRandomPoint(IntType cnt);

	vector<GiftID> selectNStartPoint(IntType cnt);
protected:

	//void BuildKDTree(const vector<GiftID> & items, GiftKDTree & index);


	vector<GiftID> FindNN(const GiftKDTree & kdtree,
												const vector<GiftID> & items,
												const Location & loc,
												IntType  count);

private:
	std::random_device r_device;
	std::default_random_engine default_random_engine;;


  GlobalGiftData gl_gift_data;
	set<GiftID> gifts_not_in_routes;
};

vector<Route> ss_generate(GlobalGiftData gift_data);

#endif //KEGGLE_SANTA_SIMPLE_SOLVER_H
