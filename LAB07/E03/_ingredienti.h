#ifndef _INGREDIENTI_H_INCLUDED
#define _INGREDIENTI_H_INCLUDED



// PROTOTIPI DELLE FUNZIONI
typedef struct node *NODE;
typedef struct LISTA_WRAPPER *LISTA_W;


LISTA_W InizializzaLista();
void InserimentoCoda(LISTA_W mia_lista,char *n,float c,float cal);
NODE NewNODE(char *n,float c,float cal,NODE next);
void Stampa_Lista(LISTA_W mia_lista);







#endif // _INGREDIENTI_H_INCLUDED
