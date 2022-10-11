#include <stdio.h>
#include <stdint.h>

#define Size 9
#define SizeMaxColor 10

char tab[Size][SizeMaxColor] = {    {"Black"},  {"Brown"}, {"Red"}, {"Orange"}, 
                                    {"Yellow"}, {"Green"}, {"Blue"}, {"Purple"}, {"Grey"}, {"White"}};

int main(void){
    //printf("%s \n", tab[5]);
    char x[SizeMaxColor], y = -1;
    printf("\nWrite the color on your Resistor starting with a capital letter: ");
    scanf("%s", x);

    for(int i = 0; i<Size; i++){
        if(tab[i] == x){
            y = i;
            printf("%d", i);
        }
        printf("%d", i);
        printf("%s \n", tab[i]);
        printf("%s \n", x);
    }
    if(y != -1){
        printf("\nYour color is corresponding to %d Ohm \n", y);
    }
    else {printf("\nYou may have entered a wrong color, please try again \n");}
    return 0;
}
