//
// Created by alexey on 27.12.15.
//

#include "NNSearcher.h"
vector<GiftID> nnsearch::NNSearcher::FindNN(GiftID gift_id, IntType count)
{
	vector<GiftID> res;

	auto loc = this->g_gifts[gift_id].Loc();
	FloatType query_pt[3];
	getPoint(loc, query_pt);

	// search N nearest
	std::vector<size_t> ret_index(count);
	std::vector<FloatType> out_dist_sqr(count);
	kdtree->knnSearch(&query_pt[0],
									 count,
									 &ret_index[0],
									 &out_dist_sqr[0]);

	for (auto i : ret_index) {
		auto id = this->g_id[i];
		if(id!=gift_id)
			res.push_back(id);
	}
	return res;
}
