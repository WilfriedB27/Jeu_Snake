#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "fonction.h"
#define CYCLE 10000L

/*variables gestion du timer*/
unsigned long int suivant;
unsigned long int old_seconde=0;

/*variables pour gerer les menus + la pause*/
int go_menu2=1;
int go_on=1;
int go_menu=1;
int pause=1;

/*variables gestion score*/
int Nbr;

/*variables gestion serpent + pomme*/
int segment=10;
int tete_up, tete_down, tete_right, tete_left, fond, pomme, serpent;

/*1 : vers le haut, 2 : vers le bas, 3 vers la gauche, 4 vers la droite*/
int direction=4;

/*vitesse d'acualisation du serpent*/
long int vitesse=100000;

/*variables gestion input*/
int t;
int t2;
int t3;


/*Fonction Principale*/
int main(){
    /* paramétrage de la fenêtre + chargement première scène */
    InitialiserGraphique();
    CreerFenetre(350,100,1200,800);

    /*chargement des sprites nécessaire pour le jeu*/
    serpent=ChargerSprite("IMG/serpent.png");
    fond=ChargerSprite("IMG/fond.png");
    tete_up = ChargerSprite("IMG/tete_up.png");
    tete_down =ChargerSprite("IMG/tete_down.png");
    tete_left = ChargerSprite("IMG/tete_left.png");
    tete_right = ChargerSprite("IMG/tete_right.png");
    pomme=ChargerSprite("IMG/pomme.png");

    /*creation du menu du début*/
    MenuDebut();

    /*choix dans le menu*/
    while(go_menu2){
        while(ToucheEnAttente()){
            t3 = Touche();
            switch(t3){  
                case XK_q : 
                    FermerGraphique();
                    return EXIT_SUCCESS;
                    break;
                case XK_Right:
                    go_menu2=0;
                    break;
            }
        }
    }

    /*creation de la scene du jeu*/
    EffacerEcran(CouleurParComposante(0,0,0));
    DessinerScene(segment, serpent, pomme);
    suivant=Microsecondes()+CYCLE;
    old_seconde=(suivant/100000)%10;
	
/*Boucle Principale du Programme*/
    while(go_on){
        direction = Controle(direction);
        if (pause==1){
            old_seconde = Timer(suivant, old_seconde);
            Collision(segment);
            vitesse = Update_Vitesse(vitesse);
            segment = Update_Segment(segment);
            Serpent(direction, segment, tete_up, tete_down, tete_right, tete_left, serpent, fond);
            Nbr = Score(segment, Nbr);
		    Pomme(pomme);
            Attendre(vitesse);  
            CollisionTerrain();
        }
	}
  
/* fermeture de la fenêtre si ECHAP pressé + Menu de Fin*/
    MenuDeFin(Nbr);

    while(go_menu){
        while(ToucheEnAttente()){
            t2 = Touche();
            switch(t2){  
                case XK_q : 
                    go_menu=0;
                    break;
            }
        }
    }
    /*fermeture du programme*/
    FermerGraphique();
    return EXIT_SUCCESS;
}