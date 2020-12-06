#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// definizione di punto
typedef struct
{
    float x;
    float y;
    float d;
}punto_t;

// definizione lista punto
typedef struct node_
{
    punto_t coordinate;
    struct node_ * next;
}node;
typedef node *link;

link NuovoPunto(punto_t a,link succ)
{
    link z=NULL;
    z=malloc(sizeof(node));
    if(z==NULL)
        return NULL;
    z->coordinate=a;
    z->next=succ;
    return z;
}

link InserimentoOrder(link h,punto_t a)
{
    link t=NULL,p=NULL;
    if(h==NULL)
        return NuovoPunto(a,h);
    else
        if(h->coordinate.d > a.d)
            return NuovoPunto(a,h);

    for( t=h->next , p=h; t!=NULL && a.d > t->coordinate.d; p=t , t=t->next );
    p->next=NuovoPunto(a,t);

    return h;
}

float distanzaOrigine(punto_t a)
{
    float l = a.x*a.x + a.y*a.y ;
    return (float)sqrt((double)l);
}

void StampaLista(link h)
{
    link k=NULL;
    printf("\n Head-> ");
    for(k=h; k!=NULL; k=k->next)
        printf("\n{(%.2f , %.2f) , distanza %.2f } - ",k->coordinate.x,k->coordinate.y,k->coordinate.d);
}

int main()
{
    punto_t k;
    link h=NULL;
    int fine=1;

    while (fine)
    {
        printf("\n Inserisci le coordinate: ");
        scanf("%f %f",&k.x,&k.y);
        k.d=distanzaOrigine(k);
        h=InserimentoOrder(h,k);
        StampaLista(h);
    }



    return 0;
}
