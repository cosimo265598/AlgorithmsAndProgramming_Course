#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ruotaVettore(int V[], int dir, int N, int P)
{
    int i,j,c;
    N--;
    P--;
    if(dir==1) /** DESTRA */
    {
        for (i=0;i<=P;i++)
        {
            c=V[N];
            for(j=N;j>0;j--)
                V[j]=V[j-1];
            V[0]=c;
        }
    }
    else
    {
        /** SINISTRA */
        for (i=0;i<=P;i++)
        {
            c=V[0];
            for(j=0;j<N;j++)
                V[j]=V[j+1];
            V[N]=c;
        }

    }
}

void stampaMatrice(int dim2,int v[][dim2],int dim1)
{
    int i,j;
    printf("\n");
    for(i=0;i<dim1;i++)
    {
        for(j=0;j<dim2;j++)
            printf("%d  ",v[i][j]);
        printf("\n");
    }
}

void ruotaMatrice(int dim2,int M[][dim2], char r_o_c[], int target, int dim1, int P, int dir)
{
    int vet[dim1],i;
    if(strcmp(r_o_c,"RIGA")==0)
    {
        ruotaVettore(M[target-1],dir,dim2,P);
    }
    else
    {
        for(i=0;i<dim1;i++)
            vet[i]=M[i][target-1];
        ruotaVettore(vet,dir,dim1,P);
        for(i=0;i<dim1;i++)
           M[i][target-1]= vet[i];
    }
    return;
}

int main()
{
    int dim1=3,dim2=3;
    int mat[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    int p,dir,target,i;
    char r_o_c[10];
    do
    {
        printf("\n MENU -- rotazioni --: ");
        printf("\n Riga o Colonna: ");
        scanf("%s",r_o_c);
        for(i=0;i<strlen(r_o_c);i++)
            r_o_c[i]=toupper(r_o_c[i]);
        if(strcmp(r_o_c,"FINE")!=0)
        {
            printf("\n Numero di %s :",r_o_c);
            scanf("%d",&target);
            printf("\n Numero di posizioni: ");
            scanf("%d",&p);
            printf("\n Direzione (1= dx,up,0= sx,down):");
            scanf("%d",&dir);
        }
        ruotaMatrice(dim2,mat,r_o_c,target,dim1,p,dir);
        stampaMatrice(dim2,mat,dim1);

    }while(strcmp(r_o_c,"FINE"));
    return 0;
}
