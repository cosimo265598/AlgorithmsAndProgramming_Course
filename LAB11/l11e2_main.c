#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "pq.h"
#include "item.h"

int main(int argc, char **argv) {

  PQ pq = PQinit();

  PQinsert(pq, ITEMnew("ciao", 4));
  PQinsert(pq, ITEMnew("come", 7));
  PQinsert(pq, ITEMnew("va?", 5));

  while(!PQempty(pq)) {
    Item a = PQget(pq);
    ITEMshow(a);
  }

  return 0;
}
