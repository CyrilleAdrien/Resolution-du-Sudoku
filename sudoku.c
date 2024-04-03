#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//déclaration de variable et fonction
int tab[3][3][3][3];
int space_ligne = 0;
void Grille();
void affiche_grille(int [3][3][3][3]);
void insertValeur();
bool ControleSaisie(int GrandeLigne, int GrandeColonne, int PetiteLigne, int PetiteColonne, int nombre);
void Play();


void main(){
    Grille();
    affiche_grille(tab);
    insertValeur();

}

//Création d'une grille pleine de 0
void Grille(){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    tab[i][j][k][l] = 0;
                }
            }
        }
    }
}
void affiche_grille(int grille[3][3][3][3]) {

    printf("\nGrille Actuelle :\n\n");
    // Affichage des lignes et des colonnes
    for (int i = 0; i < 3; i++) {
        // affichage les lignes horizontales "+-------"
        for (int j = 0; j < 3; j++) {
            printf("+-------");
        }
        printf("+\n");
        // Cellules avec les valeurs
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                printf("|");
                    for (int l = 0; l < 3; l++) {
                        printf(" %d", grille[i][j][k][l]);
                    }
                    printf(" ");
            }
            printf("|\n");
        }
    } 
    // Dernière ligne horizontale
    for (int j = 0; j < 3; j++) {
        printf("+-------");
    }
    printf("+\n");
}


void insertValeur() {
    int nombre = 0, ligne = 0, colonne = 0, region = 0;

    for (int i = 0; i < 3; i++) { // Grande Colonne
        for (int j = 0; j < 3; j++) { // Grande Ligne
            ligne++;
            for (int k = 0; k < 3; k++) { // Petite Colonne
                for (int l = 0; l < 3; l++) { // Petite Ligne
                    colonne++;
                    if (colonne % 9 == 0) colonne = 0;
                    retry_input: // Étiquette associée à la boucle extérieure

                    printf("Region %d, ligne %d et colonne %d : ", region + 1, ligne, colonne);
                    if (scanf("%d", &nombre) == 1) {
                        if (ControleSaisie(j, i, l, k, nombre)) {
                            tab[i][j][k][l] = nombre;
                            affiche_grille(tab);
                        } else {
                            printf("\033[0;31m Saisie invalide dans ce champ. Reesayer et eviter les redondances sur les lignes, colonnes et regions.\033[0m\n");
                            goto retry_input; // Retourner à l'étiquette pour réessayer la saisie
                        }
                    } else {
                        printf("\033[0;31m Veuillez saisir une valeur entiere :-( \033[0m \n");
                        // Vider le flux d'entrée
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                        goto retry_input; // Retourner à l'étiquette pour réessayer la saisie
                    }
                }
            }
        }
    }
}

bool ControleSaisie(int GrandeLigne, int GrandeColonne, int PetiteLigne, int PetiteColonne, int nombre) {
    // Contrôle de valeur
    if (nombre == 0) {
        return true;
    } else if (nombre >= 1 && nombre <= 9) {
        /* Contrôle de la logique de la grille */
        // Contrôle de l'ensemble des éléments sur la colonne 
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                if (tab[GrandeColonne][j][PetiteColonne][i] == nombre || tab[j][GrandeLigne][i][PetiteLigne] == nombre 
                    || tab[GrandeColonne][GrandeLigne][i][j] == nombre) {
                    return false;
                }
            }
        } 
        return true;
    } else {
        printf("\033[0;31m Veuillez saisir une valeur entre 0 et 9 :-)\n \033[0m");
        return false;
    }
}
void Play(){
    
}