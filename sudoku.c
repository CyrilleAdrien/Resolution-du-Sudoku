#include<stdio.h>
#include<stdlib.h>
//déclaration de variable et fonction
int tab[3][3][3][3];
int space_ligne = 0;
void affiche_grille(int ligne, int colone, int PetiteLigne, int PetiteColone, int nombre);


void main(){

    affiche_grille(1,2,0,1,5);
    affiche_grille(1,2,1,1,9);
    affiche_grille(1,2,1,2,9);
}

void affiche_grille(int GrandeLine, int GrandeColone, int PetiteLigne, int PetiteColone, int nombre){
int indinceColone = 1;
//affiche indice de ligne
    printf("\n   ");
    for(int n = 1; n <10 ; n++){
        printf("%d ",n);
        if(n%3==0 && n!=9) printf("  ");
    }
    //remplace la valeur
    for(int i = 0; i <3; i++){
        for(int j = 0; j <3; j++){
            //printf("%d  ",indinceColone);
            printf("\n%d  ",indinceColone);
            indinceColone++;
            for(int k = 0; k <3; k++){
                for(int l = 0; l <3; l++){
                    if(i == GrandeLine && j == GrandeColone && k == PetiteLigne && l == PetiteColone){
                        tab[GrandeLine][GrandeColone][PetiteLigne][PetiteColone] = nombre;
                    }
                    else if(tab[i][j][k][l] == 0){
                        tab[i][j][k][l] = 0;
                    }
                    printf("%d ", tab[i][j][k][l]);
                    space_ligne ++;
                    if(space_ligne%27 == 0)
                        printf("\n");
                }
                printf("  ");
            }

        }
    }

}

int remplir_grille(){

}