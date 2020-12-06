#include <stdio.h>
#include <stdlib.h>
#define MAXR 50

void leggiMatrice(int M[][MAXR],int dim,int *nr,int *nc)
{
    FILE *fp;
    int i,j;
    fp=fopen("matrice.txt","r");
    if(fp==NULL)
        return ;
    fscanf(fp,"%d%d",nr,nc);
    for(i=0;i<*nr;i++)
        for(j=0;j<*nc;j++)
            fscanf(fp,"%d",&M[i][j]);
}

void elaboraMatrice(int M[][MAXR],int nr,int nc)
{
    int i,j,b=0,h=0,n=1;
    for(i=0;i<nr;i++)
        for(j=0;j<nc;j++)
        {
            if(M[i][j]==1)
                if(riconosciRegione(M,nr,nc,i,j,&b,&h))
                {
                    printf("\nRegione %d: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d",n,i,j,b,h,b*h);
                    n++;
                }
            b=0;
            h=0;
        }
}

int riconosciRegione(int M[][MAXR],int nr, int nc,int r,int c,int *b,int *h)
{
    int i,j,val;
    if((M[r][c-1]==0 && M[r-1][c]==0 )|| (c-1<0 && r-1<0) || (c-1<0 && M[r-1][c] ==0) || (M[r][c-1]==0 && r-1<0))
    {
        for(i=r, val=1; i>=0 && i<nr && M[i][c];i++,val++);
        *h=val-1;
        for(j=c, val=1; j>=0 && j<nc && M[r][j];j++, val++);
        *b=val-1;

        return 1;
    }
    else
        return 0;
}

void stampa(int M[][MAXR],int nr,int nc)
{
    int i,j;
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
            printf("%d\t",M[i][j]);
        printf("\n");
    }

}

int main()
{
    int mat[MAXR][MAXR];
    int nr=0,nc=0;
    printf("\n** Inizio **\n");
    leggiMatrice(mat,MAXR,&nr,&nc);
    printf("\nMatrice acquisita!\n");
    stampa(mat,nr,nc);
    printf("\nDati: ");
    elaboraMatrice(mat,nr,nc);



    return 0;
}
