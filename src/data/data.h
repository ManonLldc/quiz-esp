#ifndef DATA_H
#define DATA_H

#include <Arduino.h>

struct Question {
  String texte;
  String reponses[4];
  char correct;
};

// Déclaration externe du tableau quiz
extern Question quiz[];
extern int nbQuestions;

#endif
