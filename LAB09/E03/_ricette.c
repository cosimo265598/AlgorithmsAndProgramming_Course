#include <stdio.h>
#include <stdlib.h>
#include "_ricette.h"
#include <string.h>
#define MAXC 255

struct node_ricetta{
    char nome_ingre[MAXC];
    float grammi;
    LINK next;
};

struct node_r{
    char nome[MAXC];
    float tempo; // minuti
    int n_ingre; // al grammo
    LINK head_r;
};

struct LISTA_WRAPPER_RICETTA{
     NODE_RICETTA *elenco;
     int maxn;
     int N;
}LISTA_WRAPPER_RICETTA;


void Stampa_Ricetta(LISTA_W_RICETTA mia)
{
    int i;
    for(i=0;i<mia->N;i++)
    {
        printf("\n******** Ricetta ********");
        printf("\nNome : %s  Minuti: %f  Numero in: %d",mia->elenco[i]->nome,
                                                        mia->elenco[i]->tempo,
                                                        mia->elenco[i]->n_ingre);
        stampa_elementi_R(mia->elenco[i]);
    }
}

void stampa_elementi_R(NODE_RICETTA mia_lista)
{
    LINK x;
    for(x=mia_lista->head_r ; x!=NULL; x=x->next)
        printf("\n\nNome: %s \nGrammi: %.2f ",x->nome_ingre,x->grammi);

}

LISTA_W_RICETTA InizializzaListaRicetta( int max_elementi )
{
    LISTA_W_RICETTA a=malloc(sizeof(*a));
    a->maxn=max_elementi;
    a->N=0;
    a->elenco=malloc(max_elementi*sizeof(*a->elenco));
    return a;
}

void InRicetta(LISTA_W_RICETTA mia,NODE_RICETTA mia_ric)
{
    int dim;
    if(mia->N<mia->maxn)
    {
        mia->elenco[mia->N]=mia_ric;
        mia->N++;
    }
    else
    {
        dim=mia->N;
        mia=realloc(mia,2*dim);
        mia->elenco[dim]=mia_ric;
        mia->N=dim+1;
        mia->maxn=2*dim;
    }
}

NODE_RICETTA NewRicetta(char *nomericetta,float temporicetta,int n_i,LINK val)
{
    NODE_RICETTA a=malloc(sizeof(*a));
    strcpy(a->nome,nomericetta);
    a->tempo=temporicetta;
    a->n_ingre=n_i;
    a->head_r=val;
    return a;
}


LINK NewRicetta2(char *nomeIN,float gram,LINK Next)
{
    LINK a=malloc(sizeof(*a));
    strcpy(a->nome_ingre,nomeIN);
    a->grammi=gram;
    a->next=Next;
    return a;
}

LINK InserisciElementiRicettaInCoda(LINK h, char *n,float g)
{
    LINK x;
    if(h==NULL)
        return NewRicetta2(n,g,NULL);
    else
    {
        for(x=h;x->next!=NULL;x=x->next);
        x->next=NewRicetta2(n,g,NULL);
        return h;
    }
}

void dettagliRicetta(LISTA_W_RICETTA mia,char *nomericetta)
{
    int i;
    for(i=0;i<mia->N;i++)
    {
        if(strcmp(mia->elenco[i]->nome,nomericetta)==0)
        {
            stampa_elementi_R(mia->elenco[i]);
            break;
        }
    }
}

float costoUnaRicetta (LISTA_W_RICETTA mia,char *nomericetta,LISTA_W L_in)
{
    int i;
    LINK x=NULL;
    float costo=0;
    for(i=0;i<mia->N;i++)
    {
        if(strcmp(mia->elenco[i]->nome,nomericetta)==0)
        {
            for(x=mia->elenco[i]->head_r;x!=NULL;x=x->next)
                costo=costo+(RitornaCosto(L_in,x->nome_ingre)*(x->grammi/1000));
            return costo;

        }
    }
}

float calorieUnaRicetta(LISTA_W_RICETTA mia,char *nomericetta,LISTA_W L_in)
{
    int i;
    LINK x=NULL;
    float ca=0;
    for(i=0;i<mia->N;i++)
    {
        if(strcmp(mia->elenco[i]->nome,nomericetta)==0)
        {
            for(x=mia->elenco[i]->head_r;x!=NULL;x=x->next)
                ca=ca+(RitornaCalorie(L_in,x->nome_ingre)*x->grammi);
            return ca;
        }
    }
}


void StampaInsiemeRicettaIngrediente(LISTA_W_RICETTA mia,char *nomeIN)
{
    int i;
    LINK x=NULL;
    for(i=0;i<mia->N;i++)
    {
        for(x=mia->elenco[i]->head_r;x!=NULL;x=x->next)
        {
            if(strcmp(nomeIN,x->nome_ingre)==0)
            {
                printf("\n******** Ricetta ********");
                printf("\nNome : %s ",mia->elenco[i]->nome);
            }
        }
    }




}
