Ce mini-Projet a pour but de modifier un jeu en lui ajoutant des caractéristiques.

Je souhaite modifier le jeu Arkanoid de la bibliohèque Raylib (https://www.raylib.com/games.html)

# Description du projet
- Le Jeu: Arkanoid
- Les Modifications:   
	`*Afficher un menu avec les touches`  
	`*Afficher les scores`  
	`*Mettre de la couleur (les vies en vert, lorsqu'il reste plus que deux vies, elles sont en rouge. De même, des couleurs sur les cases)`  
	`*Ajouter des touches (les numéros du clavier par example ou une seule touche)  pour augmenter la vitesse du curseur`  
	`*ajouter des bonus (pour 15 cases cassées en un coup, une vie gagnée)`   

# Comment compiler

gcc -Wall -std=c11 arkanoid.c /home/bot/Raylib.git/src/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11 -o arkanoid

# Comment exécuter

./arkanoid

# Comment utiliser le projet

Vous avez 5 vies. Le but est de détruire tous les carrés à l'aide d'une balle.
Il y a 2 fenêtres, une avec les explications pour jouer, et une avec le jeu.

# URL vidéo de démo

# Quelques détails sur votre implémentation
quel(s) fichier(s), structures de données, algorithme, ...

# Extensions / améliorations possibles

En fonction de l'avancement, une possibilité d'amélioration sera d'ajouter des cases bonus  
Par exemple:  
	*case bleu: duplique la balle avec un temps d'intervalle (cela met 2 balles en jeu)  
	*case orange: permet d'avoir un support (ce qui tape la balle) 2 fois plus gros, mais un peu plus lent  
	*case verte: une case serait présente dans le jeu et rajoute une vie (5 vies max)  
Remarque: les cases seront réparties de façon aléatoires et leur emplacement differera donc d'une partie à l'autre
