#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(char *nomefile,int *nr, int *nc)
{
    int **m;
    FILE *fp=NULL;
    int i=0,j=0,r,c;
    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(printf("\n Errore apertura file"));
    fscanf(fp,"%d %d",&r,&c);
    // alloco la matrice
    m=malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        m[i]=malloc(c*sizeof(int));
    // fine alloco

    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            fscanf(fp,"%d",&m[i][j]);
    *nr=r;
    *nc=c;
    return m;
}

void malloc2dP(int ***mp,int *nr,int *nc,char *nomefile)
{
    int **m;

    FILE *fp=NULL;
    int i=0,j=0,r,c;

    fp=fopen(nomefile,"r");
    if(fp==NULL)
        exit(printf("\n Errore apertura file"));
    fscanf(fp,"%d %d",&r,&c);
    // alloco la matrice
    m=malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        m[i]=malloc(c*sizeof(int));
    // fine alloca

    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            fscanf(fp,"%d",&m[i][j]);

    *nr=r;
    *nc=c;
    *mp=m;
    return;
}

void stampaMatrice(int **m,int r,int c)
{
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
            printf("%d ",m[i][j]);
        printf("\n");
    }
}
int **cercaDiagonali(int n,int r,int **mat,int *vet)
{
    int i,j,riga,colonna,i_diag=0,conta=0,N=r;
    int **diagonali;
    int *n_elementi;
    // prove

    //
    diagonali=malloc((2*N-1)*sizeof(int*));
    n_elementi=malloc((2*N-1)*sizeof(int));
    for(i=0;i<N;i++)
    {
        for(j=N-1;j>=0;j--)
        {
            if(i*j==0)
            {
                if(i<=0)
                {
                    diagonali[i_diag]=malloc((N-j)*sizeof(int));
                    n_elementi[i_diag]=N-j;
                }
                else
                {
                    diagonali[i_diag]=malloc((N-i)*sizeof(int));
                    n_elementi[i_diag]=N-i;
                }
                for(riga=i,colonna=j,conta=0;riga>=0 && riga<N && colonna<N && colonna>=0;riga++,colonna++,conta++)
                    diagonali[i_diag][conta]=mat[riga][colonna];
                i_diag++;
            }
        }
    }
    for(i=0;i<2*N-1;i++)
        vet[i]=n_elementi[i];
    return diagonali;
}

int **cerca_A_Diagonali(int nr,int nc,int **mat,int *vet)
{
    int i,j,riga,colonna,i_diag=0,conta=0,N=nr;
    int **adiagonali;
    int *n_elementi;

    adiagonali=malloc((2*N-1)*sizeof(int*));
    n_elementi=malloc((2*N-1)*sizeof(int));

    for(i=0;i<nr;i++)
    {
        for(j=0;j<nc;j++)
        {
            if(j==0 || i==N-1)
            {
                if(i!=N-1)
                {
                    adiagonali[i_diag]=malloc((i+1)*sizeof(int));
                    n_elementi[i_diag]=i+1;
                }
                else
                {
                    adiagonali[i_diag]=malloc((N-j)*sizeof(int));
                    n_elementi[i_diag]=N-j;
                }
                for(riga=i,colonna=j,conta=0;riga>=0 && riga<N && colonna<N && colonna>=0;riga--,colonna++,conta++)
                    adiagonali[i_diag][conta]=mat[riga][colonna];
                i_diag++;
            }
        }
    }

    for(i=0;i<2*N-1;i++)
        vet[i]=n_elementi[i];
    return adiagonali;
}

void stampaDiagonali(int **diag, int *vet,int dim)
{
    int i=0,j=0;

    for(i=0;i<dim;i++)
    {
        for(j=0;j<vet[i];j++)
        {
            printf("%d ",diag[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int nr,nc;
    int **mat;
    int **diag;
    int **adiag;
    int *vet,*vet2;
    int i;

    mat=malloc2dR(argv[1],&nr,&nc);
    // alternativa di creazione matrice
    // malloc2dP(&mat,&nr,&nc,argv[1]);
    printf("Matrice aquisita dal file %s : \n",argv[1]);
    stampaMatrice(mat,nr,nc);

    // costruzioni matrici diagonali - antidiagonali
    // VET e VET2 vettori di appoggio contenente i
    // vari numeri di valori da stampare
    vet=malloc((2*nr-1)*sizeof(int));
    diag=cercaDiagonali(nr,nc,mat,vet);
    vet2=malloc((2*nr-1)*sizeof(int));
    adiag=cerca_A_Diagonali(nr,nc,mat,vet2);

    // stampe dei risultati
    printf("\nLe diagonali sono :\n");
    stampaDiagonali(diag,vet,2*nr-1);
    printf("\nLe anti-diagonali sono :\n");
    stampaDiagonali(adiag,vet2,2*nr-1);

    return 0;
}
