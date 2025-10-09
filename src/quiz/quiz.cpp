#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "./data/data.h"
#include "./config/config.h"
#include "./models/joueur.h"
#include "./ui/pageConnexion.h"
#include "./globals/globals.h"
#include "./connexion/connexion.h"
#include "quiz.h"

// Configuration quiz
// const int nbQuestionsQuiz = 10;
int questionsSelectionnees[nbQuestionsQuiz];
int indexQuestion = 0;

void genererQuestionsAleatoires() {
  bool dejaPris[nbQuestions] = { false };
  int count = 0;
  while (count < nbQuestionsQuiz) {
    int r = random(0, nbQuestions);
    if (!dejaPris[r]) {
      dejaPris[r] = true;
      questionsSelectionnees[count++] = r;
    }
  }
}

// Trouve l'index du joueur par son nom
int trouverJoueur(String nom) {
  for (int i = 0; i < maxJoueurs; i++) {
    if (joueurs[i].actif && joueurs[i].nom == nom) {
      return i;
    }
  }
  return -1;
}

// Traitement des réponses
void repondre() {
  if (!server.hasArg("nom") || !server.hasArg("r")) {
    server.sendHeader("Location", "/");
    server.send(303);
    return;
  }

  String nom = server.arg("nom");
  int idxJoueur = trouverJoueur(nom);
  
  if (idxJoueur < 0) {
    server.sendHeader("Location", "/");
    server.send(303);
    return;
  }

  Joueur &j = joueurs[idxJoueur];
  char r = server.arg("r").charAt(0);
  Question &q = quiz[questionsSelectionnees[j.questionActuelle]];

  if (r == q.correct) {
    j.score++;
  }

  j.questionActuelle++;
  
  // Vérifie si tous les joueurs ont fini
  bool tousTermines = true;
  for (int i = 0; i < maxJoueurs; i++) {
    if (joueurs[i].actif && joueurs[i].questionActuelle < nbQuestionsQuiz) {
      tousTermines = false;
      break;
    }
  }
  
  if (tousTermines) {
    quizTermine = true;
  }

  server.sendHeader("Location", "/quiz?nom=" + nom);
  server.send(303);
}

// Reset du quiz
void resetQuiz() {
  indexQuestion = 0;
  quizDemarre = false;
  quizTermine = false;
  
  for (int i = 0; i < maxJoueurs; i++) {
    joueurs[i].score = 0;
    joueurs[i].actif = false;
    joueurs[i].questionActuelle = 0;
  }
  
  nbJoueursConnectes = 0;
  genererQuestionsAleatoires();
  
  server.sendHeader("Location", "/");
  server.send(303);
}

// Démarrage du quiz
void demarrerQuiz() {
  quizDemarre = true;
  server.sendHeader("Location", "/");
  server.send(303);
}
