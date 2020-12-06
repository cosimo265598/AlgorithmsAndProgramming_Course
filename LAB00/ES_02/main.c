#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

int ConteggioVocali(char s[])
{
    int vocali=0,i=0;
    while(s[i]!='\0')
    {
        if( s[i]=='a' ||s[i]=='e' || s[i]=='i' || s[i]=='o' ||s[i]=='u' || s[i]=='A'|| s[i]=='E' || s[i]=='I' || s[i]=='O' || s[i]=='U')
            vocali++;
        i++;
    }
    return vocali;
}
int main()
{
    FILE *fp,*fp2,*fp3;
    int n,i,sogliavocali;
    char p[MAX],q[MAX];

    fp=fopen("file.txt","r");
    if(fp==NULL)
        printf("Errore di apertura del file.txt \n");
    fp2=fopen("file2.txt","w");
    if(fp==NULL)
        printf("Errore di apertura del file2.txt \n");
    fp3=fopen("file3.txt","w");
    if(fp==NULL)
        printf("Errore di apertura del file3.txt \n");

    fscanf(fp,"%d %s",&n,p);
    sogliavocali=ConteggioVocali(p);
    for (i=0;i<n;i++)
    {
        fscanf(fp,"%s",q);
        if(strcmp(q,p)==1)
            fprintf(fp2,"%s\n",q);
        if(ConteggioVocali(q)>=sogliavocali)
            fprintf(fp3,"%s\n",q);
    }

    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    return 0;
}
