#ifndef SOLUTIONOUTPUT_H
#define SOLUTIONOUTPUT_H

#include <set>
#include <map>

#include "types.h"
#include "Route.h"

using namespace std;

class SolutionOutputValue{
public:
        GiftID gift_id;
        RouteID route_id;
};

class SolutionOutput{
public:
    SolutionOutput(){}

    void push_back(GiftID gift_id, RouteID route_id);

    size_t size() const;

    const SolutionOutputValue& operator [](IntType index) const;

    vector<Route> ReadRoutes(GlobalGiftData gifts);
private:
    vector<SolutionOutputValue> items;
};

#endif // SOLUTIONOUTPUT_H
