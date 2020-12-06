#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "_item.h"
#include "_PQ.h"

void InsManuale()
{
    Item tmp;
    int i,n;
    printf("\nQuanti elemnti vuoi inserire: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        tmp=ITEMscan();
        InserimentoPQ(tmp);
    }
}

void EliminaPartecipante()
{
    Item tmp;
    char st[MAXC];
    float p;
    printf("\nNome patecipante: ");
    scanf("%s",st);
    p=0;
    tmp=CostruisciItem(st,p);
    EliminaItemPQ(tmp);
}

void SfidaPatecipanti()
{
    Item par1,par2;
    int r1=rand()%100;
    int r2=rand()%100;
    float p1=0;
    float p2=0;
    float bonus=0;
    char st[MAXC];
    par1=estraiMinPQ();
    par2=estraiMinPQ();
    printf("\nSi sfidano : %s  vs  %s",GETname(par1),GETname(par2));
    if(r1>=r2)
    {
        // primo partecipante vincente e il secondo perde
        p2=GETprio(par2);
        strcpy(st,GETname(par2));
        bonus=((25*p2)/100);
        p2=p2-bonus;
        if(p2==0)
            EliminaItemPQ(par2);
        par2=CostruisciItem(st,p2);
        InserimentoPQ(par2);
        p1=GETprio(par1);
        strcpy(st,GETname(par1));
        p1=p1+bonus;
        par1=CostruisciItem(st,p1);
        InserimentoPQ(par1);
        printf("\nHa vinto : %s",GETname(par1));
    }
    else
    {
        // secondo partecipante vincente e il primo perde
        p1=GETprio(par1);
        strcpy(st,GETname(par1));
        bonus=((25*p1)/100);
        p1=p1-bonus;
        if(p1==0)
            EliminaItemPQ(par1);
        par1=CostruisciItem(st,p1);
        InserimentoPQ(par1);
        p2=GETprio(par2);
        strcpy(st,GETname(par2));
        p2=p2+bonus;
        par2=CostruisciItem(st,p2);
        InserimentoPQ(par2);
        printf("\nHa vinto : %s",GETname(par2));

    }
}

int menu()
{
    int s=0;
    printf("\n************ Menu ************");
    printf("\n1. stampa classifica");
    printf("\n2. inserimento partecipante");
    printf("\n3. eliminazione partecipante");
    printf("\n4. singola sfida");
    printf("\n5. carica dati da file");
    printf("\n6. salva dati su fie");
    printf("\n7. fine");
    printf("\nScelta: ");
    scanf("%d",&s);
    return s;
}

int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));
    int s;
    s=menu();
    while(s!=7)
    {
        switch(s)
        {
            case 1:
                StampaPQ();
                break;
            case 2:
                InsManuale();
                break;
            case 3:
                EliminaPartecipante();
                break;
            case 4:
                SfidaPatecipanti();
                break;
            case 5:
                caricaDaFilePQ(argv[1]);
                break;
            case 6:
                stampaSuFilePQ();
            default:
                break;
        }
        s=menu();
    }
    return 0;
}
