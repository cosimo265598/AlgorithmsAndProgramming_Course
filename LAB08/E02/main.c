#include <stdio.h>
#include <stdlib.h>
#include "_ingredienti.h"
#include "_ricette.h"
#define MAXS 255

LISTA_W InserisciDaFileIngredienti(char *nomefile,int *n)
{
    LISTA_W A=InizializzaLista();
    FILE *fp;
    int i;
    char b[MAXS];
    float c;
    float d;

    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",n);
    for(i=0;i<*n;i++)
    {
        fscanf(fp,"%s %f %f",b,&c,&d);
        InserimentoCoda(A,b,c,d);
    }
    fclose(fp);
    return A;
}

LISTA_W_RICETTA InserisciDaFileRicette(char *nomefile,int *m)
{
    LISTA_W_RICETTA B;
    LINK B1=NULL;
    NODE_RICETTA B2=NULL;
    FILE *fp;
    int i,n,l,j;
    char b[MAXS];
    char d[MAXS];
    float c,z;
    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",&n);
    *m=n;
    B=InizializzaListaRicetta(n);
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%s %f %d",b,&c,&l);
        for(j=0;j<l;j++)
        {
            fscanf(fp,"%s %f",d,&z);
            B1=InserisciElementiRicettaInCoda(B1,d,z);
        }
        B2=NewRicetta(b,c,l,B1);
        B1=NULL;
        InRicetta(B,B2);
        B2=NULL;
    }
    return B;
}

int menu()
{
    int scelta;
    printf("\n*************** Menu *************** ");
    printf("\n1) stampa dettagli di una ricetta ");
    printf("\n2) stampa dei dettagli di un ingrediente ");
    printf("\n3) calcolo del costo di una ricetta ");
    printf("\n4) calcolo dell'apporto calorico di una ricetta ");
    printf("\n5) stampa dell' intero elenco di ricette");
    printf("\n6) stampa dell' intero elenco di ingredienti");
    printf("\n7) stampa dell' elenco di ricette in cui sia presente un dato ingrediente");
    printf("\n8) introduzione (e memorizzazione) di una nuova ricetta ");
    printf("\n9) fine");
    printf("\nScelta :   ");
    scanf("%d",&scelta);
    return scelta;
}

void NuovaRicetta(LISTA_W_RICETTA B)
{
    LINK H=NULL;
    NODE_RICETTA Z=NULL;
    char st[MAXS];
    int i,n,gr;
    float f;
    printf("\nNumero di ingredienti: ");
    scanf("%d",&n);
    printf("\nInserisci come <nome ingrediente> <grammi>: \n");
    for(i=0;i<n;i++)
    {
        scanf("\n%s %d",st,&gr);
        H=InserisciElementiRicettaInCoda(H,st,gr);
    }
    printf("\nNome ricetta: ");
    scanf("%s",&st);
    printf("\nTempo Preparazione <Minuti> : ");
    scanf("%f",&f);
    Z=NewRicetta(st,f,n,H);
    InRicetta(B,Z);

}


int main(int argc,char *argv[])
{
    LISTA_W A;
    LISTA_W_RICETTA B;
    int n,m;
    int j;
    float f=0;
    int scelta;
    char st[MAXS];

    A=InserisciDaFileIngredienti(argv[1],&n);
    B=InserisciDaFileRicette(argv[2],&m);

    j=menu();
    switch(j)
    {
        case 1:
            printf("\nNome ricetta: ");
            scanf("%s",st);
            dettagliRicetta(B,st);
            break;
        case 2:
            printf("\nNome ingrediente: ");
            scanf("%s",st);
            dettagliIngrediente(A,st);
            break;
        case 3:
            printf("\nNome ricetta: ");
            scanf("%s",st);
            f=(float) costoUnaRicetta(B,st,A);
            printf("\n Costo della ricetta : %.2f ",f);
            break;
        case 4:
            printf("\nNome ricetta: ");
            scanf("%s",st);
            f=(float) calorieUnaRicetta(B,st,A);
            printf("\n Calorie della ricetta : %.2f ",f);
            break;
        case 5:
            Stampa_Ricetta(B);
            break;
        case 6:
            Stampa_Lista(A);
            break;
        case 7:
            printf("\nNome Ingrediente: ");
            scanf("%s",st);
            StampaInsiemeRicettaIngrediente(B,st);
            break;
        case 8:
            NuovaRicetta(B);
            break;

    }

    return 0;

}
