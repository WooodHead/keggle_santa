/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Guido Tack <tack@gecode.org>
 *
 *  Copyright:
 *     Guido Tack, 2012
 *
 *  Last modified:
 *     $Date: 2015-03-19 14:02:56 +0100 (Thu, 19 Mar 2015) $ by $Author: schulte $
 *     $Revision: 14468 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#include <gecode/search.hh>

namespace Gecode { namespace Search { namespace Meta {

  /*
   * Stopping for meta search engines
   *
   */

  bool 
  RestartStop::stop(const Statistics& s, const Options& o) {
    // Stop if the fail stop object for the engine says so
    if (e_stop->stop(s,o)) {
      e_stopped = true;
      m_stat.restart++;
      return true;
    }
    // Stop if the stop object for the meta engine says so
    if ((m_stop != NULL) && m_stop->stop(m_stat+s,o)) {
      e_stopped = false;
      return true;
    }
    return false;
  }


  Space*
  RBS::next(void) {
    if (restart) {
      restart = false;
      sslr++;
      NoGoods& ng = e->nogoods();
      // Reset number of no-goods found
      ng.ng(0);
      CRI cri(stop->m_stat.restart,sslr,e->statistics().fail,last,ng);
      bool r = master->master(cri);
      stop->m_stat.nogood += ng.ng();
      if (master->status(stop->m_stat) == SS_FAILED) {
        stop->update(e->statistics());
        delete master;
        master = NULL;
        e->reset(NULL);
        return NULL;
      } else if (r) {
        stop->update(e->statistics());
        Space* slave = master;
        master = master->clone(shared);
        complete = slave->slave(cri);
        e->reset(slave);
        sslr = 0;
        stop->m_stat.restart++;
      }
    }
    while (true) {
      Space* n = e->next();
      if (n != NULL) {
        // The engine found a solution
        restart = true;
        delete last;
        last = n->clone();
        return n;
      } else if ( (!complete && !e->stopped()) ||
                  (e->stopped() && stop->enginestopped()) ) {
        // The engine must perform a true restart
        // The number of the restart has been incremented in the stop object
        sslr = 0;
        NoGoods& ng = e->nogoods();
        ng.ng(0);
        CRI cri(stop->m_stat.restart,sslr,e->statistics().fail,last,ng);
        (void) master->master(cri);
        stop->m_stat.nogood += ng.ng();
        long unsigned int nl = ++(*co);
        stop->limit(e->statistics(),nl);
        if (master->status(stop->m_stat) == SS_FAILED)
          return NULL;
        Space* slave = master;
        master = master->clone(shared);
        complete = slave->slave(cri);
        e->reset(slave);
      } else {
        return NULL;
      }
    }
    GECODE_NEVER;
    return NULL;
  }
  
  Search::Statistics
  RBS::statistics(void) const {
    return stop->metastatistics()+e->statistics();
  }
  
  bool
  RBS::stopped(void) const {
    /*
     * What might happen during parallel search is that the
     * engine has been stopped but the meta engine has not, so
     * the meta engine does not perform a restart. However the
     * invocation of next will do so and no restart will be
     * missed.
     */
    return e->stopped(); 
  }
  
  RBS::~RBS(void) {
    // Deleting e also deletes stop
    delete e;
    delete master;
    delete last;
    delete co;
  }

}}}

// STATISTICS: search-meta
