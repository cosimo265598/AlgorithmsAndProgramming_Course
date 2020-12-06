#ifndef _ITEM_H_INCLUDED
#define _ITEM_H_INCLUDED

#define MAXC 10

typedef struct item* Item;
typedef char* KEYname;
Item ITEMscan();
Item ITEMsetvoid();
void ITEMshow(Item data);
Item ITEMchange();
int CMPprio(Item data1, Item data2);
float GETprio(Item data);
KEYname GETname(Item data);
Item CostruisciItem(char *nome, float val);


#endif // _ITEM_H_INCLUDED
