#ifndef FONCTION_TRAITEMENT_CSV_H
#define FONCTION_TRAITEMENT_CSV_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Window* window;
extern SDL_Window* windowTraitementCSV; // Déclaration de la fenêtre de traitement CSV*
extern SDL_Renderer* rendererTraitementCSV;

void menu_traitementCSV();

#endif /* FONCTION_TRAITEMENT_CSV_H */