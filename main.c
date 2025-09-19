
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include "enigme2.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* ecran = SDL_SetVideoMode(1920, 950, 32, SDL_HWSURFACE);
    if (!ecran) {
        printf("Erreur d'initialisation de la fenêtre : %s\n", SDL_GetError());
        return 1;
    }

    srand(time(NULL));
    static int dernier_choix;
    static int avant_dernier_choix;

    int choix;
    do {
        choix = rand() % 3 + 1;
    } while (choix == dernier_choix && choix == avant_dernier_choix) ;
    avant_dernier_choix = dernier_choix;
    dernier_choix = choix;
    
    
    Enigme2 enigme2;
    Enigme2_2 enigme2_2;
    Enigme2_3 enigme2_3;
    int quitter = 0;
    SDL_Event event;

    if (choix == 1) {
        init_bg(&enigme2);
    } else if(choix == 2) {
        init_bg2(&enigme2_2);
    }
    else{
        init_bg3(&enigme2_3);
    }

    while (!quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter = 1;
            }
            if (choix == 1) {
                clickButton(&enigme2, event);
            } else if (choix == 2) {
                clickButton2(&enigme2_2, event);
            }
            else{
                clickButton3(&enigme2_3, event);
            }
        }
        if (choix == 1) {
            afficher_bg1(&enigme2, ecran);
            mettre_a_jour_enigme(&enigme2);
            if (enigme2.fin_jeu == 1 || enigme2.jouer_gagner == 0) quitter = 1;
        } 
        else if (choix == 2) {
            afficher_bg2(&enigme2_2, ecran);
            mettre_a_jour_enigme2(&enigme2_2);
            if (enigme2_2.fin_jeu == 1 || enigme2_2.jouer_gagner == 0) quitter = 1;
        }
        else {
            afficher_bg3(&enigme2_3, ecran);
            mettre_a_jour_enigme3(&enigme2_3);
            if (enigme2_3.fin_jeu == 1 || enigme2_3.jouer_gagner == 0) quitter = 1;
        }
    
        SDL_Flip(ecran);
    }
    if (choix == 1) {
        liberer_enigme(&enigme2);
    } else if (choix == 2){
        liberer_enigme2(&enigme2_2);
    }
    else{
        liberer_enigme3(&enigme2_3);
    }

    SDL_Quit();
    return 0;
}
