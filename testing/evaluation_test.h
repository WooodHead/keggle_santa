#ifndef EVALUATION_TEST_H
#define EVALUATION_TEST_H

#include <cassert>

#include "gift_testing_data.h"

#include "../Route.h"

inline
Route make_route(initializer_list<RouteID> ril){
    return Route(static_data::gifts_values(), ril);
}

inline
FloatType eval_route(const Route & r){
    return route_evaluation(
                static_data::gifts_values(),
                r);
}

void test_route_evaluation2();
void test_route_evaluation1();


void test_solution_evaluation2();

//128706931626.0

inline
void test_route_evaluation(){
    test_route_evaluation1();
    test_route_evaluation2();

    test_solution_evaluation2();
}


#endif // EVALUATION_TEST_H
