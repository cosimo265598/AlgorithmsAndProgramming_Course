#include <stdio.h>
#include <stdlib.h>

void binarioBaseB(int N, int B)
{
    if(N==0)
        return;
    binarioBaseB(N/B,B);
    printf("%d",N%B);
}

int main()
{
    int n,b;

    printf("\nInserisci il numero in base 10: ");
    scanf("%d",&n);
    printf("\nBase di destinazione: ");
    scanf("%d",&b);
    printf("\n");
    binarioBaseB(n,b);

    return 0;
}
