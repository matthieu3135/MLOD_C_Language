#include "../V1/linkedList.h"
#include <stdbool.h>


// I keep this lines in case I need it

/*
typedef void* Element;

struct cellule_s {
	Element val;
	struct cellule_s* suiv;
};

typedef struct cellule_s Cellule;

typedef Cellule* Liste;
*/ 

// Music struct
typedef struct{         // Ne connaissant pas la taille de mes tableaux je vais utiliser des pointeurs
    char *name;
    char *artiste;
    char *album;
    char *genre;
    int DiscNumber;
    int TrackNumber;
    int Year;
}Music;

// Definition of functions
extern bool equalsElement(Element e1, Element e2);
extern void detruireElement(Element e);
extern void afficheElement(Element e);