//
// Created by alexey on 24.12.15.
//

#ifndef KEGGLE_SANTA_TYPES_H
#define KEGGLE_SANTA_TYPES_H

using FloatType = double;
using IntType = int;//unsigned long;

//using VehicleId = IntType;
namespace internal {
    struct RouteIDTag { };
    struct GiftIDTag { };
}

//using RouteID = Explicit<IntType, internal::RouteIDTag>;
//using GiftID = Explicit<IntType, internal::GiftIDTag>;
using RouteID = IntType;
using GiftID = IntType;



#endif //KEGGLE_SANTA_TYPES_H
