#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include "fonctionTraitementCSV.h"

SDL_Window* windowTraitementCSV = NULL;
SDL_Renderer* rendererTraitementCSV = NULL;
SDL_Texture* backgroundTextureTraitementCSV;
SDL_Rect buttonMenu1Rect;
SDL_Texture* buttonMenu1Texture = NULL;

#define WINDOW_WIDTH 1333
#define WINDOW_HEIGHT 1000

int buttonMenu1State = 0;

void loadTexturesMenu_Traitement()
{
    // Charger les textures depuis les fichiers d'images
    backgroundTextureTraitementCSV = IMG_LoadTexture(rendererTraitementCSV, "./Texture/fond.png");
    buttonMenu1Texture = IMG_LoadTexture(rendererTraitementCSV, "./Texture/bouton1VERT.png");
}

void handleButtonClickTraitementCSV(SDL_Rect* buttonRect, int* buttonState)
{
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseX >= buttonRect->x && mouseX <= (buttonRect->x + buttonRect->w) &&
        mouseY >= buttonRect->y && mouseY <= (buttonRect->y + buttonRect->h)) {
        // Clic sur le bouton "Quitter"
        if (buttonRect == &buttonMenu1Rect && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
            buttonMenu1State = 1;  // Marquer le bouton "Quitter" comme cliqué
        }
    }
}


void handleEventsTraitementCSV()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                handleButtonClickTraitementCSV(&buttonMenu1Rect, &buttonMenu1State);
                // Ajoutez la logique pour les autres boutons ici
                break;
            default:
                break;
        }
    }
}

void renderTraitementCSV()
{
    SDL_RenderClear(rendererTraitementCSV);

    SDL_RenderCopy(rendererTraitementCSV, backgroundTextureTraitementCSV, NULL, NULL);
    SDL_RenderCopy(rendererTraitementCSV, buttonMenu1State == 0 ? buttonMenu1Texture : buttonMenu1Texture, NULL, &buttonMenu1Rect);

    SDL_RenderPresent(rendererTraitementCSV);
}

void menu_traitementCSV()
{
    // Vérifier si la fenêtre de traitement existe déjà
    if (windowTraitementCSV == NULL) {
        // Créer la fenêtre de traitement
        windowTraitementCSV = SDL_CreateWindow("TraitementCSV", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_HIDDEN);  // Utiliser SDL_WINDOW_HIDDEN pour cacher la fenêtre

        // Créer le renderer de traitement
        rendererTraitementCSV = SDL_CreateRenderer(windowTraitementCSV, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        // Charger les textures et les ressources nécessaires pour la nouvelle fenêtre
        loadTexturesMenu_Traitement(); // ou utilisez une fonction appropriée pour charger les textures

        // Effectuer le rendu des éléments de la nouvelle fenêtre
        SDL_RenderCopy(rendererTraitementCSV, backgroundTextureTraitementCSV, NULL, NULL);
        // Effectuer le rendu des autres éléments de la nouvelle fenêtre

        buttonMenu1Rect.x = 1000;
        buttonMenu1Rect.y = 800;
        buttonMenu1Rect.w = 100;
        buttonMenu1Rect.h = 100;

        // Mettre à jour le rendu de la nouvelle fenêtre
        SDL_RenderPresent(rendererTraitementCSV);
    }

    // Afficher la fenêtre de traitement
    SDL_HideWindow(window);
    SDL_ShowWindow(windowTraitementCSV);

    while (1) {
        handleEventsTraitementCSV();
        renderTraitementCSV();

        if (buttonMenu1State) {
            // Cacher la fenêtre de traitement
            SDL_HideWindow(windowTraitementCSV);
            buttonMenu1State = 0;
            break;
        }
    }

    // Afficher à nouveau la fenêtre principale
    SDL_ShowWindow(window);
}