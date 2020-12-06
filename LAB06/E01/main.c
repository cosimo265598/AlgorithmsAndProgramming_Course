#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXS 11 /* 10 + 1 per '\0' */

// Definizione delle strutture dati usate
typedef struct nodo* link;

struct nodo {
  char val[MAXS];
  link left;
  link right;
};

// Prototipi delle funzioni di utilità
link new_nodo(char *val);
link leggi_nodo(FILE *in);
link leggi_albero(char *filename);
void libera_albero(link root);
void display_albero(link root);

// Prototipi delle funzioni da implementare
//int distanza(link n, char *k1, char *k2);
int contaCompleti(link n, int L1, int L2,int *LC);
void distanzaRF(link n,char *k,int *n_a);
link nodo_comune(link n, char *k1, char *k2);
int distanza(link n, char *k1, char *k2);



int main(int argc, char **argv)
{

    link root;
    int c=0;
    int d=0;
    int l1,l2;
    char k1[MAXS];
    char k2[MAXS];
    root = leggi_albero(argv[1]);
    display_albero(root);

    // invocazione delle funzioni richieste
    printf("\nConta nodi con due figli tra due livelli\n\n");
    printf("\nInserisci Livello 1 Livello2 : ");
    scanf("%d %d",&l1,&l2);
    c=contaCompleti(root,l1,l2,&d);
    printf("\n%d",c);

    printf("\nInserisci il nome dei due nodi: ");
    scanf("%s %s ",k1,k2);
    c=distanza(root,k1,k2);
    printf("\nDistanza %d ",c);

    libera_albero(root);
    return 0;
}

// Implementazione delle funzioni di utilità

link new_nodo(char *val) {
    link n = malloc(1*sizeof(*n));
    strcpy (n->val,val);
    n->left = NULL;
    n->right = NULL;
    return n;
};

void display_albero(link root) {
    if (root == NULL) return;
    printf("nodo %s\n", root->val);
    display_albero(root->left);
    display_albero(root->right);
}

void libera_albero(link root) {
    if (root == NULL) return;
    libera_albero(root->left);
    libera_albero(root->right);
    free(root);
}

link leggi_nodo(FILE *in) {
    char val[MAXS];
    int l, r;
    if (fscanf(in, "%s %d %d", val, &l, &r) != 3) return NULL;
    link n = new_nodo(val);
    if (l!=0) n->left = leggi_nodo(in);
    if (r!=0) n->right = leggi_nodo(in);
    return n;
}

link leggi_albero(char *filename) {
    FILE *in;
    in = fopen(filename, "r");
    link root = leggi_nodo(in);
    fclose(in);
    return root;
}

// Implementazione delle funzioni da aggiungere

int contaCompleti(link n, int L1, int L2,int *LC) {
    int count;
    if (n == NULL)
        return 0;

    *LC=*LC+1;
    count=contaCompleti(n->left,L1,L2,LC);
    count=contaCompleti(n->right,L1,L2,LC);
    *LC=*LC-1;

    if(n->left != NULL && n->right!=NULL)
    {
        if(*LC<=L2 && *LC>=L1){
            printf("nodo %s\n", n->val);
            count++;
        }
    }
    return count;
}

int distanza(link n, char *k1, char *k2)
{
    int dist_n=0,dist_n1=0;
    int dist_2_nodi=0;
    link n_comune=NULL;
    n_comune=nodo_comune(n,k1,k2);

    distanzaRF(n_comune,k1,&dist_n);
    distanzaRF(n_comune,k2,&dist_n1);
    return dist_2_nodi=(dist_n1-1)+(dist_n-1);
}

link nodo_comune(link n, char *k1, char *k2)
{
    if((strcmp(k1, n->val)<=0 && strcmp(k2, n->val)>=0)||
       (strcmp(k1, n->val)>=0 && strcmp(k2, n->val)<=0))
     return n;
    else if((strcmp(k1, n->val)<0) && (strcmp(k2, n->val)<0))
            n= nodo_comune(n->left, k1, k2);
    else if((strcmp(k1, n->val)>0) && (strcmp(k2, n->val)>0))
            n= nodo_comune(n->right, k1, k2);
    return n;
}
void distanzaRF(link n,char *k,int *n_a)
{
    if(n==NULL)
        return;
    *n_a=*n_a+1;
    if(strcmp(n->val,k)==0)
    {
        return;
    }

    if(strcmp(n->val,k)>0)
        distanzaRF(n->left,k,n_a);

    if(strcmp(n->val,k)<0)
        distanzaRF(n->right,k,n_a);

    return;
}
