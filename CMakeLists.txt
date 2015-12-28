#cmake_minimum_required(VERSION 2.8)
cmake_minimum_required(VERSION 3.3)
project(keggle_santa)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
#find_package(Gecode REQUIRED COMPONENTS kernel support int set driver flatzinc gist minimodel search)
#include_directories(GECODE_INCLUDE_DIR)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O0")

set(SOURCE_FILES main.cpp
        Gift.cpp Gift.h
        Location.cpp Location.h
        types.h
        const.h
#        simple_solver.cpp simple_solver.h
        Route.cpp Route.h
				IOfuncs.h IOfuncs.cpp
				ClarkeWright.cpp ClarkeWright.h
				SimulatedAnnealing.cpp SimulatedAnnealing.h
				NNSearcher.cpp NNSearcher.h
				Solution.h Solution.cpp
				RandomPointSelector.h RandomPointSelector.cpp
				phantom_types.h
#				gecodesupport.h gecodesupport.cpp
				)


#set(SOURCE_FILES ${SOURCE_FILES} simple_solver.cpp simple_solver.h )
add_subdirectory(libs/nanoflann-1.1.9)

add_executable(keggle_santa ${SOURCE_FILES})
target_link_libraries(keggle_santa

		${GECODE_LIBRARIES}
		)
