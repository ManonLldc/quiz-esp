#include "./config/config.h"
#include "./models/joueur.h"
#include <Arduino.h>
#include "./globals/globals.h"

// Page de connexion
void pageConnexion() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<link rel='stylesheet' href='/css/style.css'>";
  html += "<title>Quiz - Connexion</title></head><body>";
  html += "<div class='container'>";
  html += "<div class='header'>";
  html += "<h1>Quiz</h1>";
  html += "</div>";
  
  html += "<div class='question-card'>";
  
  if (quizTermine) {
    html += "<div class='message' style='color: #e74c3c; margin-bottom: 20px;'>⚠️ Le quiz est terminé</div>";
  } else if (quizDemarre) {
    html += "<div class='message' style='color: #f39c12; margin-bottom: 20px;'>⏳ Quiz en cours...</div>";
  }
  
  html += "<h2 style='text-align: center; margin-bottom: 30px;'>👤 Connexion</h2>";
  html += "<form action='/connexion' method='POST' style='max-width: 400px; margin: 0 auto;'>";
  html += "<input type='text' name='nom' placeholder='Entrez votre nom' required ";
  html += "style='width: 100%; padding: 20px; border: 3px solid #e0e0e0; border-radius: 15px; ";
  html += "font-size: 1.2em; font-weight: 600; margin-bottom: 20px; transition: all 0.3s; ";
  html += "font-family: inherit;' ";
  html += "onfocus='this.style.borderColor=\"#667eea\"; this.style.boxShadow=\"0 0 0 4px rgba(102,126,234,0.1)\"' ";
  html += "onblur='this.style.borderColor=\"#e0e0e0\"; this.style.boxShadow=\"none\"'>";
  html += "<button type='submit' class='restart-btn' style='width: 100%; margin-top: 10px;'>Se connecter</button>";
  html += "</form>";
  
  if (nbJoueursConnectes > 0) {
    html += "<div style='margin-top: 40px; padding-top: 30px; border-top: 2px solid #e0e0e0;'>";
    html += "<h3 style='text-align: center; color: #2c3e50; margin-bottom: 20px;'>👥 Joueurs connectés (" + String(nbJoueursConnectes) + ")</h3>";
    html += "<div style='display: grid; grid-template-columns: repeat(auto-fill, minmax(150px, 1fr)); gap: 10px;'>";
    for (int i = 0; i < maxJoueurs; i++) {
      if (joueurs[i].actif) {
        html += "<div style='background: linear-gradient(135deg, #667eea, #a2794bff); color: white; ";
        html += "padding: 12px 20px; border-radius: 25px; text-align: center; font-weight: 700; ";
        html += "box-shadow: 0 4px 15px rgba(102,126,234,0.3);'>👤 " + joueurs[i].nom + "</div>";
      }
    }
    html += "</div></div>";
  }
  
  html += "</div></div></body></html>";
  server.send(200, "text/html", html);
}
