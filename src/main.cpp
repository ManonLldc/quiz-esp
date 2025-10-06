#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "data.h"
#include "style.h"

const char* ssid = "JeuBuzzer";
const char* password = "12345678";

ESP8266WebServer server(80);

// Configuration quiz
const int nbQuestionsQuiz = 10;
int questionsSelectionnees[nbQuestionsQuiz];
int indexQuestion = 0;
int score = 0;

// Sélectionne 10 indices uniques aléatoires parmi les questions disponibles
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

// Page principale du joueur
void pageJoueur() {
  String page = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Quiz Buzzer</title>";
  page += css;
  page += "</head><body><div class='container'>";
  page += "<h1> Quiz </h1>";

  if (indexQuestion >= nbQuestionsQuiz) {
    // Fin du quiz
    page += "<div class='final-score'>";
    page += "<h2>🎉 Terminé !</h2>";
    page += "<div class='score-number'>" + String(score) + "/" + String(nbQuestionsQuiz) + "</div>";

    float pourcentage = (score * 100.0) / nbQuestionsQuiz;
    if (pourcentage == 100) {
      page += "<p style='font-size:1.3em; margin-top:20px;'>🏆 Parfait ! Score maximum !</p>";
    } else if (pourcentage >= 75) {
      page += "<p style='font-size:1.3em; margin-top:20px;'>👏 Excellent travail !</p>";
    } else if (pourcentage >= 50) {
      page += "<p style='font-size:1.3em; margin-top:20px;'>👍 Bien joué !</p>";
    } else {
      page += "<p style='font-size:1.3em; margin-top:20px;'>💪 Retente ta chance !</p>";
    }

    page += "<a href='/reset'><button class='btn btn-reset'>🔁 Recommencer</button></a>";
    page += "</div>";
  } else {
    // Affichage de la question en cours
    int progress = (indexQuestion * 100) / nbQuestionsQuiz;
    page += "<div class='score'>Score : " + String(score) + " | Question " + String(indexQuestion + 1) + "/" + String(nbQuestionsQuiz) + "</div>";
    page += "<div class='progress'><div class='progress-bar' style='width:" + String(progress) + "%'></div></div>";

    Question &q = quiz[questionsSelectionnees[indexQuestion]];
    page += "<h2>" + q.texte + "</h2>";

for (int i = 0; i < 4; i++) {
  char rep = 'A' + i;
  String couleurClasse = "btn-" + String((char)tolower(rep)); // btn-a, btn-b, etc.
  page += "<a href='/repondre?r=" + String(rep) + "'><button class='btn " + couleurClasse + "'>";
  page += "<strong>" + String(rep) + ".</strong> " + q.reponses[i];
  page += "</button></a>";
}
  }

  page += "</div></body></html>";
  server.send(200, "text/html; charset=UTF-8", page);
}

// Traite la réponse de l'utilisateur
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

// Réinitialise le quiz
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

  genererQuestionsAleatoires(); // Génère une première fois
  server.begin();
  Serial.println("Serveur HTTP lancé !");
}

void loop() {
  server.handleClient();
}
