#include "evaluation_test.h"



void test_route_evaluation2(){
    auto r = make_route({
                            38949,38950,38951,38952,38953,38954,38955,
                            38956,38957,38958,38959,38960,38961,38962,
                            38963,38964,38965,38966,38967,38968,38969,
                            38970,38971,38972,38973,38974,38975,38976,
                            38977,38978,38979,38980,38981,38982,38983,
                            38984,38985,38986,38987,38988,38989,38990,
                            38991,38992,38993,38994,38995,38996,38997,
                            38998,38999,39000,39001,39002,39003,39004,
                            39005,39006,39007,39008,39009
                        });
    auto r_weight = eval_route(r);
    auto r_weight_req = 264871954.298;
    assert(round(r_weight) == round(r_weight_req));
}

void test_route_evaluation1(){
    GlobalGiftData const_gifts = static_data::gifts_values();
    FloatType r_weight, r_weight_req;

    auto route_values = {
        1263,1561,3373,7855,11693,22173,22895,
        40137,42127,44796,46995,48734,49286,64206,
        68260,72880,74613,80012,82175,91467,94009};
    Route r(const_gifts, route_values);

    vector<FloatType> route_weights=r.GenWeights();
    vector<FloatType> route_weights_req = {
        1.0,1.0,50.0,30.8449690944,
        30.3592786156,9.07124714251,6.46303123105,
        16.3518907548,13.7365857447,8.99645512192,
        5.50097233436,26.5890805733,1.0,13.0199068307,
        5.05953192132,1.0,50.0,1.89021767789,1.0,
        6.93102857881,8.97811943737};
    assert(route_weights==route_weights_req);

    r_weight = route_evaluation(const_gifts, r);
    r_weight_req = 645307.127856;
    assert(round(r_weight)==round(r_weight_req));
}

void test_solution_evaluation2(){
    const auto sol6 = static_data::solution6();
    FloatType r_weight, r_weight_req;
    r_weight = evaluate_solution(
                static_data::gifts_values(),
                sol6
                );
    r_weight_req = 48645711480.4;

    assert(round(r_weight)==round(r_weight_req));
}
