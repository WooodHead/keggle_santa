#ifndef EVALUATION_TEST_H
#define EVALUATION_TEST_H

#include <cassert>

#include "gift_testing_data.h"

#include "../Route.h"
#include "../IOfuncs.h"
#include "../file_provider.h"
#include "../SimulatedAnnealing.h"

using namespace std;


//inline
//Route make_route(initializer_list<RouteID> ril){
//    return Route(static_data::gifts_values(), ril);
//}

//inline
//FloatType eval_route(const Route & r){
//    return route_evaluation(
//                static_data::gifts_values(),
//                r);
//}


void test_route_evaluation1(GlobalGiftData gdata);
void test_route_evaluation2(GlobalGiftData gdata);
void test_route_evaluation4(GlobalGiftData gdata);
void test_route_evaluation5(GlobalGiftData gdata);

//void test_solution_evaluation2();


void test_solution_evaluation3();


void test_solution_evaluation5();


void test_solution_evaluation6();

void RoundDistances(vector<FloatType> & distances);
void RoundValues(vector<FloatType> & distances);

inline
void test_swapmove_operation1(){
    IOhelper io( file_prov().DataFile() );
    Solution initial_sol = io.LoadSolution(
                file_prov().sol_file7()
                );
    auto obj_func_init = evaluate_solution(
                initial_sol.Gifts(),
                initial_sol.Routes());


//    auto gift_id = initial_sol.GetRoute(0)[0];
//    SwapMove sm(0,0,0,0, gift_id);
//    sm.MakeMove(initial_sol);
    RouteID r_from, r_to;
    SimulatedAnnealing sa(initial_sol,true);
    sa.SetOnMove([&](auto move){
        r_from = move.route_from;
        r_to = move.route_to;
    });
    sa.work(1);

    auto obj_func1 = evaluate_solution(
                initial_sol.Gifts(),
                initial_sol.Routes());

    auto sol_output = GetSolutionOutput(
                initial_sol.Routes(),
                initial_sol.Gifts());
    auto re_read_routes = ReadSolutionRoutes(sol_output, initial_sol.Gifts());
    auto reread_sol = StartingSolution(initial_sol.Gifts(), re_read_routes);

    auto obj_func2 = evaluate_solution(initial_sol.Gifts(), re_read_routes);

    CompareSolutions(initial_sol, reread_sol);

    assert(obj_func1==obj_func2);
}

inline
void test_route_evaluation(){
    IOhelper io( file_prov().DataFile() );
    auto gifts = io.LoadGifts();

    test_route_evaluation1(gifts);
    test_route_evaluation2(gifts);
    test_route_evaluation4(gifts);
    test_route_evaluation5(gifts);

//    test_solution_evaluation2();
    test_solution_evaluation3();
    test_solution_evaluation5();
    test_solution_evaluation6();

    test_swapmove_operation1();
}


#endif // EVALUATION_TEST_H
