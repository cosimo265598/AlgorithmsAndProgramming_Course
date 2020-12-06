#include <stdio.h>
#include <stdlib.h>
#define MAXS 9
#define MAXCOL 10

int **AllocaMatriceFile(char *nome_file, int *n)
{
    int **nM;
    int i,j;
    FILE *fp;

    fp=fopen(nome_file,"r");
    if(fp==NULL)
        exit(-1);

    fscanf(fp,"%d ",n);
    nM = malloc((*n)*sizeof(int*));

    for(i=0;i<*n;i++)
    {
        nM[i]=(int) calloc(MAXCOL,sizeof(int));
        for(j=0;j<MAXCOL;j++)
            fscanf(fp,"%d ",&nM[i][j]);
    }

    return nM;
}

void StampaMatrice(int **M,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<MAXCOL && M[i][j]!=0 ;j++)
            printf("%d ",M[i][j]);
        printf("\n");
    }
}

int comb_sempli(int pos,int *val,int *sol, int n,int k,int start, int count,int **M,int dim)
{
    int i;

    if(pos>=k)
    {
        if(controlla(sol,k,M,dim)) // funzione che verifica se la soluzione
        {
            for(i=0; i<k; i++)
                printf(" S (%d) ",sol[i]);
            printf("\n");
        }
        return count+1;
    }
    for(i=start;i<n;i++)
    {
        sol[pos]=val[i];
        count=comb_sempli(pos+1,val,sol,n,k,i+1,count,M,dim);
    }
    return count;
}

int controlla(int *sol, int k,int **M,int dim)
{
    /**
    Verifico tramite vettore occorenza se la soluzione degli insimei da come
    unione L'insieme U
    */
    int occ[MAXCOL]={1,0,0,0,0,0,0,0,0,0};
    int i,j;
    int pos;

    for( i=0 ,j=0; i<k ;i++ )
    {
        while(M[sol[i]][j]!=0)
        {
            pos=M[sol[i]][j];
            occ[pos]++;
            j++;
        }
        j=0;
    }
    for(i=0;i<MAXS;i++)
    {
        if(occ[i]!=1)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    // L'insime U e' e l'insime dei numeri da 1 a 9
    int **M;
    int *val;
    int *sol;
    int i;
    int k;
    int n=0;

    M=AllocaMatriceFile(argv[1],&n);
    printf("Matrice Aquisita!: \n\n");
    StampaMatrice(M,n);
    // allocazione vettore val che contera il numero degli insiemi
    val=malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        val[i]=i;
    // allocazione del vettore sol
    printf("\n Inserisci k= ");
    scanf("%d",&k);
    sol=malloc(k*sizeof(int));
    for(i=0;i<k;i++)
        sol[i]=0;
    // chiamata della funzione ricorsiva cobinazioni
    i=comb_sempli(0,val,sol,n,k,0,0,M,n);
    printf("\nNumero di combinazioni : %d \n",i);
    printf("\nQuelle che soddisfano le richieste sono quelle riportate su.\n");
    return 0;
}
