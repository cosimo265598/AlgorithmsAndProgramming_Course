#include <stdio.h>
#include <stdlib.h>
#define MAXRC 20


void leggiMatriceFile(int mat[][MAXRC],int *nr,int *nc)
{
    char nomefile[MAXRC];
    FILE *fp;
    int i=0,j=0;

    printf("\n Nome file input: ");
    scanf("%s",nomefile);
    fp=fopen(nomefile,"r");
    if(fp==NULL)
        return printf("\nErrore apertura file input!");
    fscanf(fp,"%d %d",nr,nc);
    for(i=0;i<*nr;i++)
        for(j=0;j<*nc;j++)
            fscanf(fp,"%d",&mat[i][j]);
    fclose(fp);
}

void stampaMatrice(int mat[][MAXRC],int nr,int nc)
{
    int i=0,j=0;
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
            printf("%d\t",mat[i][j]);
        printf("\n");
    }
    return;
}

int sommaMatrice(int mat[][MAXRC],int nr,int nc,int riga,int colonna,int lato)
{
    int i=0,j=0,k,z,somma=0,raggio=(lato-1)/2;
    for(i=riga,k=0; k<lato ;i++,k++)
        for(j=colonna,z=0; z<lato ;j++,z++)
            if(i<nr && i>=0 && j<nc && j>=0)
                if(k==0 || k==lato-1 || z==0 || z==lato-1)
                    somma=somma+mat[i][j];

    return somma;
}
void elaboraMatrice(int mat[][MAXRC],int nr,int nc,int raggio)
{
    int i=0,j=0,somma=0;
    FILE *fout;
    fout=fopen("Nuova_matrice.txt","w");
    fprintf(fout,"%d %d\n",nr,nc);
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
        {
            somma=sommaMatrice(mat,nr,nc,i-raggio,j-raggio,2*raggio+1);
            fprintf(fout,"%d  ",somma);
        }
        fprintf(fout,"\n");

    }
    fclose(fout);
}

int main()
{
    int mat[MAXRC][MAXRC];
    int nr=0,nc=0,r=0;
    leggiMatriceFile(mat,&nr,&nc);
    /** ritorno con i valori nr e nc aggiornati **/
    printf("\nMatrice acquisita in input:\n");
    stampaMatrice(mat,nr,nc);
    printf("\nDimensione del raggio :");
    scanf("%d",&r);
    elaboraMatrice(mat,nr,nc,r);





    return 0;
}
