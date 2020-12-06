#include <stdio.h>
#include <stdlib.h>
#include "_ingredienti.h"
#define MAXS 255
LISTA_W InserisciDaFile(char *nomefile,int *n)
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


int main(int argc,char *argv[])
{
    LISTA_W A;
    int n;

    A=InserisciDaFile(argv[1],&n);
    Stampa_Lista(A);

    printf("\n\nHello world!\n");
    return 0;

}
