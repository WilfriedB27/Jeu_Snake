#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "fonction.h"
#define CYCLE 10000L

int seconde=0, minute=0, seconde_actuel=0;
int imageMenuFin;
int imageMenuDebut;
char timer[6];
char score[4];

/*Fonction pour calculer le temps*/
int Timer(unsigned long int suivant, int old_seconde){
	if(Microsecondes()> suivant){
		suivant = Microsecondes()+CYCLE;
		seconde_actuel = (suivant/1000000)%10;
		if(seconde_actuel !=old_seconde){
			old_seconde = seconde_actuel;
			if(seconde == 59){
				minute=minute+1;
				seconde=0;
			}else{
				seconde = seconde+1;
			}
		}
	}
	Update_Timer();
	return old_seconde;
}

/*Fonction pour mettre à jour unuquement le timer*/
void Update_Timer(){
	snprintf(timer,6,"%02d:%02d", minute, seconde);
	ChoisirCouleurDessin(CouleurParComposante(0,0,0)); 
	RemplirRectangle(0,700,1200,800);
	ChoisirCouleurDessin(CouleurParComposante(255,255,255)); 
	EcrireTexte(10,760,timer,2);
}

/*fonction afin de créer un délai (en microseconde*/
void Attendre(long int microsecondes){
	long int attendre;
	attendre = Microsecondes()+ microsecondes;
	while (Microsecondes() < attendre){
	}
}

/*création du Menu de Fin*/
void MenuDeFin(int Nbr){
    EffacerEcran(CouleurParComposante(0,0,0));
    imageMenuFin=ChargerSprite("IMG/menu2.png");
    AfficherSprite(imageMenuFin,0,0);
    ChoisirCouleurDessin(CouleurParComposante(255,255,255));
    snprintf(score,15,"Score : %04d", Nbr);
    EcrireTexte(500,650,score,2);
    snprintf(timer,14,"Temps : %02d:%02d", minute, seconde);
    EcrireTexte(490,700,timer,2);
    EcrireTexte(410,750,"Appuyer sur Q pour quitter",2);
}

/*création du menu d'accueil*/
void MenuDebut(){
    imageMenuDebut=ChargerSprite("IMG/menu1.png");
    AfficherSprite(imageMenuDebut,0,0);
    ChoisirCouleurDessin(CouleurParComposante(255,255,255)); 
    EcrireTexte(410,650,"Appuyer sur Q pour quitter",2);
    EcrireTexte(290,750,"Appuyer sur Fleche de Droite pour lancer le jeu",2);
}

/*fonction pour afficher + calculer le score*/
int Score(int segment, int Nbr){
    Nbr=(segment-10)*2.5;
    snprintf(score,5,"%04d", Nbr);
    ChoisirCouleurDessin(CouleurParComposante(0,0,0)); 
    RemplirRectangle(1100,730,1200,800);
    ChoisirCouleurDessin(CouleurParComposante(255,255,255));
    EcrireTexte(1000,750,"Score :",2);
    EcrireTexte(1100,750,score,2);
    return Nbr;
}