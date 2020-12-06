#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCAN 5
#define MAXC 255

typedef struct
{
    char elenco[MAXCAN][MAXC];
    int n_canz;
    int amico;
} Playlist;

Playlist *CanzoniFile(char *nomefile,int *n)
{
    Playlist *brani;
    FILE *fp;
    int i,j,k;
    int n_brani,dim=0;
    char ca[MAXC];

    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(-1);
    // conteggio solamente
    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d",n);

    brani=malloc((*n)*sizeof(*brani));
    for(i=0,k=0;i<*n;i++)
    {
        fscanf(fp,"%d",&n_brani);
        brani[k].amico=i;
        brani[k].n_canz=n_brani;
        for(j=0; j<n_brani; j++)
        {
            fscanf(fp,"%s",ca);
            strcpy(brani[k].elenco[j],ca);
        }
        k++;
    }
    fclose(fp);
    return brani;
}

int princ_molt(int pos, Playlist *val,char sol[][MAXC],int n,int count)
{
    int i;
    if(pos>=n)
    {
        printf("\n***************\n");
        for(i=0;i<n;i++)
        {
            printf("%s \n",sol[i]);
        }
        printf("\n***************\n");
    }
    for(i=0;i<val[pos].n_canz;i++)
    {
        strcpy(sol[pos],val[pos].elenco[i]);
        count=princ_molt(pos+1,val,sol,n,count);
    }
    return count;
}

int main(int argc, char *argv[])
{
    Playlist *album;
    int n;
    int i;
    char mat[MAXCAN][MAXC];

    //Alloco da file i brani con i rispettivi
    album=CanzoniFile(argv[1],&n);
    i=princ_molt(0,album,mat,n,0);
    printf("\nHo trovato : %d \n",i);
    return 0;
}
