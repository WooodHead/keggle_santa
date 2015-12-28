//
// Created by alexey on 27.12.15.
//

#ifndef KEGGLE_SANTA_NNSEARCHER_H
#define KEGGLE_SANTA_NNSEARCHER_H

#include <vector>
#include <set>
#include <random>

#include "Gift.h"
#include "Route.h"

#include "libs/nanoflann-1.1.9/include/nanoflann.hpp"
#include "const.h"

using namespace std;
using namespace nanoflann;

namespace nnsearch
{

struct PointCloud
{
public:

    PointCloud(const vector<GiftID> &g_id, GlobalGiftData g_gifts)
		: g_id(g_id), g_gifts(g_gifts)
	{ }

	inline size_t kdtree_get_point_count() const
	{
		return g_id.size();
	}

	inline FloatType
	kdtree_distance(const FloatType *p1,
									const size_t idx_p2, size_t /*size*/) const
	{
		auto __id = g_id[idx_p2];
		const auto &gift = g_gifts[__id];
		auto gift_loc = gift.Loc();

		FloatType X, Y, Z;
		GetXYZ(gift_loc, X, Y, Z);

		const FloatType d0 = p1[0] - X;
		const FloatType d1 = p1[1] - Y;
		const FloatType d2 = p1[2] - Z;

		return d0 * d0 + d1 * d1 + d2 * d2;
	}

	inline FloatType
	kdtree_get_pt(const size_t idx, int dim) const
	{
		auto __id = g_id[idx];
		const auto &gift = g_gifts[__id];
		auto gift_loc = gift.Loc();

		FloatType X, Y, Z;
		GetXYZ(gift_loc, X, Y, Z);

		if (dim == 0)
			return X;
		else if (dim == 1)
			return Y;
		else
			return Z;
	}

	template<class BBOX>
	bool kdtree_get_bbox(BBOX & /*bb*/) const
	{
		return false;
	}
private:
    const vector<GiftID> g_id;
	GlobalGiftData g_gifts;
};

using GiftKDTree = KDTreeSingleIndexAdaptor<
	L2_Simple_Adaptor<FloatType, PointCloud>,
	PointCloud,
	3 /* dim */>;


class NNSearcher
{
public:
	NNSearcher(GlobalGiftData g_gifts): g_gifts(g_gifts)
	{
		g_id = GenerateIDvector(g_gifts);
		cloud = new PointCloud(g_id, g_gifts);

		KDTreeSingleIndexAdaptorParams kd_par(10);
		kdtree = new GiftKDTree(3, *cloud, kd_par);
		kdtree->buildIndex();
	}
	virtual ~NNSearcher(){
		delete kdtree;
		delete cloud;
	}

	vector<GiftID> FindNN(GiftID gift_id, IntType  count);

private:
	vector<GiftID> g_id;
	GlobalGiftData g_gifts;
	PointCloud* cloud;
	GiftKDTree *kdtree;

	inline void getPoint(const Location & loc,
											 FloatType *res_arr){
		FloatType X,Y,Z;
		GetXYZ(loc, X,Y,Z);

		res_arr[0] = X;
		res_arr[1] = Y;
		res_arr[2] = Z;
	}
};

}
#endif //KEGGLE_SANTA_NNSEARCHER_H
