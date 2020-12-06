#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_PQ.h"
#include "_item.h"

typedef struct node *link;
struct node
{
    Item val;
    link next;
};

static link PQ=NULL;
static int N=0;

link NewNode(Item val,link next)
{
    link x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->val=val;
    x->next=next;
    return x;
}

void InserimentoPQ(Item val)
{
    PQ=NewNode(val,PQ);
    N++;
}

void EliminaItemPQ(Item val)
{
    link x,p;
    if(PQ==NULL)
        exit(-1);
    for(x=PQ, p=NULL;x!=NULL;p=x, x=x->next)
    {
        if(CMPnomi(x->val,val))
        {
            if(x==PQ)
                PQ=x->next;
            else
                p->next=x->next;
            free(x);
            break;
        }
    }
    N--;
}

void stampaSuFilePQ()
{
    FILE *fp=NULL;
    link x;
    fp=fopen("save.txt","w");
    if(fp==NULL)
        exit(-1);
    fprintf(fp,"%d\n",N);
    for(x=PQ; x!=NULL;x=x->next)
        fprintf(fp,"%s %.2f\n",GETname(x->val),GETprio(x->val));
    printf("\nSalvataggio completato!");
    fclose(fp);
    return;
}

Item estraiMinPQ()
{
    Item tmp;
    link x,p;
    float min;
    x=PQ;
    min=GETprio(x->val);
    for(x=PQ, p=NULL;x!=NULL;p=x, x=x->next)
    {
        if(GETprio(x->val)<min)
        {
            min=GETprio(x->val);
        }
    }
    for(x=PQ, p=NULL;x!=NULL;p=x, x=x->next)
    {
        if(GETprio(x->val)==min)
        {
            tmp=CostruisciItem(GETname(x->val),GETprio(x->val));
            if(x==PQ)
                PQ=x->next;
            else
                p->next=x->next;
            free(x);
            break;

        }
    }
    N--;
    return tmp;
}

void StampaPQ()
{
    link x;
    printf("\nStampa partecipanti con relativi punteggi\n");
    for(x=PQ; x!=NULL;x=x->next)
        ITEMshow(x->val);
}

int PQvuota()
{
    if(PQ==NULL)
        return 1;
    else
        return 0;
}
void caricaDaFilePQ(char *nomefile)
{
    FILE *fp;
    int n,i;
    char s[MAXC];
    float p;
    Item tmp;
    if(PQvuota())
    {
        fp=fopen(nomefile,"r");
        fscanf(fp,"%d",&n);
        N=n;
        for(i=0; i<n; i++)
        {
            fscanf(fp,"%s %f",s,&p);
            tmp=CostruisciItem(s,p);
            InserimentoPQ(tmp);
        }
        fclose(fp);
    }
    else
        printf("\nPQ gia' piena");
}
