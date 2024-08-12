#include <stdio.h>    // Inclusion de la bibliothèque standard pour les entrées/sorties
#include <stdbool.h>  // Inclusion de la bibliothèque pour les types booléens
#include <string.h>   // Inclusion de la bibliothèque pour les opérations sur les chaînes de caractères

#define TAILLE 9  // Définition de la taille de la grille de Sudoku

int grille[TAILLE][TAILLE] = {0}; // Grille principale de Sudoku initialisée à 0
bool logiqueTab[TAILLE][TAILLE][TAILLE+1]; // Grille logique pour gérer les possibilités

bool ControleSaisie(int, int, int);

// Initialise la grille principale et la grille logique
void initialiserGrilles() {
    int exemples[TAILLE][TAILLE] = {
        {8, 1, 3, 4, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 1, 4, 0, 3},
        {0, 0, 5, 0, 7, 0, 0, 0, 0},
        {0, 4, 0, 0, 9, 5, 6, 0, 0},
        {0, 5, 2, 8, 4, 7, 3, 9, 0},
        {0, 0, 1, 6, 3, 0, 0, 4, 0},
        {0, 0, 0, 0, 8, 0, 2, 0, 0},
        {5, 0, 6, 9, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 6, 9, 3, 8}
    };
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            grille[i][j] = exemples[i][j];
            for (int k = 1; k <= TAILLE; k++) {
                logiqueTab[i][j][k] = (grille[i][j] == 0 || grille[i][j] == k); // Initialise la grille logique
            }
        }
    }
}


// Affiche la grille de Sudoku
void afficherGrille() {
    printf("\nGrille Actuelle :\n\n");
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                printf("| ");
            }
            printf("%d ", grille[i][j]);
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
}

void insertValeur(int grille[9][9]) {
    int nombre = 0;

    for (int i = 0; i < 9; i++) { // Ligne
        for (int j = 0; j < 9; j++) { // Colonne
            retry_input: // Étiquette associée à la boucle extérieure

            printf("Ligne %d et colonne %d : ", i + 1, j + 1);
            //test sur la variable reçu au clavier pour savoir s'il s'agit d'un entier
            if (scanf("%d", &nombre) == 1) {
                if (ControleSaisie(i, j, nombre)) {
                    grille[i][j] = nombre;//affectation du nombre saisie à la grille
                    afficherGrille();
                } else {
                    printf("\033[0;31m Saisie invalide dans ce champ. Reessayer et eviter les redondances sur les lignes, colonnes et regions.\033[0m\n");
                    goto retry_input; // Retourner à l'étiquette pour réessayer la saisie
                }
            } else {
                printf("\033[0;31m Veuillez saisir une valeur entiere :-( \033[0m \n");
                // Vider le flux d'entrée dans le scanf() si la saisie était incorrect
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                goto retry_input; // Retourner à l'étiquette pour réessayer la saisie
            }
        }
    }
}    
// Met à jour la grille logique pour refléter les contraintes actuelles
void updateConstraints(int ligne, int colonne, int num, bool state) {
    for (int i = 0; i < TAILLE; i++) {
        logiqueTab[ligne][i][num] = state; // Mise à jour de la ligne
        logiqueTab[i][colonne][num] = state; // Mise à jour de la colonne
    }

    int startRow = ligne - (ligne % 3);
    int startCol = colonne - (colonne % 3);
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            logiqueTab[i][j][num] = state; // Mise à jour du bloc 3x3
        }
    }
}

// Vérifie si le placement d'un numéro est possible
bool ControleLogique(int ligne, int colonne, int num) {
    for (int i = 0; i < TAILLE; i++) {
        if (grille[ligne][i] == num || grille[i][colonne] == num)
            return false; // Vérifie les doublons dans la ligne et la colonne
    }
    int startRow = ligne - (ligne % 3);
    int startCol = colonne - (colonne % 3);
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (grille[i][j] == num)
                return false; // Vérifie les doublons dans le bloc 3x3
        }
    }
    return true; // Retourne vrai si le placement est possible
}
bool ControleSaisie(int ligne, int colonne, int num) {
    if (num == 0) {
         return true; // Passer à la case vide suivante 
    }
    for (int i = 0; i < TAILLE; i++) {
        if (grille[ligne][i] == num || grille[i][colonne] == num)
            return false; // Vérifie les doublons dans la ligne et la colonne
    }
    int startRow = ligne - (ligne % 3);
    int startCol = colonne - (colonne % 3);
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (grille[i][j] == num)
                return false; // Vérifie les doublons dans le bloc 3x3
        }
    }
    return true; // Retourne vrai si le placement est possible
}

// Résout le Sudoku en utilisant la grille logique
bool Solver(int ligne, int colonne) {
    if (ligne == TAILLE)  // Si toutes les lignes sont traitées
        return true;
    int nextLigne = (colonne == TAILLE - 1) ? ligne + 1 : ligne;
    int nextColonne = (colonne + 1) % TAILLE;

    if (grille[ligne][colonne] != 0)  // Si la cellule est déjà remplie
        return Solver(nextLigne, nextColonne);

    for (int num = 1; num <= TAILLE; num++) {
        if (logiqueTab[ligne][colonne][num] && ControleLogique(ligne, colonne, num)) {
            grille[ligne][colonne] = num; // Place le nombre
            updateConstraints(ligne, colonne, num, false); // Met à jour les contraintes
            if (Solver(nextLigne, nextColonne))
                return true; // Si la grille est résolue, retourne vrai
            grille[ligne][colonne] = 0; // Annule le placement
            updateConstraints(ligne, colonne, num, true); // Réinitialise les contraintes
        }
    }
    return false; // Retourne faux si aucune solution valide n'est trouvée
}

// Vérifie que la grille complétée est correcte
bool verifierGrille() {
    for (int ligne = 0; ligne < TAILLE; ligne++) {
        for (int colonne = 0; colonne < TAILLE; colonne++) {
            int num = grille[ligne][colonne];
            if (num != 0 && !ControleLogique(ligne, colonne, num))
                return false; // Retourne faux si un nombre est mal placé
        }
    }
    return true; // Retourne vrai si la grille est correcte
}

bool verifieLigne(int grille[TAILLE][TAILLE], int ligne) {
    bool presente[TAILLE + 1] = {false}; // Un tableau pour vérifier la présence des chiffres 1 à 9
    for (int colonne = 0; colonne < TAILLE; colonne++) {
        int num = grille[ligne][colonne];
        if (num < 1 || num > 9 || presente[num]) {
            printf("Ligne %d: Erreur\n", ligne + 1);
            return false;
        }
        presente[num] = true;
    }
    printf("Ligne %d: \033[32mOK\033[0m\n", ligne + 1);
    return true;
}

bool verifieColonne(int grille[TAILLE][TAILLE], int colonne) {
    bool presente[TAILLE + 1] = {false}; // Un tableau pour vérifier la présence des chiffres 1 à 9
    for (int ligne = 0; ligne < TAILLE; ligne++) {
        int num = grille[ligne][colonne];
        if (num < 1 || num > 9 || presente[num]) {
            printf("Colonne %d: Erreur\n", colonne + 1);
            return false;
        }
        presente[num] = true;
    }
    printf("Colonne %d: \033[32mOK\033[0m\n", colonne + 1);
    return true;
}

bool verifieSousGrille(int grille[TAILLE][TAILLE], int startLigne, int startColonne) {
    bool presente[TAILLE + 1] = {false}; // Un tableau pour vérifier la présence des chiffres 1 à 9
    for (int ligne = 0; ligne < 3; ligne++) {
        for (int colonne = 0; colonne < 3; colonne++) {
            int num = grille[startLigne + ligne][startColonne + colonne];
            if (num < 1 || num > 9 || presente[num]) {
                printf("Sous-grille (%d, %d): Erreur\n", startLigne, startColonne);
                return false;
            }
            presente[num] = true;
        }
    }
    printf("Sous-grille (%d, %d): \033[32mOK\033[0m\n", startLigne, startColonne);
    return true;
}

bool TestFinal(int grille[TAILLE][TAILLE]) {
    printf("\nLe Test commence...\n\n");
    bool valide = true;

    for (int ligne = 0; ligne < TAILLE; ligne++) {
        if (!verifieLigne(grille, ligne)) {
            valide = false;
        }
    }

    for (int colonne = 0; colonne < TAILLE; colonne++) {
        if (!verifieColonne(grille, colonne)) {
            valide = false;
        }
    }

    for (int ligne = 0; ligne < TAILLE; ligne += 3) {
        for (int colonne = 0; colonne < TAILLE; colonne += 3) {
            if (!verifieSousGrille(grille, ligne, colonne)) {
                valide = false;
            }
        }
    }
    if (valide) {
        printf("\n\033[32mSudoku resolu avec succes ! Voici la solution : OK\033[0m\n\n");
    }
    return valide;
}

int main() {
    int choix;

    printf("Choisissez une option:\n");
    printf("1. Utiliser une grille preremplie\n");
    printf("2. Inserer vous-meme les valeurs\n");
    printf("Votre choix: ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            initialiserGrilles(); // Initialise les grilles avec une grille préremplie
            break;
        case 2:
            for (int i = 0; i < TAILLE; i++) {
                for (int j = 0; j < TAILLE; j++) {
                    grille[i][j] = 0;
                    for (int k = 1; k <= TAILLE; k++) {
                        logiqueTab[i][j][k] = true;
                    }
                }
            }
            insertValeur(grille); // Permet à l'utilisateur d'insérer les valeurs
            break;
        default:
            printf("Choix invalide.\n");
            return 1;
    }

    afficherGrille(); // Affiche la grille initiale
    printf("\nResolution commence\n   .\n   .\n   .\n");

    if (Solver(0, 0) && verifierGrille()) { // Tente de résoudre le Sudoku et vérifie la solution
        if (TestFinal(grille)) {
            afficherGrille(); // Affiche la grille résolue
        }
    } else if(TestFinal(grille)) {//Voir les erreurs sur la grille
        afficherGrille(); // Affiche la grille non résolue
    }
    afficherGrille();

    return 0;
}
