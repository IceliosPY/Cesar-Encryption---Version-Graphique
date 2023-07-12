#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fonctionTraitement.h"

void chiffrement_cesar(char message[], char* cle, int Dechiffrement, int buttonCSVState, int buttonTXTState) {
  int i;
  int key = atoi(cle);
  
  for(i = 0; message[i] != '\0'; ++i) {
    if(isalpha(message[i])) {
      if(islower(message[i])) {
        message[i] = (((message[i] - 'a') + key) % 26) + 'a';
      } else {
        message[i] = (((message[i] - 'A') + key) % 26) + 'A';
      }
    }
  }
  
  if (Dechiffrement != 1) {
    FILE *fp;
    if (buttonTXTState == 1 && buttonCSVState == 0) {
      fp = fopen("result.txt", "a+");
      fprintf(fp, "Le message chiffré en utilisant la clé %s : %s\n", cle, message);
      fclose(fp);
    } else if (buttonTXTState == 0 && buttonCSVState == 1) {
      fp = fopen("result.csv", "a+");
      fprintf(fp, "clef;message;traitement\n");
      fprintf(fp, "%s;%s;;chiffrement cesar\n", cle, message);
      fclose(fp);
    } else {
    }
  }
}

void dechiffrement_cesar(char message[], char* cle, int Dechiffrement, int buttonCSVState, int buttonTXTState) {
  int key = atoi(cle);
  
  for(int i = 0; message[i] != '\0'; ++i) {
    if(isalpha(message[i])) {
      if(islower(message[i])) {
        message[i] = (((message[i] - 'a') - key + 26) % 26) + 'a';
      } else {
        message[i] = (((message[i] - 'A') - key + 26) % 26) + 'A';
      }
    }
  }
  
  FILE *fp;
  if (buttonTXTState == 1 && buttonCSVState == 0) {
    fp = fopen("result.txt", "a+");
    fprintf(fp, "Le message déchiffré en utilisant la clé %s : %s\n", cle, message);
    fclose(fp);
  } else if (buttonTXTState == 0 && buttonCSVState == 1) {
    fp = fopen("result.csv", "a+");
    fprintf(fp, "clef;message;traitement\n");
    fprintf(fp, "%s;%s;;déchiffrement cesar\n", cle, message);
    fclose(fp);
  } else {
  }
}

void chiffrement_vigenere(char message[], char* cle, int Dechiffrement, int buttonCSVState, int buttonTXTState) {
  int i, j;
  int message_length = strlen(message);
  int key_length = strlen(cle);
  
  for(i = 0, j = 0; i < message_length; ++i, ++j) {
    if(j == key_length) {
      j = 0;
    }
    
    if(isalpha(message[i])) {
      if(islower(message[i])) {
        message[i] = (((message[i] - 'a') + (tolower(cle[j]) - 'a')) % 26) + 'a';
      } else {
        message[i] = (((message[i] - 'A') + (toupper(cle[j]) - 'A')) % 26) + 'A';
      }
    }
  }
  
  if (Dechiffrement != 1) {
    FILE *fp;
    if (buttonTXTState == 1 && buttonCSVState == 0) {
      fp = fopen("result.txt", "a+");
      fprintf(fp, "Le message chiffré en utilisant la clé %s : %s\n", cle, message);
      fclose(fp);
    } else if (buttonTXTState == 0 && buttonCSVState == 1) {
      fp = fopen("result.csv", "a+");
      fprintf(fp, "clef;message;traitement\n");
      fprintf(fp, "%s;%s;;chiffrement vigenere\n", cle, message);
      fclose(fp);
    } else {
    }
  }
}

void dechiffrement_vigenere(char message[], char* cle, int Dechiffrement, int buttonCSVState, int buttonTXTState) {
  Dechiffrement = 1;
  int i, j;
  int message_length = strlen(message);
  int key_length = strlen(cle);
  
  for(i = 0, j = 0; i < message_length; ++i, ++j) {
    if(j == key_length) {
      j = 0;
    }
    
    if(isalpha(message[i])) {
      if(islower(message[i])) {
        message[i] = (((message[i] - 'a') - (tolower(cle[j]) - 'a') + 26) % 26) + 'a';
      } else {
        message[i] = (((message[i] - 'A') - (toupper(cle[j]) - 'A') + 26) % 26) + 'A';
      }
    }
  }

  FILE *fp;
  if (buttonTXTState == 1 && buttonCSVState == 0) {
    fp = fopen("result.txt", "a+");
    fprintf(fp, "Le message chiffré en utilisant la clé %s : %s\n", cle, message);
    fclose(fp);
    printf("Résultat écrit dans le fichier result.txt\n");
  } else if (buttonTXTState == 0 && buttonCSVState == 1) {
    fp = fopen("result.csv", "a+");
    fprintf(fp, "clef;message;traitement\n");
    fprintf(fp, "%s;%s;;dechiffrement vigenere\n", cle, message);
    fclose(fp);
  } else {
  }
}









