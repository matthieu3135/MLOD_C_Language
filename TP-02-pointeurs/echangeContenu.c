#include <stdio.h>
#include <stdint.h>


uint16_t a = 10;
uint16_t b =20;

int echangeContenu(void){
    uint16_t i = a;
    a = b;
    b = i;
}

int main(void){
    printf("\n Avant échange: a = %d, and b = %d", a, b);
    echangeContenu();
    printf("\n Après échange: a = %d, and b = %d \n", a, b);
}