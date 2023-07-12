======================================== Projet de fou n'ayant aucun nom, mais au final les noms de projet c'est surcoté ======================================================

Compatible Linux, Windows et possiblement mac (ça compile sur windows et linux en tout cas)

Le programme posséde une interface graphique
------------------------ Compiler le programme ------------------------
procédure a suivre : 

1 - Ouvrez CMD
2 - Allez dans le repertoire INDEX 
3 - Compilez-le a l'aide de la séquence suivante
gcc src/main.c src/FonctionTraitement.h src/FonctionTraitement.c src/FonctionTraitementCSV.h src/FonctionTraitementCSV.c -o test.exe -I./include -L./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -std=c99
4 - Enjoy  


---------------------------------------------------------------------- 