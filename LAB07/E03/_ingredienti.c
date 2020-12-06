
#include <stdio.h>
#include <stdlib.h>
#include "_ingredienti.h"
#include <string.h>

#define MAXC 255


struct node{
    char nome[MAXC];
    float costo;
    float calorie;
    NODE next;
};
typedef struct LISTA_WRAPPER{
 NODE head;
 NODE tail;
 int  N;
}LISTA_WRAPPER;

LISTA_W InizializzaLista()
{
    LISTA_W a= malloc(sizeof(*a));
    a->head=NULL;
    a->tail=NULL;
    a->N=0;
    return a;
}

void InserimentoCoda(LISTA_W mia_lista,char *n,float c,float cal)
{
    if(mia_lista->head==NULL)
        mia_lista->head=mia_lista->tail=NewNODE(n,c,cal,NULL);
    else
    {
        mia_lista->tail->next=NewNODE(n,c,cal,NULL);
        mia_lista->tail=mia_lista->tail->next;
    }
}


NODE NewNODE(char *n,float c,float cal,NODE next)
{
    NODE x;
    x=malloc(sizeof(*x));
    if(x==NULL)
        exit(-1);
    x->calorie=cal;
    x->costo=c;
    strcpy(x->nome,n);
    x->next=next;
    return x;
}

void Stampa_Lista(LISTA_W mia_lista)
{
    NODE x;
    for(x=mia_lista->head ; x!=NULL; x=x->next)
        printf("\n\nNome: %s \nCosto: %.2f \nCalorie: %.2f ",x->nome,x->costo,x->calorie);
}

// FUNZIONi E STRUTTURE DATI

