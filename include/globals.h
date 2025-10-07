#pragma once
#include <ESP8266WebServer.h>

// Réseau Wi-Fi
extern const char* ssid;
extern const char* password;

// Serveur web
extern ESP8266WebServer server;

// Configuration du quiz
extern const int nbQuestionsQuiz;
extern int questionsSelectionnees[];
extern int indexQuestion;
extern int score;

// Déclarations de fonctions globales
void genererQuestionsAleatoires();
void repondre();
void resetQuiz();
