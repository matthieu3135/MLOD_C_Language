#include "raylib.h"
//#include "FenetreAide.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define PLAYER_MAX_LIFE         5
#define LINES_OF_BRICKS         5
#define BRICKS_PER_LINE        20
#define CASES_BONUS             5

static int tableauBonus[CASES_BONUS];


bool IsInside(int element, int tab[], int tabTaille){
    for(int j = 0; j < tabTaille; j++){
        if(element == tab[j]) return true;
    }
    return false;
}


void FillArrayRandomly(){
    /*int bonus;
    bonus = malloc(size*sizeof(int));*/
    for(int i = 0; i<CASES_BONUS; i++ ){
        tableauBonus[i] = rand() % 59; 
        //tableau[i] =   GetRandomValue(1,59);
        /*                     // We create a random integer between 1 and 59 (max(10*numberOfLine + numberOfBricks) = 59)
        while(IsInside(tableauBonus[i], tableauBonus, CASES_BONUS)==1){         // We check that the number is not already present
            tableauBonus[i] = rand() % 59;
            //tableau[i] = GetRandomValue(1,59);
        }*/
    }
}

int estDedans(int x, int tab[], int tailletab){
    for(int i = 0; i<tailletab; i++){
        if(x == tab[i]) return 1;
    }
    return 0;
}


int main(void){
    //tableauBonus = {1, 2, 3, 4, 5};
    /*
    for(int i = 0; i < CASES_BONUS; i++){
        tableauBonus[i] = i; 
        printf("%d\n", tableauBonus[i]);
    }
    */
   /*FillArrayRandomly();
   for(int i = 0; i < 3*CASES_BONUS; i++){ 
        //printf("%d\n", tableauBonus[i]);
        printf("%d\n", rand() % 59 );
        
    }*/
    printf("-------------------------------\n");
    int tableau[30];
    int tab[10];

    for(int i = 0; i<30; i++){
        tableau[i] = rand() % 59;
    }

    for(int j = 0; j<10; j++){
        int l = tableau[rand() % 30];
        int ran = rand() % 30;
        while(estDedans(l, tab, j) == 1){
            l = tableau[ran];
            ran = ran + 1;
        }
        tab[j] = l;
        
        //}
    }
    for(int i = 0; i < 10; i++){ 
        printf("%d\n", tab[i]);
    }
    //printf("------------\n %d\n", tableau[rand() % 30]);
    printf("aaa %d\n", rand());
    int brick[5][20];

    for (int i = 0; i < LINES_OF_BRICKS; i++)
            {
                for (int j = 0; j < BRICKS_PER_LINE; j++)
                {
                    if (brick[i][j].active)
                    {
                        if(((i==3) && (j==5)) || ((i==2) && (j==15))){
                            printf("oui");
                        }
                    }
                }
            }

}