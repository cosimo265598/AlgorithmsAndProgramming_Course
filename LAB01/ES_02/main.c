#include <stdio.h>
#include <stdlib.h>
#define  MAX 20
#define LUNG 10

int acquisci_matrice(int mat[MAX][MAX])
{
    FILE *fp;
    char nomefile[LUNG];
    int i,j,n;
    printf("\nInserisci il nome del file: ");
    scanf("%s",nomefile);
    fp=fopen(nomefile,"r");
    if(fp==NULL)
        return -1;
    fscanf(fp,"%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            fscanf(fp,"%d",&mat[i][j]);
    return n;
}

void visualizza_matrice(int mat[MAX][MAX],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d\t",mat[i][j]);
        printf("\n");
    }
}
void stampa_sx_dx(int x,int y,int n,int mat[MAX][MAX],int dist)
{
    int j;
    for(j=x;j<n-dist;j++)
        printf(" %d ",mat[x][j]);
}
void stampa_top_bottom(int x,int y,int n,int mat[MAX][MAX],int dist)
{
    int i;
    for(i=x;i<n-dist;i++)
        printf(" %d ",mat[i][y]);
}
void stampa_dx_sx(int x,int y,int n,int mat[MAX][MAX],int dist)
{
    int j;
    for(j=y;j>=dist;j--)
        printf(" %d ",mat[x][j]);
}
void stampa_bottom_top(int x,int y,int n,int mat[MAX][MAX],int dist)
{
    int i;
    for(i=x;i>=dist;i--)
        printf(" %d ",mat[i][y]);
}
void elabora_matrice(int mat[MAX][MAX],int n)
{
    int i=0,j=0,cont=0,stop,centro=0;
    // gestione dell centro con relativi numero di cicli
    if(n%2)
    {
        stop=((n-1)/2);
        centro=1;
    }
    else
        stop=((n-1)/2)+1;
    while(cont<stop)
    {
        stampa_sx_dx(i,j,n,mat,cont);
        stampa_top_bottom(i+1,(n-1)-cont,n,mat,cont+1);
        stampa_dx_sx(n-1-cont,n-1-cont,n,mat,cont);
        stampa_bottom_top((n-1)-(cont+1),j,n,mat,cont+1);
        i++;
        j++;
        cont++;
    }//stampa del centro manuale
    if(centro==1)
        printf(" %d ",mat[(n-1)/2][(n-1)/2]);
}
int main()
{
    int mat[MAX][MAX];
    int rc;/** rc indica che ha lo stesso numero di righe e colonne*/
    rc=acquisci_matrice(mat);
    visualizza_matrice(mat,rc);
    printf("\n");
    elabora_matrice(mat,rc);
    return 0;
}
