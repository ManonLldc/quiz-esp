#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "./config/config.h"
#include "./models/joueur.h"
#include "./ui/pageConnexion.h"
#include "./quiz/quiz.h"
#include "./ui/pageQuiz.h"
#include "./ui/pageClassement.h"
#include <LittleFS.h>


void setup() {
  Serial.begin(115200);
  
    if (!LittleFS.begin()) {
        Serial.println("Erreur: Impossible de monter LittleFS");
        return;
    }

    Serial.println("LittleFS monté avec succès !");
  
  // Initialisation des joueurs
  for (int i = 0; i < maxJoueurs; i++) {
    joueurs[i].actif = false;
  }
  
  WiFi.softAP(ssid, password);
  Serial.println("AP démarré, IP : " + WiFi.softAPIP().toString());

    
server.on("/css/style.css", HTTP_GET, []() {
  File file = LittleFS.open("/css/style.css", "r");
  if (!file) {
    server.send(404, "text/plain", "CSS file not found");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
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