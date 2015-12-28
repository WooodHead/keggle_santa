//
// Created by alexey on 24.12.15.
//

#ifndef KEGGLE_SANTA_CONST_H
#define KEGGLE_SANTA_CONST_H

#include "types.h"
#include "Location.h"
#include "math.h"

const FloatType sleigh_base_weight = 10;
const FloatType sleigh_weight_limit = 1000;
const Location north_pole = {90,0};
//const Location north_pole = {0,0,0};

#ifndef M_PI
    #define M_PI 3.141592653589793
#endif

const FloatType earth_radius = 6371.0;

#include <set>

template<typename T>
bool contain(const std::set<T> & s, const T & value){
	return s.find(value) != s.end();
}

template<typename T>
void remove(std::set<T> & s, const T & value){
	auto iter = s.find(value);
	if(iter != s.end())
		s.erase(iter);
}

#endif //KEGGLE_SANTA_CONST_H
