#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "data.h"
#include "style.h"
#include "config.h"
#include "joueur.h"
#include "pageConnexion.h"
#include "globals.h"

// Configuration quiz
const int nbQuestionsQuiz = 10;
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

// Page du quiz pour un joueur
void pageQuiz() {
  if (!server.hasArg("nom")) {
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
  
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<link rel='stylesheet' href='/style.css'>";
  html += "<title>Quiz - " + nom + "</title></head><body>";
  html += "<div class='container'>";
  html += "<div class='header'>";
  html += "<h1>👤 " + nom + "</h1>";
  html += "<div class='score-bar'>Score: " + String(j.score) + " / " + String(j.questionActuelle) + "</div>";
  
  int progressPercent = (j.questionActuelle * 100) / nbQuestionsQuiz;
  html += "<div class='progress-container'>";
  html += "<div class='progress-bar' style='width:" + String(progressPercent) + "%'></div>";
  html += "</div></div>";

  if (quizTermine) {
    html += "<div class='final-screen'>";
    html += "<h2>Quiz terminé ! 🎉</h2>";
    html += "<div class='score-display'>" + String(j.score) + "/" + String(nbQuestionsQuiz) + "</div>";
    html += "<div class='message'>Excellent travail !</div>";
    html += "<a href='/classement' class='restart-btn'>Voir le classement</a>";
    html += "</div>";
  } else if (j.questionActuelle >= nbQuestionsQuiz) {
    html += "<div class='question-card'>";
    html += "<h2>Vous avez terminé ! ✅</h2>";
    html += "<div class='message'>En attente des autres joueurs...</div>";
    html += "</div>";
    html += "<meta http-equiv='refresh' content='3'>";
  } else {
    Question &q = quiz[questionsSelectionnees[j.questionActuelle]];
    html += "<div class='question-card'>";
    html += "<h2>" + String(q.texte) + "</h2>";
    html += "<div class='answers-grid'>";
    html += "<a href='/repondre?nom=" + nom + "&r=A' class='answer-btn btn-red'>" + String(q.reponses[0]) + "</a>";
    html += "<a href='/repondre?nom=" + nom + "&r=B' class='answer-btn btn-blue'>" + String(q.reponses[1]) + "</a>";
    html += "<a href='/repondre?nom=" + nom + "&r=C' class='answer-btn btn-yellow'>" + String(q.reponses[2]) + "</a>";
    html += "<a href='/repondre?nom=" + nom + "&r=D' class='answer-btn btn-green'>" + String(q.reponses[3]) + "</a>";
    html += "</div></div>";
  }

  html += "</div></body></html>";
  server.send(200, "text/html", html);
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

// Page de classement
void pageClassement() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<link rel='stylesheet' href='/style.css'>";
  html += "<title>Classement</title></head><body>";
  html += "<div class='container'>";
  html += "<div class='header'>";
  html += "<h1>🏆 Classement Final</h1>";
  html += "</div>";

  // Tri des joueurs par score décroissant
  Joueur classement[maxJoueurs];
  int nbJoueurs = 0;
  for (int i = 0; i < maxJoueurs; i++) {
    if (joueurs[i].actif) {
      classement[nbJoueurs++] = joueurs[i];
    }
  }

  // Tri à bulles
  for (int i = 0; i < nbJoueurs - 1; i++) {
    for (int j = 0; j < nbJoueurs - i - 1; j++) {
      if (classement[j].score < classement[j + 1].score) {
        Joueur temp = classement[j];
        classement[j] = classement[j + 1];
        classement[j + 1] = temp;
      }
    }
  }

  html += "<div class='question-card'>";
  
  // Podium pour le top 3
  if (nbJoueurs > 0) {
    html += "<div style='display: flex; align-items: flex-end; justify-content: center; gap: 20px; margin-bottom: 40px;'>";
    
    // 2ème place
    if (nbJoueurs > 1) {
      html += "<div style='text-align: center; flex: 1; max-width: 150px;'>";
      html += "<div style='font-size: 3em;'>🥈</div>";
      html += "<div style='background: linear-gradient(135deg, #95a5a6, #7f8c8d); color: white; ";
      html += "padding: 30px 20px; border-radius: 15px; margin-top: 10px;'>";
      html += "<div style='font-size: 1.8em; font-weight: 900;'>" + String(classement[1].score) + "</div>";
      html += "<div style='font-size: 0.9em; margin-top: 5px;'>" + classement[1].nom + "</div>";
      html += "</div></div>";
    }
    
    // 1ère place (plus haute)
    html += "<div style='text-align: center; flex: 1; max-width: 150px;'>";
    html += "<div style='font-size: 4em;'>🥇</div>";
    html += "<div style='background: linear-gradient(135deg, #f39c12, #e67e22); color: white; ";
    html += "padding: 40px 20px; border-radius: 15px; margin-top: 10px; box-shadow: 0 10px 30px rgba(243,156,18,0.4);'>";
    html += "<div style='font-size: 2.2em; font-weight: 900;'>" + String(classement[0].score) + "</div>";
    html += "<div style='font-size: 1em; margin-top: 5px;'>" + classement[0].nom + "</div>";
    html += "</div></div>";
    
    // 3ème place
    if (nbJoueurs > 2) {
      html += "<div style='text-align: center; flex: 1; max-width: 150px;'>";
      html += "<div style='font-size: 2.5em;'>🥉</div>";
      html += "<div style='background: linear-gradient(135deg, #e67e22, #d35400); color: white; ";
      html += "padding: 25px 20px; border-radius: 15px; margin-top: 10px;'>";
      html += "<div style='font-size: 1.6em; font-weight: 900;'>" + String(classement[2].score) + "</div>";
      html += "<div style='font-size: 0.85em; margin-top: 5px;'>" + classement[2].nom + "</div>";
      html += "</div></div>";
    }
    
    html += "</div>";
  }

  // Liste complète
  if (nbJoueurs > 3) {
    html += "<div style='margin-top: 30px;'>";
    for (int i = 3; i < nbJoueurs; i++) {
      html += "<div style='display: flex; justify-content: space-between; align-items: center; ";
      html += "padding: 15px 25px; margin: 10px 0; background: #f8f9fa; border-radius: 15px; ";
      html += "border-left: 5px solid #667eea;'>";
      html += "<div style='font-weight: 700; color: #2c3e50;'>";
      html += "<span style='color: #95a5a6; margin-right: 15px;'>#" + String(i + 1) + "</span>";
      html += classement[i].nom + "</div>";
      html += "<div style='font-size: 1.3em; font-weight: 900; color: #667eea;'>";
      html += String(classement[i].score) + "/" + String(nbQuestionsQuiz) + "</div>";
      html += "</div>";
    }
    html += "</div>";
  }

  html += "<form action='/reset' method='POST' style='margin-top: 30px; text-align: center;'>";
  html += "<button type='submit' class='restart-btn'>🔄 Nouveau Quiz</button>";
  html += "</form>";
  
  html += "</div></div></body></html>";
  server.send(200, "text/html", html);
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
