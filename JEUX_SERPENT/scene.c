#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "fonction.h"
#define LIGNE 34
#define COLONNE 58
#define TAILLE_CASE 20

/*variable position du seprent*/
int pos_x[2400], pos_y[2400], old_x[2400], old_y[2400];

/*variables position des pommes*/
int pommex[5], pommey[5];

/*variables pour créer le fond du jeu*/
int i,j,posx=20, posy=20;

/*variables des boucles*/
int p=0;
int i=0;
int pp=0;

char timer2[6];

/*Fonction Pour créer la première scene du jeu*/
void DessinerScene(int segment, int serpent, int pomme){
        for(i=0;i<LIGNE;i++){
            for(j=0;j<COLONNE;j++){
                ChoisirCouleurDessin(CouleurParComposante(0,0,0));
                DessinerRectangle(posx,posy, TAILLE_CASE, TAILLE_CASE);
                    posx += 1;
                    posy += 1;
                ChoisirCouleurDessin(CouleurParComposante(5,130,4));
                RemplirRectangle(posx,posy, TAILLE_CASE, TAILLE_CASE);
                    posx += TAILLE_CASE;
                    posx -= 1;
                    posy -= 1;
            }
            posy += TAILLE_CASE;
            posx = TAILLE_CASE;
        }
    
	snprintf(timer2,6,"%02d:%02d", 0, 0);
    ChoisirCouleurDessin(CouleurParComposante(255,255,255)); 
    EcrireTexte(10,760,timer2,2);

             
    for (i = 0; i < segment; i++){
    	AfficherSprite(serpent, 500-(i*20), 360); 
    	pos_x[i]=500-(i*20);
    	pos_y[i]=360;
    	old_y[i]=pos_y[i];
    	old_x[i]=pos_x[i];
	}
	srand(time(NULL)); 
	for (p = 0; p < 5; p++) {
    	pommex[p] = ((rand() % (58)+1)*20);
    	pommey[p] = ((rand() % (34)+1)*20);
    	AfficherSprite(pomme, pommex[p], pommey[p]);
    }
}

/*Apparition aléatoire des pommes*/
void Pomme(int pomme){
	for (pp = 0; pp < 5; ++pp) {
		AfficherSprite(pomme, pommex[pp], pommey[pp]);
	}

}

/*Input Serpent*/
int Controle(int direction){
    int t;
    while(ToucheEnAttente()){
        t = Touche();
        switch(t){
            case XK_Left : 
                if (direction != 4){    
                    direction=3;
                }
                break;
            case XK_Right:
                if (direction != 3){
                    direction=4;
                }
                break;
            case XK_Up:
                if(direction !=2){
                    direction=1;
                }
                break;
            case XK_Down:
                if (direction !=1){
                    direction=2;
                }
                break;
            case XK_Escape:
                go_on=0;
                go_menu=0;
                break;
            case XK_space:
                if (pause==0){
                    pause=1;
                }else{ 
                    pause=0;
                    ChoisirCouleurDessin(CouleurParComposante(255,255,255));
                    EcrireTexte(500,750,"Jeu en Pause",2);
                }
                break;
        }
    }
    return direction;
}

/*Avancement automatique du serpent en fonction de la direction*/
void Serpent(int direction, int segment, int tete_up, int tete_down, int tete_left, int tete_right, int serpent, int fond){ 
    if (direction == 1){
        pos_y[0]=old_y[0]-20;
    }
    if (direction == 2){
        pos_y[0]=old_y[0]+20;
    }
    if (direction == 3){
        pos_x[0]=old_x[0]-20;
    }
    if (direction == 4){
        pos_x[0]=old_x[0]+20;
    }
    AfficherSprite(fond, pos_x[segment-1], pos_y[segment-1]);
    Update_Serpent(direction, segment, tete_up, tete_down, tete_right, tete_left, serpent);
}

/*augmentation de la vitesse en fonction des pommes mangées*/
long int Update_Vitesse(long int vitesse){
    int p=0;
    for(p=0; p<5; p++){
        if(pommex[p]==pos_x[0] && pommey[p]==pos_y[0]){
            if (vitesse>20000){
                vitesse=vitesse-1500;
            }
        }
    }
    return vitesse;
}

int Update_Segment(int segment){
    int p=0;
    for(p=0; p<5; p++){
        if(pommex[p]==pos_x[0] && pommey[p]==pos_y[0]){
            segment=segment+2;
            pommex[p] = ((rand() % (58)+1)*20);
            pommey[p] = ((rand() % (34)+1)*20);
        }
    }
    return segment;
}

/*fonction pour mettre à jour la position du serpent*/
void Update_Serpent(int direction, int segment, int tete_up, int tete_down, int tete_left, int tete_right, int serpent){

    /*affichage de la tete en fonction de la direction du serpent*/
    if (direction==1){
        AfficherSprite(tete_up, pos_x[0], pos_y[0]);
    }
    if (direction==2){
        AfficherSprite(tete_down, pos_x[0], pos_y[0]);
    }
    if (direction==3){
        AfficherSprite(tete_left, pos_x[0], pos_y[0]);
    }
    if (direction==4){
        AfficherSprite(tete_right, pos_x[0], pos_y[0]);
    }

    /*affichage du reste du corps*/
    for (i=1 ; i<segment ; i++){
        pos_x[i]=old_x[i-1];
        pos_y[i]=old_y[i-1];
        AfficherSprite(serpent, pos_x[i], pos_y[i]);
    }

    ChoisirCouleurDessin(CouleurParComposante(0,0,0)); 
    RemplirRectangle(0,0,20,20);

    /*Décalage des positions du serpent*/
    old_x[0]=pos_x[0];
    old_y[0]=pos_y[0];
    for (i=1 ; i<segment ; i++){
        old_x[i]=pos_x[i];
        old_y[i]=pos_y[i];
    }
}

/*Fonction pour détécter si le serpent se touche lui même*/
void Collision(int segment){
    int i=1;
    for(i=1; i<segment;i++){
        if (pos_x[0]==pos_x[i] && pos_y[0]==pos_y[i]){
            go_on=0;
        }
    }
}

/*Fonction pour detecter si le serpent sort du terrain*/
void CollisionTerrain(){
    if (pos_x[0] >1160 || pos_x[0]<20)
        go_on=0;
    if (pos_y[0]<20 || pos_y[0] >680)
        go_on=0;
}
