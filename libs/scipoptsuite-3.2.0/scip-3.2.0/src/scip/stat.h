/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2015 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   stat.h
 * @brief  internal methods for problem statistics
 * @author Tobias Achterberg
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_STAT_H__
#define __SCIP_STAT_H__


#include "scip/def.h"
#include "blockmemshell/memory.h"
#include "scip/type_prob.h"
#include "scip/type_retcode.h"
#include "scip/type_set.h"
#include "scip/type_stat.h"
#include "scip/type_mem.h"
#include "scip/pub_message.h"

#include "scip/struct_stat.h"

#ifdef __cplusplus
extern "C" {
#endif

/** creates problem statistics data */
extern
SCIP_RETCODE SCIPstatCreate(
   SCIP_STAT**           stat,               /**< pointer to problem statistics data */
   BMS_BLKMEM*           blkmem,             /**< block memory */
   SCIP_SET*             set,                /**< global SCIP settings */
   SCIP_MESSAGEHDLR*     messagehdlr         /**< message handler */
   );

/** frees problem statistics data */
extern
SCIP_RETCODE SCIPstatFree(
   SCIP_STAT**           stat,               /**< pointer to problem statistics data */
   BMS_BLKMEM*           blkmem              /**< block memory */
   );

/** diables the collection of any statistic for a variable */
extern
void SCIPstatDisableVarHistory(
   SCIP_STAT*            stat                /**< problem statistics data */
   );

/** enables the collection of statistics for a variable */
extern
void SCIPstatEnableVarHistory(
   SCIP_STAT*            stat                /**< problem statistics data */
   );

/** marks statistics to be able to reset them when solving process is freed */
extern
void SCIPstatMark(
   SCIP_STAT*            stat                /**< problem statistics data */
   );

/** reset statistics to the data before solving started */
extern
void SCIPstatReset(
   SCIP_STAT*            stat,               /**< problem statistics data */
   SCIP_SET*             set                 /**< global SCIP settings */
   );

/** reset implication counter */
extern
void SCIPstatResetImplications(
   SCIP_STAT*            stat                /**< problem statistics data */
   );

/** reset presolving and current run specific statistics */
extern
void SCIPstatResetPresolving(
   SCIP_STAT*            stat                /**< problem statistics data */
   );

/* reset primal-dual integral */
extern
void SCIPstatResetPrimalDualIntegral(
   SCIP_STAT*            stat,               /**< problem statistics data */
   SCIP_SET*             set,                /**< global SCIP settings */
   SCIP_Bool             partialreset        /**< should time and integral value be kept? (in combination with no statistical
                                              *  reset, integrals are added for each problem to be solved) */
   );

/** update the primal-dual integral statistic. method accepts + and - SCIPsetInfinity() as values for
 *  upper and lower bound, respectively
 */
extern
void SCIPstatUpdatePrimalDualIntegral(
   SCIP_STAT*            stat,               /**< problem statistics data */
   SCIP_SET*             set,                /**< global SCIP settings */
   SCIP_PROB*            transprob,          /**< transformed problem */
   SCIP_PROB*            origprob,           /**< original problem */
   SCIP_Real             primalbound,        /**< current primal bound in transformed problem, or infinity */
   SCIP_Real             dualbound           /**< current lower bound in transformed space, or -infinity */
   );

/** reset current branch and bound run specific statistics */
extern
void SCIPstatResetCurrentRun(
   SCIP_STAT*            stat,               /**< problem statistics data */
   SCIP_Bool             solved              /**< is problem already solved? */
   );

/** resets display statistics, such that a new header line is displayed before the next display line */
extern
void SCIPstatResetDisplay(
   SCIP_STAT*            stat                /**< problem statistics data */
   );

/** increases LP count, such that all lazy updates depending on the LP are enforced again */
extern
void SCIPstatEnforceLPUpdates(
   SCIP_STAT*            stat                /**< problem statistics data */
   );

/** depending on the current memory usage, switches mode flag to standard or memory saving mode */
extern
void SCIPstatUpdateMemsaveMode(
   SCIP_STAT*            stat,               /**< problem statistics data */
   SCIP_SET*             set,                /**< global SCIP settings */
   SCIP_MESSAGEHDLR*     messagehdlr,        /**< message handler */
   SCIP_MEM*             mem                 /**< block memory pools */
   );

/** enables or disables all statistic clocks of \p stat concerning LP execution time, strong branching time, etc.
 *
 *  @note: The (pre-)solving time clocks which are relevant for the output during (pre-)solving
 *         are not affected by this method
 *
 *  @see: For completely disabling all timing of SCIP, consider setting the parameter timing/enabled to FALSE
 */
extern
void SCIPstatEnableOrDisableStatClocks(
   SCIP_STAT*            stat,               /**< SCIP statistics */
   SCIP_Bool             enable              /**< should the LP clocks be enabled? */
   );

#ifdef __cplusplus
}
#endif

#endif
