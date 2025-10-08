#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "joueur.h"

extern int nbJoueursConnectes;
extern bool quizDemarre;
extern bool quizTermine;
extern const int maxJoueurs;
extern Joueur joueurs[];

#endif
