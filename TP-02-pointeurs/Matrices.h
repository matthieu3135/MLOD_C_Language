#include <stdint.h>
#include <stdlib.h>
#define SIZE 5

int64_t matrix_mult(int64_t res[SIZE][SIZE],int64_t m1[SIZE][SIZE],int64_t m2[SIZE][SIZE]){
    res = 0*res;   //pas de multiplication, il faut passer par une boucle for
    for(int i = 0; i<SIZE; i++){
        for(int k = 0; k<SIZE; k++){
            res[i][j] = res[i][j] + m1[i][k] * m2[k][i];   // que vaut j
        }

    }
    return res;
}

int64_t matrix_print(int64_t res[SIZE][SIZE]){
    for(int i = 0; i<SIZE; i++){
        printf("%d\n", res[i][:]);  //pas de :
    }
    return 0;
}