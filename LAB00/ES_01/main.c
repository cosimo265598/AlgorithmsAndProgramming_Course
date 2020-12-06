#include <stdio.h>
#include <stdlib.h>

/** Calcolo del baricentro */

int main()
{
    FILE *fp;
    float x=0,y=0,z=0;
    float sommax=0,sommay=0,sommaz=0;
    int num_i=0;

    fp=fopen("file.txt","r");
    if(fp==NULL)
        return printf("Errore apertura file.txt\n");

    while(fscanf(fp,"%f%f%f",&x,&y,&z)!=EOF)
    {
        sommax=sommax+x;
        sommay=sommay+y;
        sommaz=sommaz+z;
        num_i++;
    }
    printf("Il baricentro e': %.2f  %.2f  %.2f",sommax/num_i,sommay/num_i,sommaz/num_i);
    fclose(fp);
    return 0;
}
