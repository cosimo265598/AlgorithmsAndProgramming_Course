#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

float valutaHorner(float P[MAX+1], float x)
{
    int i=MAX+1;
    float val=0;
    val=P[i]*x+P[i-1];
    for(i=(MAX+1)-2;i>0;i--)
    {
        val=val*x+P[i-1];
    }
    return val;
}
void azzeramentoVettore(float vet[MAX+1])
{
    int i;
    for(i=0;i<MAX+1;i++)
        vet[i]=0;
}
/**
float calcoloIntegrale(int inf,int sup,float val[MAX+1],int m)
{
    float intervallo=(sup-inf)/m ,integrale=0;

    for(inf=(inf+intervallo)/2; inf<sup ; inf=inf+intervallo)
        integrale=integrale+valutaHorner(val,inf)*intervallo;

    return integrale;
}*/

int main()
{
    float intervallo;
    float a,b;
    int n,m;
    int i;
    float valori[MAX+1],integrale=0;
    printf("\nInserisci il grado del polinomio p(x) (Grado <=10): ");
    scanf("%d",&n);
    printf("\nEstremi di integrazione [a b] : ");
    scanf("%f %f",&a,&b);
    printf("\nNumero dei sottointervalli: ");
    scanf("%d",&m);
    azzeramentoVettore(valori);
    /** rimepimento con coefficienti del polinomio */
    for(i=0;i<=n;i++)
    {
        printf("Inserisci il termine a%d: ",i);
        scanf("%f",&valori[i]);
    }
    /** ampiezza dei vari sotto intervalli */

    intervallo=(b-a)/m;
    for(a=(a+intervallo)/2;a<b;a=a+intervallo)
        integrale=integrale+valutaHorner(valori,a)*intervallo;

    //integrale=calcoloIntegrale(a,b,valori,m);

    printf("\nIntegrale vale %.2f con %d sottointervalli",integrale,m);
    return 0;
}
