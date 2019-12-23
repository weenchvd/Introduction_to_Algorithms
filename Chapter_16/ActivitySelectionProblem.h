#ifndef _ACTIVITYSELECTIONPROBLEM_H
#define _ACTIVITYSELECTIONPROBLEM_H

#include "ActivitySelectionProblem_common.h"
#include "ActivitySelectionProblem_struct.h"
#include <stdio.h>
#include <stdlib.h>

void RecursiveActivitySelector(AS_t* as, int k);
void GreedyActivitySelector(AS_t* as);

#endif