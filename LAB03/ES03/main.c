#include <stdio.h>
#include <stdlib.h>
#define MAXRC 50

void leggiMatrice(int M[][MAXRC],int dim,int *nr,int *nc,char *nomefile)
{
    FILE *fp=NULL;
    int i,j;

    fp=fopen(nomefile,"r");
    if(fp==NULL)
        return printf("\nArgomento Mancante!");

    fscanf(fp,"%d%d",nr,nc);
    for(i=0; i<*nr; i++)
        for(j=0; j<*nc; j++)
            fscanf(fp,"%d",&M[i][j]);

}

void stampaMatrice(int M[][MAXRC],int nr,int nc)
{
    int i,j;
    for(i=0; i<nr; i++)
    {
        for(j=0; j<nc; j++)
            printf("%d\t",M[i][j]);
        printf("\n");
    }

    return;
}

void azzeraMatrice(int occ[][MAXRC],int nr,int nc)
{
    int i,j;
    for(i=0; i<nr; i++)
    {
        for(j=0; j<nc; j++)
            occ[i][j]=0;
    }

    return;
}

int verificaCammino(int M[][MAXRC],int nr,int nc,int *p)
{
    if(M[nr][nc]!=0)
    {
        *p=*p+M[nr][nc];
        return 1;
    }
    else
        return 0;

}

void camminoSuMappa(int M[][MAXRC],int nr,int nc)
{
    int occ[MAXRC][MAXRC];
    int x,y,p=0,semplice=1,corretto=1;

    azzeraMatrice(occ,nr,nc);
    printf("\nCoordinate <x,y>: ");
    scanf("%d%d",&x,&y);
    while(x!=-1 && y!=-1)
    {
        if(occ[x][y]==0)
        {
            occ[x][y]++;
            if(!verificaCammino(M,x,y,&p))
                corretto=0;
        }
        else
            semplice=0;

        printf("\nCoordinate <x,y>: ");
        scanf("%d%d",&x,&y);
    }
    printf("\nIl cammino %s , costa %d, %s ",corretto==1?" e' corretto":" non e' corretto",p,semplice==1?"ed e' semplice":" e non e' semplice");

}

int main(int argc, char *argv[])
{
    int mat[MAXRC][MAXRC];
    int nr=0,nc=0;

    leggiMatrice(mat,MAXRC,&nr,&nc,argv[1]);
    printf("\nMATRICE ACQUISITA:\n\n");
    stampaMatrice(mat,nr,nc);
    camminoSuMappa(mat,nr,nc);

    return 0;
}
