#ifndef PQ_H_DEF
#define PQ_H_DEF

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "item.h"

PQ PQinit();
int PQempty(PQ);
Item PQget(PQ);
void PQinsert(PQ, Item);

#endif
