#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Date.h"

void initialiseDate(Date* d){
    int D, Y;
    char M;
    printf("\n Which day? ");
    scanf("%d", &D);
    printf("\n Which month? ");
    scanf("%s", &M);
    printf("\n Which year? ");
    scanf("%d", &Y);
    d->Day = D;
    d->Month = M;
    d->Year = Y;
    printf("\n %d %d %d\n", D, M, Y);
    printf("\n %d %d %d\n", d->Day, d->Month, d->Year);

}

void afficheDate(Date* d){
    printf("The date you have selected is %d  %d  %d\n", *(d->Day),d->Month, d->Year);
}

int main(){
    //printf("Saisissez une date: ")
    Date d;
    //scanf("%d", &d);
    //enum Month_of_year mois;
    //mois = January;
    //printf("\n%d\n", mois);

    initialiseDate(&d);
    afficheDate(&d);
}
