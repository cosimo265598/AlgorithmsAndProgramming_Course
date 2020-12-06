#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 25


typedef struct{
    char *codice;
    char *categoria;
    char *nome;
    float prezzo;
    int disponibile;
    char data[11];
} t_catalogo;

t_catalogo *leggiCatalogo(char *nomefile,t_catalogo *catalogo,int *num){
    FILE *fp=NULL;
    int N=0,i=0;
    char cod[MAXC],cat[MAXC],no[MAXC];

    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(1);

    fscanf(fp,"%d",&N);
    *num=N;
    catalogo=malloc(N*sizeof(t_catalogo));
    if(catalogo==NULL)
        exit(-1);
    while(i<N)
    {
        fscanf(fp,"%s%s%s%f%d%s",cod,no,cat,&catalogo[i].prezzo,&catalogo[i].disponibile,catalogo[i].data);
        catalogo[i].codice=malloc((strlen(cod)+1)*sizeof(char));
        catalogo[i].nome=malloc((strlen(no)+1)*sizeof(char));
        catalogo[i].categoria=malloc((strlen(cat)+1)*sizeof(char));
        strcpy(catalogo[i].codice,cod);
        strcpy(catalogo[i].nome,no);
        strcpy(catalogo[i].categoria,cat);
        i++;
    }

    return catalogo;
}

void stampaCatalogo(int n,t_catalogo *catalogo){
    int i=0;
    while(i<n)
    {
        printf("%s %s %s %.2f %d %s\n",
               catalogo[i].codice,
               catalogo[i].nome,
               catalogo[i].categoria,
               catalogo[i].prezzo,
               catalogo[i].disponibile,
               catalogo[i].data);
        i++;
    }
}

t_catalogo **ordinaPerNome(t_catalogo **elenco,int n){
    t_catalogo *temp=NULL;
    int i=0,j=0,imin=0;
    for(i=0;i<n-1;i++)
    {
        imin=i;
        for(j=i+1;j<n;j++)
            if(strcmp(elenco[j]->nome,elenco[imin]->nome)<0)
                imin=j;
        temp=elenco[i];
        elenco[i]=elenco[imin];
        elenco[imin]=temp;
    }
    return elenco;
}

t_catalogo **ordinaPerCodice(t_catalogo **elenco,int n){
    t_catalogo *temp=NULL;
    int i=0,j=0,imin=0;
    for(i=0;i<n-1;i++)
    {
        imin=i;
        for(j=i+1;j<n;j++)
            if(strcmp(elenco[j]->codice,elenco[imin]->codice)<0)
                imin=j;
        temp=elenco[i];
        elenco[i]=elenco[imin];
        elenco[imin]=temp;
    }
    return elenco;
}

t_catalogo **ordinaPerPrezzo(t_catalogo **elenco,int n, int tipoOrdine){
    t_catalogo *temp=NULL;
    int i=0,j=0,imin=0;
    for(i=0;i<n-1;i++)
    {
        imin=i;
        for(j=i+1;j<n;j++)
        {
            if(tipoOrdine==1)
                if(elenco[j]->prezzo < elenco[imin]->prezzo)
                    imin=j;
            if(tipoOrdine==0)
                if(elenco[j]->prezzo > elenco[imin]->prezzo)
                    imin=j;

        }
        temp=elenco[i];
        elenco[i]=elenco[imin];
        elenco[imin]=temp;
    }
    return elenco;
}

void stampaInOrdine(int n,t_catalogo **elencoOrdinato){
    int i=0;
    while(i<n)
    {
        printf("%s %s %s %.2f %d %s\n",
               elencoOrdinato[i]->codice,
               elencoOrdinato[i]->nome,
               elencoOrdinato[i]->categoria,
               elencoOrdinato[i]->prezzo,
               elencoOrdinato[i]->disponibile,
               elencoOrdinato[i]->data);
        i++;
    }
}

t_catalogo **ordinaPerCategoria(t_catalogo **elenco,int n){
    t_catalogo *temp=NULL;
    int i=0,j=0,imin=0;
    for(i=0;i<n-1;i++)
    {
        imin=i;
        for(j=i+1;j<n;j++)
            if(strcmp(elenco[j]->categoria,elenco[imin]->categoria)<0)
                imin=j;
        temp=elenco[i];
        elenco[i]=elenco[imin];
        elenco[imin]=temp;
    }
    return elenco;
}


int main(int argc,char *argv[])
{
    t_catalogo *catalogo=NULL;
    t_catalogo **elencoPerNome=NULL;
    t_catalogo **elencoPerCodice=NULL;
    t_catalogo **elencoPerPrezzo=NULL;
    t_catalogo **elencoPerCategoria=NULL;
    FILE *fp;
    int num=0,i,scelta;


    // acquisizione da file
    catalogo=leggiCatalogo(argv[1],catalogo,&num);

    // malloc di puntaori a struct
    elencoPerNome=malloc(num*sizeof(t_catalogo*));
    elencoPerCodice=malloc(num*sizeof(t_catalogo*));
    elencoPerPrezzo=malloc(num*sizeof(t_catalogo*));
    elencoPerCategoria=malloc(num*sizeof(t_catalogo*));
    // controllo
    if(elencoPerNome==NULL || elencoPerCodice==NULL
       || elencoPerPrezzo==NULL || elencoPerCategoria==NULL)
        exit(-2);

    for(i=0; i<num; i++)
    {
        elencoPerNome[i]=&catalogo[i];
        elencoPerCodice[i]=&catalogo[i];
        elencoPerPrezzo[i]=&catalogo[i];
        elencoPerCategoria[i]=&catalogo[i];
    }
    // menu comandi
    printf("\n Menu comandi:");
    printf("\n 1 - Contenuto catalogo");
    printf("\n 2 - Ordinamento prezzo");
    printf("\n 3 - Ordinamento nome");
    printf("\n 4 - Ordinamento codice");
    printf("\n 5 - Ordinamento categoria");
    printf("\n Scelta: ");
    scanf("%d",&scelta);
    while(scelta<6 && scelta>0)
    {
        switch(scelta)
        {
            case 1:
                printf("\n Su file o video <1/0>: ");
                scanf("%d",&scelta);
                if(scelta==1)// stampa su file
                {
                    fp=fopen("N_catalogo.txt","w");
                    if(fp==NULL)
                        exit(printf("\n Impossibile scrivere su file"));
                    for(i=0;i<num;i++)
                    {
                        fprintf(fp,"%s %s %s %.2f %d %s\n",
                                   catalogo[i].codice,
                                   catalogo[i].nome,
                                   catalogo[i].categoria,
                                   catalogo[i].prezzo,
                                   catalogo[i].disponibile,
                                   catalogo[i].data);
                    }
                    fclose(fp);
                }
                if(scelta==0)
                {
                    for(i=0; i<num; i++)
                        printf("%s %s %s %f %d %s \n",
                        catalogo[i].codice,
                        catalogo[i].nome,
                        catalogo[i].categoria,
                        catalogo[i].prezzo,
                        catalogo[i].disponibile,
                        catalogo[i].data);
                }
                break;
            case 2:
                printf("\n Ascendente o discendente <1/0>: ");
                scanf("%d",&scelta);
                printf("\n Elenco ordinato per prezzo: \n");
                elencoPerPrezzo=ordinaPerPrezzo(elencoPerPrezzo,num,scelta);
                stampaInOrdine(num,elencoPerPrezzo);
                break;
            case 3:
                printf("\n Elenco ordinato per nome: \n");
                elencoPerNome=ordinaPerNome(elencoPerNome,num);
                stampaInOrdine(num,elencoPerNome);
                break;
            case 4:
                printf("\n Elenco ordinato per codice: \n");
                elencoPerCodice=ordinaPerCodice(elencoPerCodice,num);
                stampaInOrdine(num,elencoPerCodice);
                break;
            case 5:
                printf("\n Elenco ordinato per categoria: \n");
                elencoPerCategoria=ordinaPerCategoria(elencoPerCategoria,num);
                stampaInOrdine(num,elencoPerCategoria);
                break;

        }
        printf("\n Scelta: ");
        scanf("%d",&scelta);
    }

    printf("\nFine ");

    return 0;
}
