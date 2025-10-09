#include "./models/joueur.h"
#include "./globals/globals.h"
#include "./config/config.h"
#include "./quiz/quiz.h"

void pageClassement() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<link rel='stylesheet' href='/css/style.css'>";
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
