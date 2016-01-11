//
// Created by alexey on 29.12.15.
//

#ifndef KEGGLE_SANTA_SCIP_SOLVER_H
#define KEGGLE_SANTA_SCIP_SOLVER_H

#include "Solution.h"

#include "scip/reader_zpl.h"
#include "objscip/objscip.h"
#include "objscip/objscipdefplugins.h"

using namespace std;
using namespace scip;

class SCIPRouteOptimizer{
public:

private:
};

class HeurFarthestInsert : public scip::ObjHeur{

};


inline
int scip_main(Solution & sol){
        return -1;

        const Route& route = sol.Routes()[0];


        SCIP* scip = NULL;

        SCIP_CALL(SCIPcreate(&scip));
        /* include default plugins */
        SCIP_CALL( SCIPincludeDefaultPlugins(scip) );
        SCIP_CALL( SCIPincludeReaderZpl(scip) );


        SCIP_CALL(SCIPcreateProb(scip, "route", NULL, NULL,NULL, NULL, NULL, NULL, NULL));

//        SCIPreadProb()
//        SCIPcreateObjVar()
//        SCIPcreateObjProb()
//        SCIPcreate

//        SCIP_VAR* var;
//        SCIP_CALL_EXC(SCIPcreateVar(
//                          scip,
//                          & var,
//                          "x#i#j",
//                          0.0, 1.0, 1.0,
//        SCIP_VARTYPE_BINARY, TRUE, FALSE,
//        NULL, NULL, NULL, NULL, NULL));




//        SCIP_CALL_EXC(SCIPsolve(scip));
};

//inline
//int scip_main(Solution & sol){
//    const Route& route = sol.Routes()[0];


//	SCIP* scip = NULL;

//    SCIP_CALL(SCIPcreate(&scip));
//    /* include default plugins */
//    SCIP_CALL( SCIPincludeDefaultPlugins(scip) );

//    SCIP_CALL(SCIPcreateProb(scip, "route", NULL, NULL,
//                              NULL, NULL, NULL, NULL, NULL));))



//    SCIP_VAR* var;
//    SCIP_CALL_EXC(SCIPcreateVar(
//                      scip,
//                      & var,
//                      "x#i#j",
//                      0.0, 1.0, 1.0,
//    SCIP_VARTYPE_BINARY, TRUE, FALSE,
//    NULL, NULL, NULL, NULL, NULL));

//    SCIP_CALL_EXC(SCIPsolve(scip));
////	SCIP_CALL(  );
//}

#endif //KEGGLE_SANTA_SCIP_SOLVER_H
