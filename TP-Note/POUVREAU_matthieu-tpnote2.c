#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>    //only used for IsEmpty function

#define CHUNK_SIZE_MAX 5


// Struct for String
struct Cellule {
	char chunk[CHUNK_SIZE_MAX];
	struct cellule* next;
};
typedef struct Cellule Cellule;


typedef Cellule* String;


// Function for checking if String is NULL
bool IsEmpty(String l){
    return l == NULL;
}

// Function for creating a String, using a character array
String create(char v[]){

	String l = malloc(sizeof(char));
	
	if(IsEmpty(l)){exit(EXIT_FAILURE);}
    int i = (int)((int)(sizeof(v)/sizeof(v[0])) / 5);
    
    for(int j = 0; j<i; j++){
        int k = 0;
        while(string_length(l->chunk)<5){
	        l->chunk[k] = v[k];
            k++;
        }
        l = l->next;
    }
	return l;
}


// Function for creating a new String
String string_new(char new[]){
    
    String copy = new;

    String p = create(new);
    
    return p;
}


// Function for calculating the length of String
int string_length(String l){
    if(IsEmpty(l)) return 0;
    
    int i = 1;
    while(!IsEmpty(l->next)){
        i = i + 5;                //because there is 5 character per chunk 
        l = l->next;
    }
} 

// Function for destructing a chunk
void detruireChunk(char c[]) {
	free(c);
}

// Function for destructing a String
void detruireString(String l) {
	
	String suivant, courant = l;
	while(!IsEmpty(courant)){
		suivant = courant->next;
		detruireChunk(courant->chunk);
		free(courant);
		courant = suivant;
	}
}

int main(void){
    char s[] = "HELLO !";
    //String s = string_new("HELLO !");
    printf("%s\n", s);
    //detruireString(s);
}