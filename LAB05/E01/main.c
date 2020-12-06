#include <stdio.h>
#include <stdlib.h>

int hofstadter(int n)
{
    if(n==1 || n==2)
        return 1;
    return hofstadter(n - hofstadter(n-1))+hofstadter(n - hofstadter(n-2));
}

int main()
{
    int i=0,a=0;
    printf("\nNumero di termine della serie hofstadter: ");
    scanf("%d",&a);
    for(i=1;i<=a;i++)
        printf("\n %d",hofstadter(i));



    return 0;
}
