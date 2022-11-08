#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 5

int64_t matrix_mult(int64_t res[SIZE][SIZE],int64_t m1[SIZE][SIZE],int64_t m2[SIZE][SIZE]){
    //res = 0*res;   //pas de multiplication, il faut passer par une boucle for
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            res[i][j] = 0;
        }  
    }
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            for(int k = 0; k<SIZE; k++){
                res[i][j] = res[i][j] + m1[i][k] * m2[k][i];   // que vaut j
            }
        }

    }
    return res;
}

int64_t matrix_print(int64_t res[SIZE][SIZE]){
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            printf("%d",res[i][j]);
            printf(j<SIZE-1? "\t" : "\n"); //si j<SIZE-1 alors on met un espace, si j = SIZE (dernière valeure), alors retour à la ligne
        }
        //printf("%d\n", res[i][:]);  //pas de :
    }
    return 0;
}