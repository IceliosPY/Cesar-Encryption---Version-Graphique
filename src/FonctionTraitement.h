#ifndef TRAITEMENT_H
#define TRAITEMENT_H

void chiffrement_cesar(char message[], char* cle, int Dechiffrement, int buttonCSVState, int buttonTXTState);
void dechiffrement_cesar(char message[], char* cle, int Dechiffrement, int buttonCSVState, int buttonTXTState);
void chiffrement_vigenere(char message[], char* cle, int Dechiffrement, int buttonCSVState, int buttonTXTState);
void dechiffrement_vigenere(char message[], char* cle, int Dechiffrement, int buttonCSVState, int buttonTXTState);
int verificationChiffreETlettre(char message[], int autorisation);
int verificationCleChiffre(int cle, int autorisation);
int verificationCleLettre(char cle2[100], int autorisation);

#endif