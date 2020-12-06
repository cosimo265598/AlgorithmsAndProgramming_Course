#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

float operando(char s[], float precedente)
{
    if(strcmp(s,"PREV")==0)
        return precedente;
    else
        return atof(s);
}

int main()
{
    char num1[MAX+1],num2[MAX+1];
    char op;
    float ris1=0,ris2=0,prec=0;
    int flag=0;

    do
    {
        printf("\n Scrivi un operatore: ");
        scanf("%c%*c",&op);
        if(op=='+' || op=='-'|| op=='*'|| op=='/')
        {
            flag=1;
            printf("\n Scrivi un operando: ");
            scanf("%s",num1);
            ris1=operando(num1,prec);
            printf("\n Scrivi un operando: ");
            scanf("%s",num2);
            ris2=operando(num2,prec);

                    switch(op)
            {
                case '+':
                    prec=ris1+ris2;
                    break;
                case '-':
                    prec=ris1-ris2;
                    break;
                case '*':
                    prec=ris1*ris2;
                    break;
                case '/':
                    if(ris2!=0)
                        prec=ris1/ris2;
                    else
                        printf("\nImpossibile dividere per zero !");
                    break;

            }
            printf("\nRisultato:%f ",prec);
        }
        else
            flag=0;

        scanf("%*c",&op);
    }while(flag==1);





    return 0;
}
