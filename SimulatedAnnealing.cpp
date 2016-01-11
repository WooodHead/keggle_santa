//
// Created by alexey on 27.12.15.
//

#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Solution &sol, bool use_console)
    : IterativeHeuristic(use_console),
      sol(sol),
      nnsearcher(sol.gl_gift_data)

{
    gift_ids = GenerateIDvector(sol.gl_gift_data);
    rand_selector = new RandomPointSelector(&sol);
}
