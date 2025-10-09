#ifndef JOUEUR_H
#define JOUEUR_H

#include <Arduino.h>

// Définition de la structure Joueur
struct Joueur {
  String nom;
  int score;
  bool actif;
  int questionActuelle;
};

#endif // JOUEUR_H
