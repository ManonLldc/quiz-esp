#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "globals.h"
#include "pages.h"
#include "data.h"

void pageJoueur() {
    String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width, initial-scale=1.0'>
<title>Quiz Buzzer</title>
)"rawliteral";

    page += css; // ton CSS depuis globals
    page += R"rawliteral(
</head>
<body>
<div class='container'>
)rawliteral";

    if (indexQuestion >= nbQuestionsQuiz) {
        // Écran final
        page += "<div class='final-screen'>";
        page += "<h2>🎉 Quiz Terminé !</h2>";
        page += "<div class='score-display'>" + String(score) + "/" + String(nbQuestionsQuiz) + "</div>";

        float pourcentage = (score * 100.0) / nbQuestionsQuiz;
        if (pourcentage == 100) page += "<p class='message'>🏆 Score parfait ! Incroyable !</p>";
        else if (pourcentage >= 75) page += "<p class='message'>⭐ Excellent travail !</p>";
        else if (pourcentage >= 50) page += "<p class='message'>👍 Bien joué !</p>";
        else page += "<p class='message'>💪 Continue, tu vas y arriver !</p>";

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

        const char* colors[] = {"red","blue","yellow","green"};

        for (int i = 0; i < 4; i++) {
            char rep = 'A' + i;
            page += "<a href='/repondre?r=" + String(rep) + "' style='text-decoration:none;'>";
            page += "<button class='answer-btn btn-" + String(colors[i]) + "'>";
            page += q.reponses[i];
            page += "</button></a>";
        }

        page += "</div></div>";
    }

    page += "</div></body></html>";

    server.send(200, "text/html; charset=UTF-8", page);
}
