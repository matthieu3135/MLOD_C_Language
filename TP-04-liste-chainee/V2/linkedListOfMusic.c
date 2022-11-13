#include "linkedListOfMusic.h"
#include <stdbool.h>

/*
On redefinit les fonctions suivantes:

extern bool equalsElement(Element e1, Element e2){}

extern void detruireElement(Element e){} 

extern void afficheElement(Element e){}

*/

bool equalsElement(Element e1, Element e2){
    Music *m1 = (Music *)e1;
    Music *m2 = (Music *)e2;
    return (strcmp(m1->name,m2->name)==0 && strcmp(m1->artiste,m2->artiste)==0 && strcmp(m1->album,m2->album)==0 && strcmp(m1->genre,m2->genre)==0 && strcmp(m1->discNumber,m2->discNumber)==0 && strcmp(m1->annee,m2->annee)==0 && strcmp(m1->trackNumber,m2->trackNumber)==0);
}

void afficheElement(Element v){
    Music* v1=(Music *)v;
    printf("%s ,", v1->name);
    printf("%s ,", v1->artiste);
    printf("%s ,", v1->album);
    printf("%s ,", v1->genre); 
    printf("%s ,", v1->DiscNumber);
    printf("%s ,", v1->TrackNumber);
    printf("%s\n", v1->Year); 
}

void detruireElement(Element v){
    Music* v1=(Music *)v;
    free(v1->name);
    free(v1->album);
    free(v1->genre);
    free(v1->artiste);
    free(v1->DiscNumber);
    free(v1->TrackNumber);
    free(v1->Year);
    free(v1);
}
