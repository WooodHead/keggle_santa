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

using namespace std;

class IOhelper{
public:
    IOhelper(string input_data_file): input_data_file(input_data_file){}

    Solution GenerateSolution();
    Solution LoadSolution(const string & solution_fn);

    void SaveSolution(const Solution & sol,
                      const string & solution_fn);

private:
    string input_data_file;
    vector<Route> GenerateDumbSolution2(GlobalGiftData gifts);
};

vector<Gift>
LoadGifts(const string & file_name);

vector<Route>
ReadSolutionRoutes(const string & file_name,
                   GlobalGiftData gift_data);

void
WriteSolution(const string & file_name,
              const vector<Route> & routes,
              GlobalGiftData gift_data);


#endif //KEGGLE_SANTA_IOFUNCS_H
