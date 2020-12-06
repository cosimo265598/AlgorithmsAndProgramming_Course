#ifndef _RICETTE_H_INCLUDED
#define _RICETTE_H_INCLUDED
#include "_ingredienti.h"

typedef struct node_ricetta *LINK;
typedef struct node_r *NODE_RICETTA;
typedef struct LISTA_WRAPPER_RICETTA *LISTA_W_RICETTA;

LINK InserisciElementiRicettaInCoda(LINK h, char *n,float g);
NODE_RICETTA NewRicetta(char *nomericetta,float temporicetta,int n_i,LINK val);
LISTA_W_RICETTA InizializzaListaRicetta(int max_elementi);
void Stampa_Ricetta(LISTA_W_RICETTA mia);
void stampa_elementi_R(NODE_RICETTA mia_lista);
void dettagliRicetta(LISTA_W_RICETTA mia,char *nomericetta);
float costoUnaRicetta (LISTA_W_RICETTA mia,char *nomericetta,LISTA_W L_in);
float calorieUnaRicetta(LISTA_W_RICETTA mia,char *nomericetta,LISTA_W L_in);
void StampaInsiemeRicettaIngrediente(LISTA_W_RICETTA mia,char *nomeIN);
void InRicetta(LISTA_W_RICETTA mia,NODE_RICETTA mia_ric);


#endif // _RICETTE_H_INCLUDED
