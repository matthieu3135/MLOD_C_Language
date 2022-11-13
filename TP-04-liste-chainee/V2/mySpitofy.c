#include <stdio.h>
#include "linkedListOfMusic.h"

#define MAXLINE 2702   //nombre de ligne max du fichier

Music* OneMusic(char* ligne) {
    Music *uneMusique = malloc(sizeof(Music));
    uneMusique->name = strdup(strsep(&ligne, ","));
    uneMusique->artiste = strdup(strsep(&ligne, ","));
    uneMusique->album = strdup(strsep(&ligne, ","));
    uneMusique->genre = strdup(strsep(&ligne, ","));
    uneMusique->DiscNumber = atoi(strsep(&ligne, ","));
    uneMusique->TrackNumber = atoi(strsep(&ligne, ","));
    uneMusique->Year = atoi(strsep(&ligne, ","));

    return uneMusique;
}

Liste readCSV(FILE* f){
    int taille = MAXLINE * sizeof(Music);
    char* ligne =malloc(taille);
    fgets(ligne,taille,f);

}


int main(){
    FILE* f = fopen("music.csv", "r");

}