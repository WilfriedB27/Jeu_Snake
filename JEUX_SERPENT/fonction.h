#ifndef FONCTION_H
#define FONCTION_H
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>


extern int go_on;
extern int go_menu;
extern int pause;

void Pomme(int pomme);
int Controle(int direction);
void Serpent(int direction, int segment, int tete_up, int tete_down, int tete_left, int tete_right, int serpent, int fond);
void Update_Serpent(int direction, int segment, int tete_up, int tete_down, int tete_left, int tete_right, int serpent);
long int Update_Vitesse(long int vitesse);
int Update_Segment(int segment);
void CollisionTerrain();
int Timer(unsigned long int suivant, int old_seconde);
void Update_Timer();
void DessinerScene(int segment, int serpent, int pomme);
int Score(int segment, int Nbr);
void Collision(int segment);
void MenuDeFin(int Nbr);
void MenuDebut();
void Attendre(long int microsecondes);

#endif