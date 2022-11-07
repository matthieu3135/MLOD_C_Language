#include <stdio.h>

int tableau (int t1[]){
    int taille = 0;
    int taille1 = ((int)sizeof(t1)/((int)sizeof(t1[0])));  //size of array divide by size of a cell = number of cells
    
    for(int i =0; i < taille1; i++){  
        taille = taille + t1[i];
    }
    return taille;
}

//int resultat[tableau(t1)]; //declaration of the length of our resultat Array

int repeat(int t1[], int t2[]){
    
    int t = 0;
    for(int g = 0; g < taille1; g++){
        for(int i = 0; i < t1[g]; i++){  // we fill the resultat Array
            resultat[t] = t2[g];
            t = t+1;
        }
    }
}

int main(void){
    

    int t1[] = {1, 2, 4};
    int t2[] = {10, 3, 8};
    int resultat[tableau(t1)]; //declaration of the length of our resultat Array
    printf(repeat(t1, t2));
    //printf(((int)sizeof(repeat(t1, t2))/((int)sizeof(repeat(t1, t2)[0]))));
}