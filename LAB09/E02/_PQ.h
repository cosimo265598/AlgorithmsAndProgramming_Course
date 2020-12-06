#ifndef _PQ_H_INCLUDED
#define _PQ_H_INCLUDED
#include "_item.h"

void InserimentoPQ(Item val);
void EliminaItemPQ(Item val);
void stampaSuFilePQ();
Item estraiMinPQ();
void StampaPQ();
void caricaDaFilePQ(char *nomefile);
int PQvuota();

#endif // _PQ_H_INCLUDED
