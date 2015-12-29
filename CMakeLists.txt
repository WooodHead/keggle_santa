#cmake_minimum_required(VERSION 2.8)
cmake_minimum_required(VERSION 3.3)
project(keggle_santa)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
#find_package(Gecode REQUIRED COMPONENTS kernel support int set driver flatzinc gist minimodel search)
#include_directories(GECODE_INCLUDE_DIR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

#set(SCIP_LPS libs/scipoptsuite-3.2.0/soplex-2.2.0)
#set(SCIP_ROOT libs/scipoptsuite-3.2.0/scip-3.2.0)
#set(SCIP_ROOT libs/scipoptsuite-3.2.0/scip-3.2.0)
#set(SCIP_ROOT libs/scipoptsuite-3.2.0/scip-3.2.0/libs)
#find_package(SOPLEX REQUIRED)
#include_directories(${SOPLEXT_INCLUDE_DIRS})

find_package(ZLIB REQUIRED)
#include_directories(/usr/include/readline)
#file(GLOB SOURCES123 "./*.c")

include_directories(libs/scipoptsuite-3.2.0/soplex-2.2.0/src)
include_directories(libs/scipoptsuite-3.2.0/scip-3.2.0/src)

link_directories(libs/scipoptsuite-3.2.0/soplex-2.2.0/lib)
link_directories(libs/scipoptsuite-3.2.0/scip-3.2.0/lib)
#link_directories(/usr/lib/x86_64-linux-gnu)
#link_directories(/usr/local/lib)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O0 ")

#set(SOURCE_FILES ${SOURCE_FILES} simple_solver.cpp simple_solver.h )
add_subdirectory(libs/nanoflann-1.1.9)
add_subdirectory(testing)


set(SOURCE_FILES
#				${SANTA_TESTING_SOURCES}
				testing/gift_testing_data.h testing/gift_testing_data.cpp
				testing/evaluation_test.h testing/evaluation_test.cpp

				main.cpp
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
				SCIP_solver.cpp SCIP_solver.h
)


add_executable(keggle_santa ${SOURCE_FILES})
target_link_libraries(keggle_santa
		libscip.a
		liblpispx.a
		libnlpi.cppad.a
		libobjscip.a
		libsoplex.linux.x86_64.gnu.opt.a
		libzimpl.linux.x86_64.gnu.opt.a

		${ZLIB_LIBRARIES}
		readline
		history
		)
