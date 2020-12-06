#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 30
#define MAXN 1000

typedef enum{
r_nome, r_IP, r_rifiuto, r_risorse, r_fine, r_err
} comando_e;

typedef struct{
    char ip[MAXC];
    char user[MAXC];
    char timestamp[MAXC];
    char richiesta[MAXC];
    char risorsa[MAXC];
    char risposta[MAXC];
}LOG;

int leggiTabella(LOG tabella[],int maxrighe)
{
    FILE *fin;
    int i=0,n;
    fin=fopen("accessi.txt","r");
    if(fin==NULL)
        return -1;
    fscanf(fin,"%d",&n);
    while(fscanf(fin,"%s%s%s%s%s%s",tabella[i].ip,tabella[i].user,
                 tabella[i].timestamp
                 ,tabella[i].richiesta,tabella[i].risorsa,
                 tabella[i].risposta)==6 && i<MAXN)
        i++;

    return i;
}
void stampaDati(LOG tabella[],int nrighe)
{
    int i=0;
    for(i=0;i<nrighe;i++)
    {
        printf("%s %s %s %s %s %s \n",tabella[i].ip,tabella[i].user,
                 tabella[i].timestamp
                 ,tabella[i].richiesta,tabella[i].risorsa,
                 tabella[i].risposta);
    }
}

void stringaToLower(char *s)
{
    while(*s!='\0')
    {
        *s=tolower(*s);
        s++;
    }
}

comando_e leggiComando()
{
    char s[MAXC];
    comando_e c;
    char *tabcomandi[r_err]={"nome","ip","rifiuto","risorsa","fine"};
    printf("\nComando (nome/ip/rifiuto/risorsa/fine): ");
    scanf("%s",s);
    stringaToLower(s);
    c=r_nome;
    while(c<r_err && strcmp(s,tabcomandi[c])!=0)
        c++;
    return c;
}

void selezionaDati(LOG tabella[],int ndati,comando_e cmd)
{
    switch(cmd)
    {
        case r_nome: selezionaNome(tabella,ndati);
            break;
        case r_IP: selezionaIp(tabella,ndati);
            break;
        case r_rifiuto: selezionaRisposta(tabella,ndati);
            break;
        case r_risorse: selezionaRisorse(tabella,ndati);
            break;
    }
    return;
}

void menuElaborazione(LOG tabella[],int ndati)
{
    comando_e cmd;
    int continua=1;
    while(continua==1)
    {
        cmd=leggiComando();
        switch(cmd)
        {
            case r_nome: selezionaDati(tabella,ndati,cmd);
                break;
            case r_IP: selezionaDati(tabella,ndati,cmd);
                break;
            case r_rifiuto: selezionaDati(tabella,ndati,cmd);
                break;
            case r_risorse: selezionaDati(tabella,ndati,cmd);
                break;
            case r_fine:continua=0;
                break;
            default: printf("\nComando errato!");
        }
    }
}
void selezionaNome(LOG tabella[],int ndati){
    char data1[MAXC],data2[MAXC],confronto[MAXC];
    int i=0;
    printf("\nInserisci l'intervallo delle date (gg/mm/aaaa): ");
    scanf("%s %s",data1,data2);
    formatoData(data1);
    formatoData(data2);
    for(i=0;i<ndati;i++)
    {
        strcpy(confronto,tabella[i].timestamp);
        strcpy(confronto+10,"\0");
        formatoData(confronto);
        if(strcmp(data1,confronto)<0 && strcmp(confronto,data2)<0)
            printf("%s\n",tabella[i].user);
    }

}

void selezionaIp(LOG tabella[],int ndati){
    char data1[MAXC],data2[MAXC],confronto[MAXC];
    int i=0;
    printf("\nInserisci l'intervallo delle date (gg/mm/aaaa): ");
    scanf("%s %s",data1,data2);
    formatoData(data1);
    formatoData(data2);
    for(i=0;i<ndati;i++)
    {
        strcpy(confronto,tabella[i].timestamp);
        strcpy(confronto+10,"\0");
        formatoData(confronto);
        if(strcmp(data1,confronto)<0 && strcmp(confronto,data2)<0)
            printf("%s\n",tabella[i].ip);
    }

}

void selezionaRisposta(LOG tabella[],int ndati){
    char data1[MAXC],data2[MAXC],confronto[MAXC];
    int i=0;
    for(i=0;i<ndati;i++)
    {
        if(strcmp(tabella[i].risposta,"401")==0)
            printf("%s\n",tabella[i].user);
    }

}

void selezionaRisorse(LOG tabella[],int ndati)
{
        char data1[MAXC],data2[MAXC],confronto[MAXC];
    int i=0;
    printf("\nInserisci l'intervallo delle date (gg/mm/aaaa): ");
    scanf("%s %s",data1,data2);
    formatoData(data1);
    formatoData(data2);
    for(i=0;i<ndati;i++)
    {
        strcpy(confronto,tabella[i].timestamp);
        strcpy(confronto+10,"\0");
        formatoData(confronto);
        if(strcmp(data1,confronto)<0 && strcmp(confronto,data2)<0)
            printf("%s\n",tabella[i].risorsa);
    }


}

void formatoData(char *s)
{
    int gg,mm,aa;
    char s1[20]="";
    s=s+6;
    strcat(s1,s);
    s--;
    strcpy(s,"\0");
    strcat(s1,"/");
    s=s-2;
    strcat(s1,s);
    s--;
    strcpy(s,"\0");
    strcat(s1,"/");
    s=s-2;
    strcat(s1,s);
    strcpy(s,s1);
}
int main()
{
    LOG tabella[MAXN];
    int ndati=0;
    char s[MAXC]="13/12/2016";
    ndati=leggiTabella(tabella,MAXN);
    stampaDati(tabella,ndati);
    menuElaborazione(tabella,ndati);

    return 0;
}
