/**
 Compilation
 gcc --std=c99 -W -Wall -o prixTuring prixTuring.c

 Exécution
 ./prixTuring < turingWinners.txt > out.txt

 Tests
 diff out.txt turingWinners.txt

 Détection de fuites mémoires
 valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./prixTuring < turingWinners.txt > out.txt
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "turingWinners.txt"

/* This function scans a line of text (until \n) and returns a char* that contains all characters on the line (up to 255) excluding \n.
It also ensures the \0 termination.
**WARNING**: The result of this function has been allocated (calloc) by the function */
char* scanLine()
{
	int maxLineSize = 255;
	char c, *line = calloc(maxLineSize+1,sizeof(char));

	scanf("%250[^\n]", line);

	if ( (c = getchar()) != '\n') {
		/* we did not get all the line */
		line[250] = '[';
		line[251] = line[252] = line[253] = '.';
		line[254] = ']';
		// line[255] = '\0'; // useless because already initialized by calloc

		// let's skip all chars untli the end of line
		while (( (c = getchar()) != '\n') && c != EOF) ;
	}

	return line;
}

/* This function scans a line of text (until \n), converts it as an integer and returns this integer */
int scanLineAsInt() {
	int buf;
	scanf("%i\n",&buf);
	return buf;
}

typedef struct {
	int Year;
	char *Name;
	char *Title;
}Winner;

//on veut le tableau de tous les gagnants
typedef struct{
	Winner *winner;  	//un tableau de gagnant
	int size;  			//taille du tableau
}WinnerTab;


WinnerTab *readWinners(){
	//on ne connait pas encore la taille du tableau donc il faut utiliser un malloc
	WinnerTab *TabOfWinners = malloc(sizeof(WinnerTab)); 		//taille du tableau alouée dynamiquement								#Allocation mémoire
	WinnerTab->size  = scanLineAsInt();							//taille du tableau sera égale au nombre de gagnants (50 ici)			#Allocation de tailles de valeures	
	//WinnerTab->winner = malloc(Winnernumber*sizeof(winner)); 	//on multiplie 50 fois le tableau qui contient annee, nom et titre

	for(int i = 0; i<Winnernumber; i++){
		WinnerTab->TabOfWinners.Year =  scanLineAsInt();		//on met un "." car Year est un int
		WinnerTab->TabOfWinners->Name = scanLine();				//on met un "->" car Name est un char*
		WinnerTab->TabOfWinners->Title = scanLine();			//on met un "->" car Title est un char*
	}
	return TabOfWinners;
}

int printWinners(){



	return 0;
}

int main(void)
{

	int nbGagnants = scanLineAsInt();
	printf("nbGagnants = %i\n",nbGagnants);

	for(int i = 0; i<nbGagnants; i++){
		
		int AnneeGagnants = scanLineAsInt();
		printf("AnneeGagnants = %i\n",AnneeGagnants);

		char* NomGagnants = scanLine();
		printf("NomGagnants = %s\n",NomGagnants);
		free(NomGagnants);

		char* TitreGagnants = scanLine();
		printf("TitreGagnants = %s\n",TitreGagnants);
		free(TitreGagnants);
	}
	return EXIT_SUCCESS;
}
