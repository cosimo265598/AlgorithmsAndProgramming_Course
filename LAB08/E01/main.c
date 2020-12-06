#include <stdio.h>
#include <stdlib.h>
#define MAX 15

static int scambi=2*MAX;
static int vett[MAX];

int controlla_frecce(int *v,int n)
{
    int i,j=0,k=0,ok=1 ;
    int n_1=0,n_0=0;
    if(v[0]==1)
        return 0;
    for(i=0;i<n;i++)
    {
        if(v[i]==0)
            n_0++;
        if(v[i]==1)
            n_1++;
    }
    if( n_1 == n_0 )
    {
        for(i=0;i<n;i++)
        {
            if(v[i]==0 && v[i+1]==1)
            {
                i=i+1;
                if(v[i+1]==1)
                {
                    ok=0;
                    return 0;
                }
            }
            else
            {
                j=0;
                k=0;
                while(v[i]==0 && i<n)
                {
                    j++;
                    i++;
                }
                while(v[i]==1 && i<n)
                {
                    i++;
                    k++;
                }
                if(k!=j)
                    ok=0;
                else
                    ok=1;
            }

        }
        if(ok==1)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

void VerificaScontri(int *sol,int *ele,int k)
{
    int i,j=0;
    int n_ele[MAX];
    for(i=0;i<k;i++)
        n_ele[i]=ele[i];

    for(i=0;i<k;i++)
    {
        if(sol[i]!=0)
        {
            if(n_ele[i]==0)
                n_ele[i]=1;
            else
                n_ele[i]=0;
            j++;
        }
    }
    if(controlla_frecce(n_ele,k))
    {
        if(j<=scambi)
        {
            scambi=j;
            for(i=0; i<k; i++)
                vett[i]=n_ele[i];
        }
    }
}

void power_set(int pos, int *val,int *sol,int k,int *ele)
{
    if(pos>=k)
    {
        VerificaScontri(sol,ele,k);
        return;
    }
    sol[pos]=0;
    power_set(pos+1,val,sol,k,ele);
    sol[pos]=1;
    power_set(pos+1,val,sol,k,ele);

}

int main()
{
    int *ele;
    int *sol;
    int *val;
    int n=0;
    int i=0;
    char in[MAX];
    //power_set(0,val,sol,4);
    printf("Insieme minimo di frecce da scambiare\n");
    printf("Inserisci come numero elementi, seguito da 0 ed 1:");
    scanf("%s",in);
    n=in[0]-'0';
    /**  CONTROLLO SE N E' PARI poiche
    altrimenti non esitono soluzioni
    e sbilanciato a prescindere  */
    if(n%2!=0)
        exit(printf("\nNon esistono soluzioni"));
    // allocazione dei vettori utili per il power set
    ele=malloc(n*sizeof(int));
    val=malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        ele[i]=in[i+1]-'0';
        val[i]=i;
    }
    sol=malloc(n*sizeof(int));
    // chiamata alla funzione power set
    power_set(0,val,sol,n,ele);
    for(i=0; i<n; i++)
        printf("%d ",vett[i]);
    printf("\n");

    return 0;
}
