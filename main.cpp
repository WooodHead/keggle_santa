#include <iostream>
#include <algorithm>

#include "Gift.h"
#include "const.h"
#include "IOfuncs.h"
#include "NNSearcher.h"
#include "simple_solver.h"
#include "Solution.h"
#include "SimulatedAnnealing.h"
#include "SCIP_solver.h"
#include "file_provider.h"
#include "distance_matrix.h"

// testing
#include "testing/gift_testing_data.h"
#include "testing/evaluation_test.h"

#include "coin/OsiClpSolverInterface.hpp"
#include "coin/CoinModel.hpp"
#include "coin/CbcModel.hpp"

#include "gecode_optim.h"

using namespace std;



//int mip_solver(){
//    OsiClpSolverInterface model;

//    CoinModel cm;

//    CbcModel m2;
////    m2.addCuts()

////    model.loadProblem();

//}

int main()
{


    // run tests
    test_route_evaluation();



    IOhelper io(file_prov().DataFile() );
    //auto sol = io.GenerateSolution();

    // 14421017258.58690
    auto sol = io.LoadSolution( file_prov().sol_file11() );
    auto obj_func1 = evaluate_solution(sol);



//    double mx, mn;
//    DistanceMatrix::getMinMax(sol.Gifts(), mx, mn);
//    auto sz=DistanceMatrix::vector_size(sol.Gifts().size())*4;
//    auto dm = new DistanceMatrix(sol.Gifts());
//
//    Route r(sol.Gifts(), {0,1,2,3,4});
//    gecode_app(sol.Gifts(), r);
//
//    scip_main(sol);
//    int k = 4;


    SimulatedAnnealing sa(sol, true);
    sa.work(1250000);

    auto obj_func2 = evaluate_solution(sol.Gifts(), sol.routes);


    auto diff = obj_func2 - obj_func1;

    auto sol_output = GetSolutionOutput(sol.Routes(), sol.Gifts());
    auto re_read_routes = ReadSolutionRoutes(sol_output, sol.Gifts());
    auto obj_func3 = evaluate_solution(sol.Gifts(), re_read_routes);



    cout << obj_func1 << endl;
    cout << obj_func2 << endl;
    cout << obj_func3 << endl;

    //14435462832,892761
    //14435462832.89280
    io.SaveSolution(sol, file_prov().sol_file());

	return 0;
}
