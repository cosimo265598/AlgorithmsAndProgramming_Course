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
    int stato;
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
        catalogo[i].stato=1;
        i++;
    }

    return catalogo;
}

void stampaCatalogo(int n,t_catalogo *catalogo){
    int i=0;
    while(i<n)
    {
        if(catalogo[i].stato==1)
        {
            printf("%s %s %s %.2f %d %s\n",
                   catalogo[i].codice,
                   catalogo[i].nome,
                   catalogo[i].categoria,
                   catalogo[i].prezzo,
                   catalogo[i].disponibile,
                   catalogo[i].data);
        }
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
        if(elencoOrdinato[i]->stato==1)
        {
            printf("%s %s %s %.2f %d %s\n",
                   elencoOrdinato[i]->codice,
                   elencoOrdinato[i]->nome,
                   elencoOrdinato[i]->categoria,
                   elencoOrdinato[i]->prezzo,
                   elencoOrdinato[i]->disponibile,
                   elencoOrdinato[i]->data);
        }
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

t_catalogo *inserimentoInCatalogo(t_catalogo *catalogo, int *dim_catalogo,int *new_dim)
{
    t_catalogo *nuovocat;
    t_catalogo elemento;
    char st[MAXC];
    int a=0;
    nuovocat=catalogo;
    if( (*dim_catalogo) >= (*new_dim) )
    {
        nuovocat=realloc(catalogo,(2*(*dim_catalogo))*sizeof(t_catalogo));
        *new_dim=2*(*dim_catalogo);
    }
    printf("\nCod: ");
    scanf("%s",st); elemento.codice=strdup(st);
    printf("\nNome: ");
    scanf("%s",st); elemento.nome=strdup(st);
    printf("\nCategoria: ");
    scanf("%s",st); elemento.categoria=strdup(st);
    printf("\nPrezzo: ");
    scanf("%f",&elemento.prezzo);
    printf("\nDisponibile: ");
    scanf("%d",&elemento.disponibile);
    printf("\nData: ");
    scanf("%s",elemento.data);
    elemento.stato=1;
    nuovocat[*dim_catalogo]=elemento;
    *dim_catalogo=*dim_catalogo+1;

    return nuovocat;
}
t_catalogo **CancellazioneLogica(t_catalogo **elenco, int dim)
{
    t_catalogo **agg_catalogo;
    int i=0;
    char st[MAXC];
    agg_catalogo=elenco;
    printf("\nInserisci il codice prodotto come <codXXXXXX> : ");
    scanf("%s",st);
    for(i=0;i<dim && strcmp(agg_catalogo[i]->codice,st)<=-1;i++);
    agg_catalogo[i]->stato=0;
    return agg_catalogo;
}

int main(int argc,char *argv[])
{
    t_catalogo *catalogo=NULL;
    t_catalogo **elencoPerNome=NULL;
    t_catalogo **elencoPerCodice=NULL;
    t_catalogo **elencoPerPrezzo=NULL;
    t_catalogo **elencoPerCategoria=NULL;
    FILE *fp;
    int num=0,i,scelta,num_dim=0;

    // acquisizione da file
    catalogo=leggiCatalogo(argv[1],catalogo,&num);
    // serve per la dimensione corrente e vecchia del catalogo
    num_dim=num;
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
    printf("\n ** Menu comandi: **");
    printf("\n 1 - Contenuto catalogo");
    printf("\n 2 - Ordinamento prezzo");
    printf("\n 3 - Ordinamento nome");
    printf("\n 4 - Ordinamento codice");
    printf("\n 5 - Ordinamento categoria");
    printf("\n 6 - Inserimento prodotto");
    printf("\n 7 - Cancellazione prodotto");
    printf("\n Scelta: ");
    scanf("%d",&scelta);
    while(scelta<8 && scelta>0)
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
            case 6:
                catalogo=inserimentoInCatalogo(catalogo,&num,&num_dim);
                break;
            case 7:
                elencoPerCodice=CancellazioneLogica(elencoPerCodice,num);
                break;

        }
        printf("\n Scelta: ");
        scanf("%d",&scelta);
    }

    printf("\nFine ");

    return 0;
}
