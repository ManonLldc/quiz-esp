const char* css = R"(
<style>
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

body {
  font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  padding: 20px;
}

.container {
  background: white;
  border-radius: 20px;
  box-shadow: 0 20px 60px rgba(0,0,0,0.3);
  padding: 40px;
  max-width: 600px;
  width: 100%;
  animation: slideIn 0.5s ease;
}

@keyframes slideIn {
  from {
    opacity: 0;
    transform: translateY(-30px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

h1 {
  color: #667eea;
  text-align: center;
  margin-bottom: 30px;
  font-size: 2.5em;
}

.score {
  background: linear-gradient(135deg, #667eea, #764ba2);
  color: white;
  padding: 15px;
  border-radius: 10px;
  text-align: center;
  margin-bottom: 20px;
  font-size: 1.2em;
}

h2 {
  color: #333;
  margin-bottom: 30px;
  font-size: 1.5em;
  line-height: 1.5;
}

.btn {
  display: block;
  width: 100%;
  padding: 15px 20px;
  margin: 10px 0;
  border: none;
  border-radius: 10px;
  background: #f0f0f0;
  color: #333;
  font-size: 1.1em;
  cursor: pointer;
  transition: all 0.3s ease;
  text-align: left;
}

a {
  text-decoration: none;
}

.btn {
  display: block;
  color: white;
  border: none;
  padding: 14px 20px;
  margin: 10px auto;
  border-radius: 8px;
  font-size: 1.2em;
  cursor: pointer;
  width: 90%;
  max-width: 400px;
  transition: transform 0.1s ease, opacity 0.3s ease;
}

.btn:hover {
  transform: scale(1.05);
  opacity: 0.9;
}

/* Couleurs selon la lettre */
.btn-a {
  background-color: #4CAF50; /* Vert */
}

.btn-b {
  background-color: #FFD700; /* Jaune */
  color: black; /* Meilleure lisibilité */
}

.btn-c {
  background-color: #2196F3; /* Bleu */
}

.btn-d {
  background-color: #F44336; /* Rouge */
}

/* Bouton de réinitialisation */
.btn-reset {
  background-color: #6c757d;
  color: white;
}

.btn-reset:hover {
  background-color: #5a6268;
}
  
.btn:hover {
  background: #667eea;
  color: white;
  transform: translateX(10px);
  box-shadow: 0 5px 15px rgba(102,126,234,0.4);
}

.btn-reset {
  background: linear-gradient(135deg, #667eea, #764ba2);
  color: white;
  text-align: center;
  font-size: 1.2em;
  margin-top: 30px;
}

.btn-reset:hover {
  transform: scale(1.05);
  box-shadow: 0 10px 25px rgba(102,126,234,0.5);
}

.progress {
  background: #e0e0e0;
  height: 8px;
  border-radius: 10px;
  margin-bottom: 30px;
  overflow: hidden;
}

.progress-bar {
  background: linear-gradient(90deg, #667eea, #764ba2);
  height: 100%;
  transition: width 0.3s ease;
}

.final-score {
  text-align: center;
  padding: 40px 20px;
}

.final-score h2 {
  font-size: 2em;
  color: #667eea;
  margin-bottom: 20px;
}

.score-number {
  font-size: 4em;
  font-weight: bold;
  background: linear-gradient(135deg, #667eea, #764ba2);
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  background-clip: text;
}
</style>
)";