#ifndef QUIZ_H
#define QUIZ_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "./models/joueur.h"
#include "./globals/globals.h"
#include "./data/data.h"

// Nombre de questions du quiz
extern const int nbQuestionsQuiz;
extern int questionsSelectionnees[];
extern int indexQuestion;

// Fonctions
void genererQuestionsAleatoires();
int trouverJoueur(String nom);
void connexion();
void pageQuiz();
void repondre();
void pageClassement();
void resetQuiz();
void demarrerQuiz();

#endif // QUIZ_H
