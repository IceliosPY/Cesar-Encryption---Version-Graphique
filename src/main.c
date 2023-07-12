#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include "fonctionTraitement.h"
#include "fonctionTraitementCSV.h"

#define WINDOW_WIDTH 1333
#define WINDOW_HEIGHT 1000

// Création des textures
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* backgroundTexture = NULL;
SDL_Texture* button1RougeTexture = NULL;
SDL_Texture* button1VertTexture = NULL;
SDL_Texture* button2RougeTexture = NULL;
SDL_Texture* button2VertTexture = NULL;
SDL_Texture* button3RougeTexture = NULL;
SDL_Texture* button3VertTexture = NULL;
SDL_Texture* button4RougeTexture = NULL;
SDL_Texture* button4VertTexture = NULL;
SDL_Texture* validateButtonTexture = NULL;
SDL_Texture* quitButtonTexture = NULL;
SDL_Texture* textFieldTexture1 = NULL;
SDL_Texture* textFieldTexture2 = NULL;
SDL_Rect textFieldRect1, textFieldRect2;
SDL_Surface* textSurface1 = NULL;
SDL_Surface* textSurface2 = NULL;
SDL_Color borderColor = { 0, 255, 0 }; // Couleur rouge pour le contour
SDL_Color focusColor;
SDL_Rect titleRect;
SDL_Rect button1Rect, button2Rect, button3Rect, button4Rect;
SDL_Rect clefEntryRect, messageEntryRect;
SDL_Rect validateButtonRect;
SDL_Rect quitbuttonRect;
SDL_Texture* quitbuttonTexture = NULL;
SDL_Rect buttonCSVRect;
SDL_Rect buttonTXTRect;
SDL_Texture* buttonTXTVertTexture = NULL;
SDL_Texture* buttonTXTRougeTexture = NULL;
SDL_Texture* buttonCSVVertTexture = NULL;
SDL_Texture* buttonCSVRougeTexture = NULL;
SDL_Rect buttonResetRect;
SDL_Texture* buttonResetTexture = NULL;
SDL_Texture* buttonTraitementCSVTexture = NULL;
SDL_Rect buttonTraitementCSVRect;

// Variable pour les Structures
int currentTextField = 1; // 1 pour la première zone de texte, 2 pour la deuxième zone de texte
int button1State = 1; // 0: Vert, 1: Rouge (initialisé à 1 pour être inactif au démarrage)
int button2State = 1; // 0: Vert, 1: Rouge (initialisé à 1 pour être inactif au démarrage)
int button3State = 1; // 0: Vert, 1: Rouge (initialisé à 1 pour être inactif au démarrage)
int button4State = 1; // 0: Vert, 1: Rouge (initialisé à 1 pour être inactif au démarrage)
char textField1Content[50] = ""; // Contenu de la zone de texte 1
char textField2Content[50] = ""; // Contenu de la zone de texte 2
TTF_Font* font = NULL;
SDL_Color textColor = { 255, 255, 255 }; 
int isValidateButtonClicked = 0;
int buttonCSVState = 0; 
int buttonTXTState = 0; 
int buttonResetState = 0;
int buttonTraitementCSVState = 0;
int quitbuttonState = 0; //

//Fenetre Pop-Up au cas ou l'utilisateur ne rempli pas tout les champs 
void afficherErreur(const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", message, NULL);
}

//Traitement des messages en fonction des boutons cliqués
void performValidationAction()
{
    char message[1000]; 
    char cle[1000];  

    // Récupérer le message et la clé
    strcpy(message, textField1Content);
    strcpy(cle, textField2Content);

    if (button1State == 0 && button2State == 1 && button3State == 0 && button4State == 1 && buttonCSVState == 1 || buttonTXTState == 1) {
        chiffrement_cesar(message, cle, 0, buttonCSVState, buttonTXTState); 
    } else if (button1State == 0 && button2State == 1 && button3State == 1 && button4State == 0 && buttonCSVState == 1 || buttonTXTState == 1) {
        dechiffrement_cesar(message, cle, 0, buttonCSVState, buttonTXTState);  
    } else if (button1State == 1 && button2State == 0 && button3State == 0 && button4State == 1 && buttonCSVState == 1 || buttonTXTState == 1) {
        chiffrement_vigenere(message, cle, 0, buttonCSVState, buttonTXTState);
    } else if (button1State == 1 && button2State == 0 && button3State == 1 && button4State == 0 && buttonCSVState == 1 || buttonTXTState == 1) {
        dechiffrement_vigenere(message, cle, 0, buttonCSVState, buttonTXTState);
    } else {
	afficherErreur("Erreur : vous avez oublié un bouton.");
    }
}
void loadTextures()
{
    // Charger les textures depuis les fichiers d'imagesTexture
    backgroundTexture = IMG_LoadTexture(renderer, "./Texture/fond.png");
    button1RougeTexture = IMG_LoadTexture(renderer, "./Texture/bouton1VERT.png");
    button1VertTexture = IMG_LoadTexture(renderer, "./Texture/bouton1ROUGE.png");
    button2RougeTexture = IMG_LoadTexture(renderer, "./Texture/bouton2VERT.png");
    button2VertTexture = IMG_LoadTexture(renderer, "./Texture/bouton2ROUGE.png");
    button3RougeTexture = IMG_LoadTexture(renderer, "./Texture/bouton3VERT.png");
    button3VertTexture = IMG_LoadTexture(renderer, "./Texture/bouton3ROUGE.png");
    button4RougeTexture = IMG_LoadTexture(renderer, "./Texture/bouton4VERT.png");
    button4VertTexture = IMG_LoadTexture(renderer, "./Texture/bouton4ROUGE.png");
    validateButtonTexture = IMG_LoadTexture(renderer, "./Texture/valider.png");
    quitbuttonTexture = IMG_LoadTexture(renderer, "./Texture/boutonquitter.png");
    buttonCSVVertTexture = IMG_LoadTexture(renderer, "./Texture/boutonCSVVERT.png");
    buttonCSVRougeTexture = IMG_LoadTexture(renderer, "./Texture/boutonCSVROUGE.png");
    buttonTXTVertTexture = IMG_LoadTexture(renderer, "./Texture/boutonTXTVERT.png");
    buttonTXTRougeTexture = IMG_LoadTexture(renderer, "./Texture/boutonTXTROUGE.png");
    buttonResetTexture = IMG_LoadTexture(renderer, "./Texture/boutonReset.png");
    buttonTraitementCSVTexture = IMG_LoadTexture(renderer, "./Texture/valider.png");

    // Vérifier si les textures sont chargées correctement
    if (!backgroundTexture || !button1RougeTexture || !button1VertTexture || !button2RougeTexture ||
        !button2VertTexture || !button3RougeTexture || !button3VertTexture || !button4RougeTexture ||
        !button4VertTexture || !validateButtonTexture || !quitbuttonTexture) {
        printf("Erreur lors du chargement des textures : %s\n", SDL_GetError());
    }

    TTF_Font* font = TTF_OpenFont("police.ttf", 24);
    if (font == NULL)
    {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        
    }

    // Couleur du texte
    SDL_Color textColor = { 0, 255, 0 }; // Exemple : texte blanc

    // Charger les textures des zones de texte
	SDL_Surface* textSurface1 = TTF_RenderText_Blended(font, "Text Field 1", textColor);
	textFieldTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
	SDL_FreeSurface(textSurface1);
	textFieldRect1.x = (WINDOW_WIDTH - textSurface1->w) / 2;
	textFieldRect1.y = 500;
	textFieldRect1.w = textSurface1->w;
	textFieldRect1.h = textSurface1->h;

	SDL_Surface* textSurface2 = TTF_RenderText_Blended(font, "Text Field 2", textColor);
	textFieldTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
	SDL_FreeSurface(textSurface2);
	textFieldRect2.x = (WINDOW_WIDTH - textSurface2->w) / 2;
	textFieldRect2.y = 550;
	textFieldRect2.w = textSurface2->w;
	textFieldRect2.h = textSurface2->h;

    // Fermer la police après utilisation
    TTF_CloseFont(font);

    // Vérifier si les textures des zones de texte sont chargées correctement
    if (!textFieldTexture1 || !textFieldTexture2) {
        printf("Erreur lors du chargement des textures des zones de texte : %s\n", SDL_GetError());
    }
}


// gere le rendu texture (plus précisement les bordures des boutons pour rendre l'interface plus jolie)
void renderTexture(SDL_Texture* texture, int x, int y)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    // Dessiner le contour autour de la texture de la zone de texte
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, 255);
    SDL_RenderDrawRect(renderer, &destRect);
}

//gere les evenements de clic sur bouton
void handleButtonClick(SDL_Rect* buttonRect, int* buttonState)
{
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseX >= buttonRect->x && mouseX <= (buttonRect->x + buttonRect->w) &&
        mouseY >= buttonRect->y && mouseY <= (buttonRect->y + buttonRect->h)) {
        // Clic sur le bouton "Quitter"
        if (buttonRect == &quitbuttonRect && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
        quitbuttonState = 1; // Marquer le bouton "Quitter" comme cliqué
        }
        // Clic sur le bouton "Valider"
        else if (buttonRect == &validateButtonRect && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
            isValidateButtonClicked = 1; // Marquer le bouton "Valider" comme cliqué
        }
        // Clic sur l'un des autres boutons
        else if (buttonState != NULL && *buttonState == 1) {
            // Désactiver les autres boutons
            if (buttonRect == &button1Rect) {
                button2State = 1;
            } else if (buttonRect == &button2Rect) {
                button1State = 1;
            } else if (buttonRect == &button3Rect) {
                button4State = 1;
            } else if (buttonRect == &button4Rect) {
                button3State = 1;
            }
            
            // Mettre à jour l'état du bouton cliqué
            *buttonState = 0;
        }
        // Clic sur le bouton CSV
else if (buttonRect == &buttonCSVRect && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
    buttonCSVState = 1; // Basculer l'état du bouton TXT à vert
    buttonTXTState = 0; // Basculer l'état du bouton CSV à vert
}
// Clic sur le bouton TXT
else if (buttonRect == &buttonTXTRect && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
    buttonTXTState = 1; // Basculer l'état du bouton CSV à vert
    buttonCSVState = 0; // Basculer l'état du bouton CSV à vert
    }
else if (buttonRect == &buttonResetRect && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
    buttonTXTState = 0; // Basculer l'état du bouton CSV à vert
    buttonCSVState = 0; // Basculer l'état du bouton CSV à vert
    button1State = 1; 
    button2State = 1;
    button3State = 1; 
    button4State = 1; 
    }
else if (buttonRect == &buttonTraitementCSVRect && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
    buttonTraitementCSVState = 1;
    }
}
}

//gere tout les types devent pas forcement les bouton mais aussi les zones de texte
void handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
		case SDL_QUIT:
                quitbuttonState = 1; // Marquer le bouton "Quitter" comme cliqué lorsque l'événement de fermeture de la fenêtre se produit
		//sert a quitter l'application
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleButtonClick(&button1Rect, &button1State);
                handleButtonClick(&button2Rect, &button2State);
                handleButtonClick(&button3Rect, &button3State);
                handleButtonClick(&button4Rect, &button4State);
		handleButtonClick(&buttonCSVRect, &buttonCSVState);
		handleButtonClick(&buttonTXTRect, &buttonTXTState);
		handleButtonClick(&buttonResetRect, &buttonResetState);
                handleButtonClick(&validateButtonRect, NULL); // Gérer le clic sur le bouton "Valider" sans modifier l'état du bouton
                handleButtonClick(&quitbuttonRect, &quitbuttonState);
   	        handleButtonClick(&buttonTraitementCSVRect, &buttonTraitementCSVState); 
                break;
            case SDL_TEXTINPUT: 
    if (event.text.windowID == SDL_GetWindowID(window)) {
        if (currentTextField == 1) {
            // Mettre à jour le contenu de la zone de texte 1
            if (textField1Content[0] == '\0') {
                strcpy(textField1Content, event.text.text);
            } else {
                strcat(textField1Content, event.text.text);
            }
        } else if (currentTextField == 2) {
            // Mettre à jour le contenu de la zone de texte 2
            if (textField2Content[0] == '\0') {
                strcpy(textField2Content, event.text.text);
            } else {
                strcat(textField2Content, event.text.text);
            }
        }
    }
    break;
            case SDL_KEYDOWN:
    if (event.key.windowID == SDL_GetWindowID(window)) {
        if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_TAB) {
            // L'utilisateur a appuyé sur "Entrée" ou "Tab"
            // permet de passe à la zone de texte suivante
            currentTextField = (currentTextField % 2) + 1;

            // Mettre à jour la couleur du texte pour indiquer le focus
            if (currentTextField == 1) {
                SDL_FreeSurface(textSurface2);
                textSurface2 = TTF_RenderText_Blended(font, textField2Content, textColor);
            } else if (currentTextField == 2) {
                SDL_FreeSurface(textSurface1);
                textSurface1 = TTF_RenderText_Blended(font, textField1Content, textColor);
            }
        } else if (event.key.keysym.sym == SDLK_BACKSPACE && currentTextField == 1) {
            // L'utilisateur a appuyé sur "Retour arrière" et le champ de texte 1 est en priorite
            if (strlen(textField1Content) > 0) {
                // Supprimer le dernier caractère du contenu du champ de texte 1
                textField1Content[strlen(textField1Content) - 1] = '\0';
                
                // Mettre à jour la surface de texte du champ de texte 1
                SDL_FreeSurface(textSurface1);
                textSurface1 = TTF_RenderText_Blended(font, textField1Content, textColor);
            }
        } else if (event.key.keysym.sym == SDLK_BACKSPACE && currentTextField == 2) {
            // L'utilisateur a appuyé sur "Retour arrière" et le champ de texte 2 est en focus
            if (strlen(textField2Content) > 0) {
                // Supprimer le dernier caractère du contenu du champ de texte 2
                textField2Content[strlen(textField2Content) - 1] = '\0';
                
                // Mettre à jour la surface de texte du champ de texte 2
                SDL_FreeSurface(textSurface2);
                textSurface2 = TTF_RenderText_Blended(font, textField2Content, textColor);
            }
        }
    }
    break;
            default:
                break;
        }
    }
}

void render()
{
    SDL_RenderClear(renderer);

    renderTexture(backgroundTexture, 0, 0);
    renderTexture(button1State == 0 ? button1VertTexture : button1RougeTexture, button1Rect.x, button1Rect.y);
    renderTexture(button2State == 0 ? button2VertTexture : button2RougeTexture, button2Rect.x, button2Rect.y);
    renderTexture(button3State == 0 ? button3VertTexture : button3RougeTexture, button3Rect.x, button3Rect.y);
    renderTexture(button4State == 0 ? button4VertTexture : button4RougeTexture, button4Rect.x, button4Rect.y);
    renderTexture(validateButtonTexture, validateButtonRect.x, validateButtonRect.y);
    renderTexture(quitbuttonTexture, quitbuttonRect.x, quitbuttonRect.y);
    renderTexture(buttonCSVState == 0 ? buttonCSVVertTexture : buttonCSVRougeTexture, buttonCSVRect.x, buttonCSVRect.y);
    renderTexture(buttonTXTState == 0 ? buttonTXTVertTexture : buttonTXTRougeTexture, buttonTXTRect.x, buttonTXTRect.y);
    renderTexture(buttonResetTexture, buttonResetRect.x, buttonResetRect.y);
    renderTexture(buttonTraitementCSVTexture, buttonTraitementCSVRect.x, buttonTraitementCSVRect.y);

    // Rendre la texture de la zone de texte 1 avec le contour approprié
    SDL_Surface* textSurface1 = TTF_RenderText_Blended(font, textField1Content, currentTextField == 1 ? textColor : focusColor);
    textFieldTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
    SDL_FreeSurface(textSurface1);
    renderTexture(textFieldTexture1, textFieldRect1.x, textFieldRect1.y);

    // Rendre la texture de la zone de texte 2 avec le contour approprié
    SDL_Surface* textSurface2 = TTF_RenderText_Blended(font, textField2Content, currentTextField == 2 ? textColor : focusColor);
    textFieldTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
    SDL_FreeSurface(textSurface2);
    renderTexture(textFieldTexture2, textFieldRect2.x, textFieldRect2.y);

    SDL_RenderPresent(renderer);
}

void cleanerMenu1(){
   // Libérer les ressources
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(button1RougeTexture);
    SDL_DestroyTexture(button1VertTexture);
    SDL_DestroyTexture(button2RougeTexture);
    SDL_DestroyTexture(button2VertTexture);
    SDL_DestroyTexture(button3RougeTexture);
    SDL_DestroyTexture(button3VertTexture);
    SDL_DestroyTexture(button4RougeTexture);
    SDL_DestroyTexture(button4VertTexture);
    SDL_DestroyTexture(validateButtonTexture);
    SDL_DestroyTexture(quitButtonTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}

void menu1(){
 
    // Initialiser SDL
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation de SDL_ttf: %s\n", TTF_GetError());
    }

    font = TTF_OpenFont("police.ttf", 24);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police: %s\n", TTF_GetError());
    }
    // Initialisation de la variable globale de la priorite des zones de texte
    focusColor.r = 0;
    focusColor.g = 255;
    focusColor.b = 0;
    // en clair, le programme affichera en vert un message valide
    // Créer la fenêtre
    window = SDL_CreateWindow("Chiffrement/Dechiffrement", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Créer le renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Charger les textures
    loadTextures();

    // Définir les rectangles des boutons et des autres éléments
    titleRect.x = (WINDOW_WIDTH - titleRect.w) / 2;
    titleRect.y = 50;


    button1Rect.x = 200;
    button1Rect.y = 200;
    button1Rect.w = 200;
    button1Rect.h = 200;

    button2Rect.x = 400;
    button2Rect.y = 200;
    button2Rect.w = 200;
    button2Rect.h = 200;

    button3Rect.x = 200;
    button3Rect.y = 400;
    button3Rect.w = 200;
    button3Rect.h = 200;

    button4Rect.x = 400;
    button4Rect.y = 400;
    button4Rect.w = 200;
    button4Rect.h = 200;


    validateButtonRect.x = 150;
    validateButtonRect.y = 650;
    validateButtonRect.w = 200; // Ajout de la largeur du bouton "Valider"
    validateButtonRect.h = 100; // Ajout de la hauteur du bouton "Valider"

    buttonResetRect.x = validateButtonRect.x+200;
    buttonResetRect.y = validateButtonRect.y;
    buttonResetRect.w = 100;
    buttonResetRect.h = 100;

    quitbuttonRect.x = buttonResetRect.x + 100; // Réglez la position x du bouton "Quitter"
    quitbuttonRect.y = buttonResetRect.y; // Réglez la position y du bouton "Quitter"
    quitbuttonRect.w = 200; // Ajout de la largeur du bouton "Quitter"
    quitbuttonRect.h = 100; // Ajout de la hauteur du bouton "Quitter"

 // Rendre la texture de la zone de texte 1
    textFieldRect1.x = WINDOW_WIDTH - 300;
    textFieldRect1.y = 200;
    textFieldRect1.w = 200;
    textFieldRect1.h = 50;
    renderTexture(textFieldTexture1, textFieldRect1.x, textFieldRect1.y);

    // Rendre la texture de la zone de texte 2
    textFieldRect2.x = WINDOW_WIDTH - 300;
    textFieldRect2.y = 400;
    textFieldRect2.w = 200;
    textFieldRect2.h = 50;
    renderTexture(textFieldTexture2, textFieldRect2.x, textFieldRect2.y);

    buttonCSVRect.x = quitbuttonRect.x+550;
    buttonCSVRect.y = quitbuttonRect.y;
    buttonCSVRect.w = 100;
    buttonCSVRect.h = 100;

    buttonTXTRect.x = buttonCSVRect.x + 100;
    buttonTXTRect.y = quitbuttonRect.y;
    buttonTXTRect.w = 100;
    buttonTXTRect.h = 100;

    buttonTraitementCSVRect.x = 1000;
    buttonTraitementCSVRect.y = 800;
    buttonTraitementCSVRect.w = 100;
    buttonTraitementCSVRect.h = 100;


    
    SDL_RenderPresent(renderer);
    // Boucle principale 
int validationActionExecuted = 0;

// Boucle principale
while (1) {
    handleEvents();
    render();

	if (quitbuttonState) {
	break;
        }
	if (buttonTraitementCSVState) {
            menu_traitementCSV();
            SDL_ShowWindow(window); // Afficher à nouveau la fenêtre menu1 après avoir fermé menu_traitementCSV
	    buttonTraitementCSVState = 0;
        }

    if (isValidateButtonClicked) {
        isValidateButtonClicked = 0; // Réinitialiser l'état du bouton "Valider"

        if (!validationActionExecuted) {
            performValidationAction();
            validationActionExecuted = 1;
        }

    } else {
        // Réinitialiser l'état du traitement du bouton "Valider" si le bouton n'est pas cliqué
        validationActionExecuted = 0;
    }


    SDL_Delay(10); // Ajouter un délai pour réduire la charge CPU
}
}

int SDL_main(int argc, char* argv[])
{
    menu1();
    return 0;
    cleanerMenu1();
}
