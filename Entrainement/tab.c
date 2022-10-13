#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "tab.h"
//using System;

int main(){
    enum couleur c = jaune;
    enum couleur co = rouge;
    //Console.WriteLine(Enum.GetName(typeof(couleur), 1));
    //enum couleur r = (enum couleur)2;
    //char color = ((enum couleur)1).ToString();
    printf("Nous pouvons voir 2 couleurs: %d et %d !\n", c, co);

//ccl:  en C, on ne peux pas retourner la valeur d'un indice d'une enumeration (si jaune = 0, 
//      dans mon int main je ne pourrais afficher que 0 en rentrant jaune, pas jaune en rentrant 0).
}

