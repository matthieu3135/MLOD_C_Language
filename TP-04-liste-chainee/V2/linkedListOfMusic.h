#include "../V1/linkedList.h"

typedef void* Element;

struct cellule_s {
	Element val;
	struct cellule_s* suiv;
};

typedef struct cellule_s Cellule;

typedef Cellule* Liste;

struct Music{
    char Name[];
    char Artiste[];
    char Album[];
    char Genre[];
    int DiscNumber;
    int TrackNumber;
    int Year;
};