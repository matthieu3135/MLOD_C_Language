#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Mois represented by an enumeration
enum Month_of_year {
    January = 1, 
    February, 
    March, 
    April, 
    May, 
    June, 
    July, 
    August, 
    September, 
    October, 
    November, 
    December
};

typedef struct{
    int Day;
    enum Month_of_year Month;
    int Year;
} Date;


