// #include "config.h"
// #include <Arduino.h>
// #include "joueur.h"

// // Page du quiz pour un joueur
// void pageQuiz() {
//   if (!server.hasArg("nom")) {
//     server.sendHeader("Location", "/");
//     server.send(303);
//     return;
//   }

//   String nom = server.arg("nom");
//   int idxJoueur = trouverJoueur(nom);
  
//   if (idxJoueur < 0) {
//     server.sendHeader("Location", "/");
//     server.send(303);
//     return;
//   }

//   Joueur &j = joueurs[idxJoueur];
  
//   String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
//   html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
//   html += "<link rel='stylesheet' href='/style.css'>";
//   html += "<title>Quiz - " + nom + "</title></head><body>";
//   html += "<div class='container'>";
//   html += "<div class='header'>";
//   html += "<h1>👤 " + nom + "</h1>";
//   html += "<div class='score-bar'>Score: " + String(j.score) + " / " + String(j.questionActuelle) + "</div>";
  
//   int progressPercent = (j.questionActuelle * 100) / nbQuestionsQuiz;
//   html += "<div class='progress-container'>";
//   html += "<div class='progress-bar' style='width:" + String(progressPercent) + "%'></div>";
//   html += "</div></div>";

//   if (quizTermine) {
//     html += "<div class='final-screen'>";
//     html += "<h2>Quiz terminé ! 🎉</h2>";
//     html += "<div class='score-display'>" + String(j.score) + "/" + String(nbQuestionsQuiz) + "</div>";
//     html += "<div class='message'>Excellent travail !</div>";
//     html += "<a href='/classement' class='restart-btn'>Voir le classement</a>";
//     html += "</div>";
//   } else if (j.questionActuelle >= nbQuestionsQuiz) {
//     html += "<div class='question-card'>";
//     html += "<h2>Vous avez terminé ! ✅</h2>";
//     html += "<div class='message'>En attente des autres joueurs...</div>";
//     html += "</div>";
//     html += "<meta http-equiv='refresh' content='3'>";
//   } else {
//     Question &q = quiz[questionsSelectionnees[j.questionActuelle]];
//     html += "<div class='question-card'>";
//     html += "<h2>" + String(q.texte) + "</h2>";
//     html += "<div class='answers-grid'>";
//     html += "<a href='/repondre?nom=" + nom + "&r=A' class='answer-btn btn-red'>" + String(q.reponses[0]) + "</a>";
//     html += "<a href='/repondre?nom=" + nom + "&r=B' class='answer-btn btn-blue'>" + String(q.reponses[1]) + "</a>";
//     html += "<a href='/repondre?nom=" + nom + "&r=C' class='answer-btn btn-yellow'>" + String(q.reponses[2]) + "</a>";
//     html += "<a href='/repondre?nom=" + nom + "&r=D' class='answer-btn btn-green'>" + String(q.reponses[3]) + "</a>";
//     html += "</div></div>";
//   }

//   html += "</div></body></html>";
//   server.send(200, "text/html", html);
// }
