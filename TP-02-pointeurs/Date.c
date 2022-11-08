#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Date.h"

void initialiseDate(Date* d){
    int D, Y;
    char M;
    printf("\n Which day? ");
    scanf("%d", &(d->Day));
    printf("\n Which month? ");
    scanf("%s", (*d).Month);
    printf("\n Which year? ");
    scanf("%d", &d->Year);
    //d->Day = D;
    
    //d->Year = Y;
    //printf("\n %d %d %d\n", D, M, Y);
    printf("\n %d %d %d\n", d->Day, d->Month, d->Year);

}

void afficheDate(Date* d){
    printf("The date you have selected is %d  %d  %d\n", d->Day,d->Month, d->Year);
}

int main(){
    //printf("Saisissez une date: ")
    Date d;
    //scanf("%d", &d);
    //enum Month_of_year mois;
    //mois = January;
    //printf("\n%d\n", mois);
    d.Month = January;
    printf("%d \n", d.Month);

    initialiseDate(&d);
    afficheDate(&d);
}
