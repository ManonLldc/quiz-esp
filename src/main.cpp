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

void pageJoueur() {
  String page = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<title>Quiz Buzzer</title>";
  page += css;
  page += "</head><body><div class='container'>";

  if (indexQuestion >= nbQuestionsQuiz) {
    // Écran final
    page += "<div class='final-screen'>";
    page += "<h2>🎉 Quiz Terminé !</h2>";
    page += "<div class='score-display'>" + String(score) + "/" + String(nbQuestionsQuiz) + "</div>";

    float pourcentage = (score * 100.0) / nbQuestionsQuiz;
    if (pourcentage == 100) {
      page += "<p class='message'>🏆 Score parfait ! Incroyable !</p>";
    } else if (pourcentage >= 75) {
      page += "<p class='message'>⭐ Excellent travail !</p>";
    } else if (pourcentage >= 50) {
      page += "<p class='message'>👍 Bien joué !</p>";
    } else {
      page += "<p class='message'>💪 Continue, tu vas y arriver !</p>";
    }

    page += "<a href='/reset'><button class='restart-btn'>🔁 Rejouer</button></a>";
    page += "</div>";
  } else {
    // Question en cours
    int progress = (indexQuestion * 100) / nbQuestionsQuiz;
    
    page += "<div class='header'>";
    page += "<h1>⚡ QUIZ TIME</h1>";
    page += "<div class='score-bar'>⭐ " + String(score) + " points | Question " + String(indexQuestion + 1) + "/" + String(nbQuestionsQuiz) + "</div>";
    page += "<div class='progress-container'><div class='progress-bar' style='width:" + String(progress) + "%'></div></div>";
    page += "</div>";

    Question &q = quiz[questionsSelectionnees[indexQuestion]];
    page += "<div class='question-card'>";
    page += "<h2>" + q.texte + "</h2>";
    page += "<div class='answers-grid'>";

    const char* colors[] = {"red", "blue", "yellow", "green"};
    // const char* shapes[] = {"▲", "◆", "●", "■"};
    
    for (int i = 0; i < 4; i++) {
      char rep = 'A' + i;
      page += "<a href='/repondre?r=" + String(rep) + "' style='text-decoration:none;'>";
      page += "<button class='answer-btn btn-" + String(colors[i]) + "'>";
      // page += "<span class='symbol'>" + String(shapes[i]) + "</span>";
      page += q.reponses[i];
      page += "</button></a>";
    }

    page += "</div></div>";
  }

  page += "</div></body></html>";
  server.send(200, "text/html; charset=UTF-8", page);
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