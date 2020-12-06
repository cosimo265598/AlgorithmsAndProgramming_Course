#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char num[4];
    char parola[15];
} diz;

void compressaParola(char *s, char p[], char t[])
{
    char *pch,app[20];
    pch=strstr(s,p);
    if(strstr(s,p)!=NULL)
    {
        strcpy(app,pch+strlen(p));
        strcpy(pch,t);
        strcat(s,app);
    }

}

void compressaTesto(FILE *fp1,FILE *fp2,FILE *fp3)
{
    char s[15],s1[15];
    char p[15];
    char t[4];
    int i,n,l=0;
    diz parole_sost[30];

    fscanf(fp2,"%d",&n);
    for(i=0;i<n;i++)
        fscanf(fp2,"%s %s",parole_sost[i].num,parole_sost[i].parola);

    while(fscanf(fp1,"%s",s)==1)
    {
        strcpy(s1,s);
        for(i=0;i<n && strcmp(s1,s)==0;i++)
            compressaParola(s,parole_sost[i].parola,parole_sost[i].num);
        l=l+strlen(s)+1;
        if(l<20)
            fprintf(fp3,"%s ",s);
        else
        {
            fprintf(fp3,"\n%s ",s);
            l=0;
        }
    }
}

int main()
{

    FILE *fp1,*fp2,*fp3;

    fp1=fopen("sorgente.txt","r");
    if(fp1==NULL)
        printf("\n Errore file 1");

    fp2=fopen("dizionario.txt","r");
    if(fp2==NULL)
        printf("\n Errore file 2");

    fp3=fopen("compresso.txt","w");
    if(fp3==NULL)
        printf("\n Errore file 3");

    compressaTesto(fp1,fp2,fp3);

    //compressaParola(s,p,"$2");
    return 0;
}
