#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_item.h"

struct item
{
    char *name;
    float punt;
};

Item ITEMscan()
{
    char name[MAXC];
    float punt;
    printf("\nPartecipante: ");
    printf("\nname = ");
    scanf("%s", name);
    punt=10;
    Item tmp = (Item) malloc(sizeof(struct item));
    tmp->name = strdup(name);
    tmp->punt = punt;

    return tmp;
}

void ITEMshow(Item data)
{
    printf("name= %s punt= %f \n", data->name, data->punt);
}

Item ITEMchange()
{
    char name[MAXC];
    float punt;
    printf("Enter item to modify: \n");
    scanf("%s", name);
    printf("Enter new priority = ");
    scanf("%f", &punt);
    Item tmp = (Item) malloc(sizeof(struct item));
    tmp->name = strdup(name);
    tmp->punt = punt;
    return tmp;
}
int CMPprio(Item data1, Item data2)
{
    float p1 = GETprio(data1), p2 = GETprio(data2);
    if (p1 < p2) return -1;
    else if (p1 == p2) return 0;
    else return 1;
}
int CMPnomi(Item data1,Item data2)
{
    char p1[MAXC],p2[MAXC];
    strcpy(p1,GETname(data1));
    strcpy(p2,GETname(data2));
    int r=strcmp(p1,p2);
    if(r==0)
        return 1;
    else
        return 0;
}
float GETprio(Item data)
{
    return data->punt;
}
KEYname GETname(Item data)
{
    return data->name;
}
Item CostruisciItem(char *nome, float val)
{
    Item A=(Item) malloc(sizeof(struct item));
    A->name=strdup(nome);
    A->punt=val;
    return A;
}
