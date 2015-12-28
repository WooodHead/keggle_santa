//
// Created by alexey on 24.12.15.
//

#include <cassert>

#include "Location.h"
#include "const.h"

Location::Location(FloatType latitude, FloatType longitude)
	//: latitude(latitude), longitude(longitude)
{
	ConvertToXYZ(latitude, longitude, X,Y,Z);
}
FloatType HaversineDistance(const Location & loc1, const Location & loc2)
{
	FloatType dX = loc1.X - loc2.X;
	FloatType dY = loc1.Y - loc2.Y;
	FloatType dZ = loc1.Z - loc2.Z;

	FloatType r = sqrt(dX*dX + dY*dY + dZ*dZ);

	return 2*earth_radius * asin(r);
}

/*
FloatType NormalDistance(const Location & loc1, const Location & loc2)
{
    FloatType dX = loc1.X - loc2.X;
    FloatType dY = loc1.Y - loc2.Y;
    FloatType dZ = loc1.Z - loc2.Z;

    FloatType r = sqrt(dX*dX + dY*dY + dZ*dZ);
    return r;
}
*/

void ConvertToXYZ(FloatType latitude,
				  FloatType longitude,

				  FloatType & X,
				  FloatType & Y,
				  FloatType & Z)
{

	auto LatitudeInRads  = (M_PI/180) * latitude;
	auto LongitudeInRads = (M_PI/180) * longitude;

	//auto LatitudeInRads  = latitude;
	//auto LongitudeInRads = longitude;

	// Cartesian coordinates, normalized for a sphere of diameter 1.0
	X = 0.5 * cos(LatitudeInRads) * sin(LongitudeInRads);
	Y = 0.5 * cos(LatitudeInRads) * cos(LongitudeInRads);
	Z = 0.5 * sin(LatitudeInRads);

}
FloatType Dist(const Location &loc1, const Location &loc2)
{

    auto res = HaversineDistance(loc1, loc2);
    //auto res = NormalDistance(loc1, loc2);
    if(res<0){
        auto k = 5;
    }

    assert(res>=0);
    return res;
}

//FloatType __distance(const Location & loc1, const Location & loc2)
//{
//	auto lon1 = loc1.getLongitude();
//	auto lon2 = loc2.getLongitude();
//
//	auto lat1 = loc1.getLatitude();
//	auto lat2 = loc2.getLatitude();
//
//	// get differences first
//	double dlon = lon1 - lon2; // difference for longitude
//	double dlat = lat1 - lat2; // difference for latitude
//// part a of algorithm
//	double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
//// part b of algorithm
//	double b = 2 * atan2(sqrt(a), sqrt(1 - a));
//// our result, or the great-circle distance between two locations
//	double result = earth_radius * b;
//	return result;
//}

void GetXYZ(const Location &loc, FloatType &X, FloatType &Y, FloatType &Z)
{
	X = loc.X;
	Y = loc.Y;
	Z = loc.Z;
}
