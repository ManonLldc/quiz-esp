#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// #include "data.h"
#include "style.h"
#include "config.h"
#include "joueur.h"
#include "pageConnexion.h"
// #include "globals.h"
#include "quiz.h"



void setup() {
  Serial.begin(115200);
  
  // Initialisation des joueurs
  for (int i = 0; i < maxJoueurs; i++) {
    joueurs[i].actif = false;
  }
  
  WiFi.softAP(ssid, password);
  Serial.println("AP démarré, IP : " + WiFi.softAPIP().toString());

  server.on("/style.css", []() {
    server.send(200, "text/css", css);
  });
  
  server.on("/", pageConnexion);
  server.on("/connexion", HTTP_POST, connexion);
  server.on("/quiz", pageQuiz);
  server.on("/repondre", repondre);  // Accepte GET et POST
  server.on("/classement", pageClassement);
  server.on("/reset", HTTP_POST, resetQuiz);
  server.on("/demarrer", HTTP_POST, demarrerQuiz);

  genererQuestionsAleatoires();
  server.begin();
  Serial.println("Serveur HTTP lancé !");
}

void loop() {
  server.handleClient();
}