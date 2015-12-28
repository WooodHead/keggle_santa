//
// Created by alexey on 25.12.15.
//

#include "simple_solver.h"

vector<Route> SimpleSolver::generate(){
	vector<Route> res;

	while (this->gifts_not_in_routes.size()>0) {

		//auto start_pnts = selectNRandomPoint(50);
        auto start_pnts = selectNStartPoint(100);

		vector<GiftID> ids(
			gifts_not_in_routes.begin(),
			gifts_not_in_routes.end()
		);

		KDTreeSingleIndexAdaptorParams kd_par(10);
		PointCloud cloud(ids, gl_gift_data);
		GiftKDTree kdtree(3, cloud, kd_par);
		kdtree.buildIndex();

		for (auto s_pnt: start_pnts)
			if (contain(gifts_not_in_routes, s_pnt)) {

				Route route(gl_gift_data);
				remove(gifts_not_in_routes, s_pnt);
				route.add(s_pnt);


				auto loc = gl_gift_data[s_pnt].Loc();
                auto nn_ids = FindNN(kdtree, ids, loc, 200);
				//remove_if(nn_ids.begin())

				std::sort(
					nn_ids.begin(),
					nn_ids.end(),
					[&](auto p1, auto p2)
					{
						const auto & pnt_gift = gl_gift_data[s_pnt];

						const auto & gift1 = gl_gift_data[p1];
						const auto & gift2 = gl_gift_data[p2];

						auto d1 = Dist(pnt_gift.Loc(), gift1.Loc());
						auto d2 = Dist(pnt_gift.Loc(), gift2.Loc());

						auto w1 = route.Weight() + gift1.Weight();
						auto w2 = route.Weight() + gift2.Weight();

						auto v1 = w1/d1;
						auto v2 = w2/d2;

						return d1<d2;
					});


                //sleigh_weight_limit = 1000;
                //auto limit = 300;
                auto limit = sleigh_weight_limit;

				for (auto id : nn_ids)
					if (contain(gifts_not_in_routes, id)) {
                        //if (route.can_add(id)) {
                        if (route.can_add_wlimit(id, limit)) {
							route.add(id);
							remove(gifts_not_in_routes, id);
						}
						else
							break;

					}
				res.push_back(route);

			}
	}

	return res;
}

GiftID SimpleSolver::selectRandomPoint()
{
	std::uniform_int_distribution<int> uniform_dist(
		0,
		gifts_not_in_routes.size()-1
	);
	int v = uniform_dist(default_random_engine);

	auto iter = gifts_not_in_routes.begin();
	std::advance(iter, v);

	return *iter;
}
vector<GiftID> SimpleSolver::FindNN(const GiftKDTree & kdtree,
																		const vector<GiftID> & items,
																		const Location & loc,
																		IntType  count)
{
	vector<GiftID> res;

	// query point
	FloatType query_pt[3];
	getPoint(loc, query_pt);


	// search N nearest
	std::vector<size_t> ret_index(count);
	std::vector<FloatType> out_dist_sqr(count);
	kdtree.knnSearch(&query_pt[0],
									 count,
									 &ret_index[0],
									 &out_dist_sqr[0]);

	for (auto i : ret_index) {
		res.push_back( items[i] );
	}

	return res;
}
vector<GiftID> SimpleSolver::selectNRandomPoint(IntType cnt)
{
    std::set<GiftID> res_set;
	for (int i = 0; i < cnt; ++i) {
		auto p = selectRandomPoint();
        res_set.insert(p);
	}

    std::vector<GiftID> res(res_set.begin(), res_set.end());
	return res;
}
//void SimpleSolver::BuildKDTree(const vector<GiftID> & items, GiftKDTree & index)
//{
//	KDTreeSingleIndexAdaptorParams kd_par(10);
//	PointCloud cloud(items, gl_gift_data);
//	index = GiftKDTree(3, cloud, kd_par);
//	index.buildIndex();
//}
vector<Route> ss_generate(GlobalGiftData gift_data)
{
	SimpleSolver ss(gift_data);
	auto routes = ss.generate();

	return routes;
}
vector<GiftID> SimpleSolver::selectNStartPoint(IntType cnt)
{
	vector<GiftID> ids(
		gifts_not_in_routes.begin(),
		gifts_not_in_routes.end()
	);

	KDTreeSingleIndexAdaptorParams kd_par(10);
	PointCloud cloud(ids, gl_gift_data);
	GiftKDTree kdtree(3, cloud, kd_par);
	kdtree.buildIndex();

	auto nn_ids = FindNN(kdtree, ids, north_pole, cnt);

	return nn_ids;
}
