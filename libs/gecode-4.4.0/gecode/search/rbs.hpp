/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *     Guido Tack <tack@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2014
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

#include <gecode/search/support.hh>
#include <gecode/search/meta/rbs.hh>

namespace Gecode {

  template<template<class> class E, class T>
  forceinline
  RBS<E,T>::RBS(T* s, const Search::Options& m_opt) {
    if (m_opt.cutoff == NULL)
      throw Search::UninitializedCutoff("RBS::RBS");
    Search::Options e_opt(m_opt.expand());
    e_opt.clone = false;
    Search::Meta::RestartStop* rs = new Search::Meta::RestartStop(m_opt.stop);
    e_opt.stop = rs;
    Space* master;
    Space* slave;
    if (s->status(rs->m_stat) == SS_FAILED) {
      rs->m_stat.fail++;
      master = NULL;
      slave  = NULL;
    } else {
      if (m_opt.clone)
        master = s->clone();
      else
        master = s;
      slave = master->clone();
      CRI cri(0,0,0,NULL,NoGoods::eng);
      slave->slave(cri);
    }
    E<T> engine(dynamic_cast<T*>(slave),e_opt);
    Search::EngineBase<T>* eb = &engine;
    Search::Engine* ee = eb->e;
    eb->e = NULL;
    e = new Search::Meta::RBS(master,rs,ee,m_opt);
  }


  template<template<class> class E, class T>
  forceinline T*
  rbs(T* s, const Search::Options& o) {
    RBS<E,T> r(s,o);
    return r.next();
  }

}

// STATISTICS: search-meta
