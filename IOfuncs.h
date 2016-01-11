//
// Created by alexey on 26.12.15.
//

#ifndef KEGGLE_SANTA_IOFUNCS_H
#define KEGGLE_SANTA_IOFUNCS_H

#include <string>
#include <tuple>
#include <map>
#include <cassert>

#include "Gift.h"
#include "Route.h"
#include "Solution.h"
#include "solution_output.h"

using namespace std;

class IOhelper{
public:
    IOhelper(string input_data_file);


    GiftData LoadGifts();

    Solution GenerateSolution();
    Solution LoadSolution(const string & solution_fn);

    void SaveSolution(const Solution & sol,
                      const string & solution_fn);

private:
    string input_data_file;
    vector<Route> GenerateDumbSolution2(GlobalGiftData gifts);
};


bool FileExists(const string & file_name);
void AssureFileExistence(const string & file_name);


vector<Gift>
LoadGifts(const string & file_name);


SolutionOutput GetSolutionOutput(
        const vector<Route> & routes,
        GlobalGiftData gift_data);

vector<Route>
ReadSolutionRoutes(
        SolutionOutput sol,
        GlobalGiftData gift_data);

vector<Route>
ReadSolutionRoutes(const string & file_name,
                   GlobalGiftData gift_data);



void
WriteSolution(const string & file_name,
              const vector<Route> & routes,
              GlobalGiftData gift_data);


#endif //KEGGLE_SANTA_IOFUNCS_H
