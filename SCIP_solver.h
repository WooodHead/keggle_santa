//
// Created by alexey on 29.12.15.
//

#ifndef KEGGLE_SANTA_SCIP_SOLVER_H
#define KEGGLE_SANTA_SCIP_SOLVER_H

//#include ""
#include "objscip/objscip.h"
#include "objscip/objscipdefplugins.h"

using namespace std;
using namespace scip;

class SCIP_solver
{

};

inline
int scip_main(){
	SCIP* scip = NULL;
    SCIP_CALL(SCIPcreate(&scip));
//	SCIP_CALL(  );

}

#endif //KEGGLE_SANTA_SCIP_SOLVER_H
