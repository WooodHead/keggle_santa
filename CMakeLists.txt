#cmake_minimum_required(VERSION 2.8)
cmake_minimum_required(VERSION 3.3)
project(keggle_santa)


set(CBC_PATH /home/alexey/development/cpp_projects/keggle_santa/libs/Cbc-2.9.7)
include_directories(${CBC_PATH}/include)
LINK_DIRECTORIES(${CBC_PATH}/lib)

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


#include_directories(/usr/include/readline)
#file(GLOB SOURCES123 "./*.c")

include_directories(libs/scipoptsuite-3.2.0/soplex-2.2.0/src)
include_directories(libs/scipoptsuite-3.2.0/scip-3.2.0/src)
link_directories(libs/scipoptsuite-3.2.0/soplex-2.2.0/lib)
link_directories(libs/scipoptsuite-3.2.0/scip-3.2.0/lib)

include_directories(libs/gecode-4.4.0/gecode)
link_directories(libs/gecode-4.4.0)

#link_directories(/usr/lib/x86_64-linux-gnu)
#link_directories(/usr/local/lib)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O0")

#set(SOURCE_FILES ${SOURCE_FILES} simple_solver.cpp simple_solver.h )
add_subdirectory(libs/nanoflann-1.1.9)
add_subdirectory(testing)

find_package(ZLIB REQUIRED)
find_package(OpenMP)
if (OPENMP_FOUND)
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

#find_package(Qt5Widgets REQUIRED)

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
				file_provider.h file_provider.cpp
				solution_output.h solution_output.cpp
				gecode_optim.h gecode_optim.cpp
				distance_matrix.h
)


add_executable(keggle_santa ${SOURCE_FILES})
target_link_libraries(keggle_santa
		#scip libs
		libscip.a
		liblpispx.a
		libnlpi.cppad.a
		libobjscip.a
		libsoplex.linux.x86_64.gnu.opt.a
		libzimpl.linux.x86_64.gnu.opt.a

		#cbc libs
		libCbcSolver.so
		libCgl.so
		libClp.so
		libClpSolver.so
		libCoinUtils.so
		libOsi.so
		libOsiCbc.so
		libOsiClp.so
		libCbcSolver.so
		libCgl.so
		libClp.so
		libClpSolver.so
		libCoinUtils.so
		libOsi.so
		libOsiCbc.so
		libOsiClp.so
		libCbc.so

		${ZLIB_LIBRARIES}

		#gecode
		libgecodedriver.so
		libgecodeflatzinc.so
		libgecodefloat.so
		libgecodegist.so
		libgecodeint.so
		libgecodekernel.so
		libgecodeminimodel.so
		libgecodesearch.so
		libgecodeset.so
		libgecodesupport.so

		libgmp.so

		readline
		history		
		)

#qt5_use_modules(keggle_santa Core Gui Widgets)
