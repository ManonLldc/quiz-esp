#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "./models/joueur.h"

extern int nbJoueursConnectes;
extern bool quizDemarre;
extern bool quizTermine;
void connexion();
extern const int maxJoueurs;
extern Joueur joueurs[];

#endif
