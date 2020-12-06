#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10
#define LUNG 10

/** acquisizione della matrice */
/** elaborazione  */
/** verifica */
void stampamatrice(int n,float matrice[MAX][MAX])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%.2f \t",matrice[i][j]);
        printf("\n");
    }
}

void elaborazione (int n, float matrice[MAX][MAX])
{
    int i,j,k;
    float potenza;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(matrice[i][j]<=0)
                matrice[i][j]=0;
            else
            {
                if(matrice[i][j]<1)/** gestione del caso <1 ovve potenze negative del 10 **/
                {
                    k=+1;
                    do
                    {
                        k--;
                        potenza=pow(10,k);
                    }while(potenza>=matrice[i][j]);
                    matrice[i][j]=pow(10,k+1);
                }
                else
                {
                    k=-1;
                    do
                    {
                        k++;
                        potenza=pow(10,k);
                    }while(potenza<=matrice[i][j]);
                    matrice[i][j]=potenza;

                }
            }
        }
}

int acquisisci_matrice(float matrice[MAX][MAX])
{
    FILE *fp;
    char miofile[LUNG];
    int n,i=0,j=0;
    printf("Nome file:\n");
    scanf("%s",miofile);
    fp=fopen(miofile,"r");
    if(fp==NULL)
        return -1;
    fscanf(fp,"%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            fscanf(fp,"%f",&matrice[i][j]);
        }
    return n;
}
int verifica(float matrice[MAX][MAX],int n)
{
    /** verificare simmetria */
    int i,j,ok=1;
    for(i=0; i<n && ok==1 ;i++)
        for(j=0; j>i && ok==1 ;j++)
            if(matrice[i][j]!=matrice[j][i])
                return 0;

    return 1;
}

int main()
{
    float mat[MAX][MAX];
    int n;
    n=acquisisci_matrice(mat);
    if(n==-1)
        printf("\nerrore apertura file!");
    elaborazione(n,mat);
    stampamatrice(n,mat);
    if(verifica(mat,n))
        printf("\nLa matrice generata dal file in ingresso e' simmetrica.");
    else
        printf("\nLa matrice generata dal file in ingresso non e' simmetrica.");

    return 0;
}
