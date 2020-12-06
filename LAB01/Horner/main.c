#include <stdio.h>
#include <stdlib.h>

int main()
{
   int vet[4]={-2,1,-2,0};
   int vet2[4]={0,0,0,0};
   int x=3;
   int i=2,val=1,temp;
   /**
   for(i=3;i>0;i--)
   {
       val=vet[i]*x+vet[i-1];
       vet[i-1]=val;
   }
   printf("%d",val);
    **/
    val=vet[i]*x+vet[i-1];
    for(i=1;i>0;i--)
    {
        val=val*x+vet[i-1];
    }
    printf("%d",val);

   return 0;
}
