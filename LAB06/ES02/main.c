#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 25
// definizione di strutte per allocare liste
typedef struct node *link;

struct node{
    char *s;
    link next;
};

link nuovoNodo(char *st,link next)
{
    link x;
    x=malloc(1*sizeof(link));
    if(x==NULL)
        return NULL;
    x->s=strdup(st);
    x->next=next;
    return x;
}

link inserimentoCoda(link h, char *s)
{
    link x;
    if(h==NULL)
        return nuovoNodo(s,NULL);
    for(x=h; x->next!=NULL;x=x->next);
    x->next=nuovoNodo(s,NULL);
    return h;
}

link splitString(char *s,char sep)
{
    char sp[]="\0";
    char parola[MAXC];
    int i=0;
    int j=0;
    link h=NULL;

    while(s[j]!='\0')
    {
        i++;
        if(s[j]=='.')
        {

            strncpy(parola,s,i-1);
            strcpy(parola+(i-1),sp);
            h=inserimentoCoda(h,parola);
            s=s+i;
            j=j-i;
            i=0;
        }
        j++;
    }
    strcpy(parola,s);
    h=inserimentoCoda(h,parola);
    return h;
}

void stampaLista(link head)
{
    link x;
    printf("\n Head ->");
    for(x=head; x->next!=NULL;x=x->next)
        printf("%s -> ",x->s);
    printf("%s",x->s);
}

int main()
{
    char st[MAXC];
    char sep;
    link head;
    printf("\nInsierisci la stringa divisa da un separatore: ");
    scanf("%s",st);
    printf("\nInsierisci il separatore usato: ");
    scanf("%*c%c",&sep);
    head=splitString(st,sep);
    stampaLista(head);
    return 0;
}
