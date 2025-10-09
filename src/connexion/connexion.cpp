#include <Arduino.h>
// #include <ESP8266WebServer.h>
#include "./globals/globals.h"
#include "./config/config.h"
#include "./quiz/quiz.h"

// Traitement de la connexion
void connexion() {
  if (!server.hasArg("nom")) {
    server.sendHeader("Location", "/");
    server.send(303);
    return;
  }

  String nom = server.arg("nom");
  nom.trim();
  
  if (nom.length() == 0 || nom.length() > 20) {
    server.sendHeader("Location", "/?error=nom");
    server.send(303);
    return;
  }

  // Vérifie si le joueur existe déjà
  if (trouverJoueur(nom) >= 0) {
    server.sendHeader("Location", "/quiz?nom=" + nom);
    server.send(303);
    return;
  }

  // Ajoute un nouveau joueur
  if (nbJoueursConnectes < maxJoueurs) {
    for (int i = 0; i < maxJoueurs; i++) {
      if (!joueurs[i].actif) {
        joueurs[i].nom = nom;
        joueurs[i].score = 0;
        joueurs[i].actif = true;
        joueurs[i].questionActuelle = 0;
        nbJoueursConnectes++;
        break;
      }
    }
  }

  server.sendHeader("Location", "/quiz?nom=" + nom);
  server.send(303);
}