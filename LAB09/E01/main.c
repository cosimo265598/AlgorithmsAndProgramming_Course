#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXC 255

typedef struct{
    char nomeE[MAXC];
    float p,d;
}Esercizio;

typedef struct{
    char nomeC[MAXC];
    int n_e,min,max;
    Esercizio *elenco;
}Categoria;

typedef struct{
    char **tutto;
    int n;
}DRC;

float punt=0;
float diff=0;
char Parz[20][MAXC];

Categoria *InDaFile(char *nomefile,int *n)
{
    Categoria  *mia;
    FILE *fp=NULL;
    int i,m,j,a,b,c;
    float d,e;
    char st[MAXC],st2[MAXC];
    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",&m);
    *n=m;
    mia=malloc(m*sizeof(*mia));
    for(i=0;i<m;i++)
    {
        fscanf(fp,"%s %d %d %d",st,&a,&b,&c);
        strcpy(mia[i].nomeC,st);
        mia[i].n_e=a;
        mia[i].min=b;
        mia[i].max=c;
        mia[i].elenco=malloc(a*sizeof(*mia[i].elenco));
        for(j=0;j<a;j++)
        {
            fscanf(fp,"%s %f %f",st2,&d,&e);
            strcpy(mia[i].elenco[j].nomeE,st2);
            mia[i].elenco[j].p=d;
            mia[i].elenco[j].d=e;
        }

    }
    return mia;
}

void StampaDati(Categoria *mia,int n)
{
    int i=0,j=0;
    for(i=0;i<n;i++)
    {
        printf("\n **** Categoria %s ****",mia[i].nomeC);
        printf("\n N ese %d",mia[i].n_e);
        printf("\n Min %d",mia[i].min);
        printf("\n Max %d",mia[i].max);
        for(j=0;j<mia[i].n_e;j++)
        {
            printf("\n\t %s %.2f %.2f",mia[i].elenco[j].nomeE,
                                        mia[i].elenco[j].p,
                                        mia[i].elenco[j].d);
        }

    }
}

void princ_molt(int pos,DRC *mia,char **sol,int n,int count)
{
    int i,j;
    if(pos>=n)
    {
        if(ControllaSoluzione(sol,n))
        {
            for(i=0;i<n;i++)
                strcpy(Parz[i],sol[i]);
            printf("\nTrovato una soluziona possibile!");
        }
        return;
    }
    for(i=0;i<mia[pos].n;i++)
    {
        // dovrei passare ogni categoria -> disposizioni ripetute
        strcpy(sol[pos],mia[pos].tutto[i]);
        princ_molt(pos+1,mia,sol,n,count);
    }
}

void disp_rip(int pos,Esercizio *val,char **sol,int n,int k,int count,int *j,char **mat)
{
    int i,z;
    float p=0,d=0;
    char sp[10],sd[10];
    if(pos>=k)
    {
        // devo trovare il punteggi complessivo e la difficoltà
        GeneraPuntiDifficolta(val,n,&p,&d,sol,k);
        sprintf(sp," p=%.2f",p);
        sprintf(sd," d=%.2f",d);
        for(i=0;i<k;i++)
        {
            if(k>1)
            {
                if(i==0)
                {
                    strcpy(mat[*j],"\0");
                    strcat(mat[*j],sol[i]);
                    strcat(mat[*j]," ");

                }
                else
                {
                    strcat(mat[*j],sol[i]);
                    strcat(mat[*j]," ");
                }
            }
            else
            {
                strcpy(mat[*j],sol[i]);
                strcat(mat[*j],sp);
                strcat(mat[*j],sd);
                *j=*j+1;
            }
        }
        if(k>1)
        {
            strcat(mat[*j],sp);
            strcat(mat[*j],sd);
            *j=*j+1;
        }
        return ;
    }
    for(i=0;i<n;i++)
    {
        sol[pos]=val[i].nomeE;
        disp_rip(pos+1,val,sol,n,k,count,j,mat);
    }
    return ;
}

DRC generaEserciziDiUnaCategoria(Categoria mia)
{
    int i,j=0,t=0,z=0;
    DRC a;
    char **sol;
    sol=malloc(200*sizeof(char *));
    for(i=0;i<200;i++)
        sol[i]=malloc(MAXC*sizeof(char));
    for(i=mia.min;i<=mia.max;i++)
    {
        z=(int)powf(mia.n_e,i);
        t=t+z;
    }
    a.n=t;
    // creazione matrice di elementi di una singola categoria
    a.tutto=malloc(t*sizeof(char *));
    for(i=0;i<t;i++)
        a.tutto[i]=malloc(MAXC*sizeof(char));

    for(i=mia.min;i<=mia.max;i++)
        disp_rip(0,mia.elenco,sol,mia.n_e,i,0,&j,a.tutto);

    return a;
}


void GeneraPuntiDifficolta (Esercizio *mia,int n,float *p,float *d,char **sol,int k)
{
    int i,j,conta=0;
    const dim=k;
    char st[dim][MAXC];

    for(i=0;i<k;i++)
            strcpy(st[i],sol[i]);
    for(i=0;i<n;i++)
    {
        conta=0;
        for(j=0;j<k;j++)
        {
            if(strcmp(mia[i].nomeE,st[j])==0)
            {
                *p=*p+mia[i].p;
                *d=*d+mia[i].d;
                strcpy(st[j],"\0");
                conta++;
            }
            if(conta>2)
                *p=0;
            if(conta==2)
                *p=mia[i].p-(mia[i].p/2);
        }
    }
    return;
}

int ControllaSoluzione(char **sol,int k)
{
    float p=0,d=0;
    CalcoloDiffPunt(sol,k,&p,&d);
    //printf("\n p=%.2f d=%.2f",p,d);
    if(punt<p && d<=diff)
    {
        punt=p;
        printf("\n p=%.2f d=%.2f",p,d);
        return 1;
    }
    else
        return 0;
}

void CalcoloDiffPunt(char **sol,int k,float *p,float *d)
{
    int i=0,z=0;
    char s[20]="\0";
    char s2[20]="\0";
    char *ps;
    for(i=0;i<k;i++)
    {
        ps=strstr(sol[i],"p=");
        ps=ps+2;
        strcpy(s,ps);
        for(z=0;*ps!=' ';ps=ps+1,z++);
        strncpy(s2,s,z-1);
        *p=*p+atof(s);
        ps=ps+z-1;
        strcpy(s2,"\0");
        strcpy(s,ps);
        for(z=0;*ps!='\0';ps=ps+1,z++);
        strncpy(s2,s,z);
        *d=*d+atof(s);
        strcpy(s2,"\0");
    }
    return;
}

int main(int argc,char *argv[])
{
    Categoria *INSIME_ES=NULL;
    int n,c,i,j,k;
    char **sol;
    char **s;
    DRC *ES;
    float d=0;

    INSIME_ES=InDaFile(argv[1],&n);
    ES=malloc(n*sizeof(*ES));

    sol=malloc(200*sizeof(char *));
    for(i=0;i<200;i++)
        sol[i]=malloc(MAXC*sizeof(char));

    s=malloc(500*sizeof(char *));
    for(i=0;i<500;i++)
        s[i]=malloc(MAXC*sizeof(char));
    printf("\n");

    /////////////////////////*** INIZIO ***/////////////////////////////////////

    for(i=0;i<n;i++)
    {
        ES[i]=generaEserciziDiUnaCategoria(INSIME_ES[i]);
    }
    // generazioni in struttura delle soluzioni parziali
    printf("\nLivello di difficolta: ");
    scanf("%f",&d);
    diff=d;
    princ_molt(0,ES,sol,n,0);
    printf("\n**************** FINE ****************");
    for(i=0;i<n;i++)
        printf("\n %s",Parz[i]);
    printf("\nTotalizzando un punteggio pari a %f : ",punt);
    return 0;
}
