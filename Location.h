//
// Created by alexey on 24.12.15.
//

#ifndef KEGGLE_SANTA_LOCATION_H
#define KEGGLE_SANTA_LOCATION_H

#include <cmath>

#include "types.h"


class Location{
public:
	Location(FloatType latitude, FloatType longitude);
    Location(FloatType x, FloatType y, FloatType z):X(x),Y(y),Z(z){}

private:

	FloatType X;
	FloatType Y;
	FloatType Z;

	friend
	FloatType HaversineDistance(const Location & loc1,
								const Location & loc2);

    friend
    FloatType NormalDistance(const Location & loc1,
                             const Location & loc2);

	friend
	void GetXYZ(const Location & loc,
				FloatType & X,
				FloatType & Y,
				FloatType & Z);
};


FloatType Dist(const Location & loc1, const Location & loc2);

FloatType HaversineDistance(const Location & loc1, const Location & loc2);


//FloatType __distance(const Location & loc1, const Location & loc2);

void ConvertToXYZ(FloatType latitude,
				  FloatType longitude,

				  FloatType & X,
				  FloatType & Y,
				  FloatType & Z);


#endif //KEGGLE_SANTA_LOCATION_H
