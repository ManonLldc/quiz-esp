#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "data.h"
#include "style.h"
#include "pages.h"
#include "globals.h"

// Réseau Wi-Fi
const char* ssid = "JeuBuzzer";
const char* password = "12345678";

// Serveur web
ESP8266WebServer server(80);

// Configuration quiz
const int nbQuestionsQuiz = 5;
int questionsSelectionnees[nbQuestionsQuiz];
int indexQuestion = 0;
int score = 0;

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

void repondre() {
  if (!server.hasArg("r")) {
    server.sendHeader("Location", "/");
    server.send(303);
    return;
  }

  char r = server.arg("r").charAt(0);
  Question &q = quiz[questionsSelectionnees[indexQuestion]];

  if (r == q.correct) {
    score++;
  }

  indexQuestion++;
  server.sendHeader("Location", "/");
  server.send(303);
}

void resetQuiz() {
  indexQuestion = 0;
  score = 0;
  genererQuestionsAleatoires();
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("AP démarré, IP : " + WiFi.softAPIP().toString());

  server.on("/", pageJoueur);
  server.on("/repondre", repondre);
  server.on("/reset", resetQuiz);

  genererQuestionsAleatoires();
  server.begin();
  Serial.println("Serveur HTTP lancé !");
}

void loop() {
  server.handleClient();
}
