#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 35
#define INV1 5
#define INV2 6
#define ELEM 3

typedef struct
{
    char nome[MAXC];
    char cat[MAXC];
    int dim1,dim2,u;
}ITEM;

ITEM *DaFile(char *nomefile,int *k)
{
    ITEM *ogg;
    FILE *fp;
    int i,n,dim1,dim2,u;
    char s[MAXC];
    char s2[MAXC];
    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",&n);
    *k=n;
    ogg=malloc(n*sizeof(*ogg));
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%s %s %d %d %d",s,s2 ,&ogg[i].dim1,&ogg[i].dim2,&ogg[i].u);
        strcpy(ogg[i].nome,s);
        strcpy(ogg[i].cat,s2);
    }
    return ogg;
}

int controllaSoluzione(ITEM *items,int *sol,int k)
{
    char equiImp[ELEM][MAXC]={"pozione","arma","armatura"};
    int occ[ELEM],i,j,ok=1;
    for(i=0;i<ELEM;i++)
        occ[i]=0;
    for(i=0;i<k;i++)
    {
        if(sol[i]!=0)
        {
            for(j=0;j<ELEM;j++)
            {
                if(strcmp(items[i].cat,equiImp[j])==0)
                    occ[j]++;
            }
        }
    }
    for(i=0;i<ELEM && ok;i++)
        if(occ[i]==0)
            ok=0;
    if(ok)
        return 1;
    else
        return 0;
}

void powerset(int pos,ITEM *items,int *sol,int k,int cap,int curr_cap,int curr_value,int *best_val,int *best_sol)
{
    int j;
    if(pos>=k)
    {
        if(controllaSoluzione(items,sol,k))
        {
            if(curr_value > *best_val)
            {
                for(j=0;j<k;j++)
                {
                    best_sol[j]=sol[j];
                }
                *best_val=curr_value;
            }

        }
        return;
    }
    if((curr_cap+(items[pos].dim1*items[pos].dim2))<cap)
    {
        sol[pos]=1;
        curr_cap+=items[pos].dim1*items[pos].dim2;
        curr_value+=items[pos].u;
        powerset(pos+1,items,sol,k,cap,curr_cap,curr_value,best_val,best_sol);
        curr_cap-=items[pos].dim1*items[pos].dim2;
        curr_value-=items[pos].u;
    }
    sol[pos]=0;
    powerset(pos+1,items,sol,k,cap,curr_cap,curr_value,best_val,best_sol);

}


int main(int argc,char *argv[])
{
    int i,k,cap,*sol,*best_sol,best_value=0;
    ITEM *oggetto;
    oggetto=DaFile(argv[1],&k);
    sol=malloc(k*sizeof(int));
    best_sol=malloc(k*sizeof(int));
    for(i=0;i<k;i++)
    {
        sol[i]=0;
        best_sol[i]=0;
    }
    cap=INV1*INV2;
    powerset(0,oggetto,sol,k,cap,0,0,&best_value,best_sol);
    printf("\nLa soluzione e': \n {");
    for(i=0;i<k;i++)
    {
        if(best_sol[i]!=0)
            printf("\n %s",oggetto[i].nome);
    }
    printf("\n } \n");
    printf("\nL'utilita' e pari a: %d ",best_value);

    return 0;
}
