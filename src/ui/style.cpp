const char* css = R"rawliteral(
<style>
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

body {
  font-family: 'Montserrat', -apple-system, BlinkMacSystemFont, 'Segoe UI', Arial, sans-serif;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 20px;
}

.container {
  width: 100%;
  max-width: 800px;
  animation: slideIn 0.5s ease-out;
}

@keyframes slideIn {
  from {
    opacity: 0;
    transform: translateY(-20px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

.header {
  text-align: center;
  color: white;
  margin-bottom: 30px;
}

.header h1 {
  font-size: 2.5em;
  font-weight: 900;
  text-shadow: 0 4px 6px rgba(0,0,0,0.2);
  margin-bottom: 10px;
}

.score-bar {
  background: rgba(255,255,255,0.2);
  padding: 15px 25px;
  border-radius: 50px;
  color: white;
  font-size: 1.1em;
  font-weight: 700;
  display: inline-block;
  backdrop-filter: blur(10px);
}

.progress-container {
  width: 100%;
  height: 8px;
  background: rgba(255,255,255,0.3);
  border-radius: 10px;
  overflow: hidden;
  margin-top: 15px;
}

.progress-bar {
  height: 100%;
  background: linear-gradient(90deg, #00ff88, #00d9ff);
  border-radius: 10px;
  transition: width 0.5s ease;
}

.question-card {
  background: white;
  border-radius: 20px;
  padding: 40px;
  box-shadow: 0 20px 60px rgba(0,0,0,0.3);
  margin-top: 30px;
  animation: popIn 0.4s cubic-bezier(0.68, -0.55, 0.265, 1.55);
}

@keyframes popIn {
  0% {
    opacity: 0;
    transform: scale(0.8);
  }
  100% {
    opacity: 1;
    transform: scale(1);
  }
}

.question-card h2 {
  font-size: 1.8em;
  color: #2c3e50;
  margin-bottom: 30px;
  font-weight: 800;
  text-align: center;
  line-height: 1.4;
}

.answers-grid {
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  gap: 15px;
  margin-top: 30px;
}

@media (max-width: 600px) {
  .answers-grid {
    grid-template-columns: 1fr;
  }
}

.answer-btn {
  position: relative;
  padding: 25px 20px;
  border: none;
  border-radius: 15px;
  font-size: 1.1em;
  font-weight: 700;
  color: white;
  cursor: pointer;
  transition: all 0.3s ease;
  text-decoration: none;
  display: flex;
  align-items: center;
  justify-content: center;
  min-height: 80px;
  box-shadow: 0 4px 15px rgba(0,0,0,0.2);
  text-align: center;
}

.answer-btn:hover {
  transform: translateY(-5px);
  box-shadow: 0 8px 25px rgba(0,0,0,0.3);
}

.answer-btn:active {
  transform: translateY(-2px);
}

.btn-red {
  background: linear-gradient(135deg, #e74c3c, #c0392b);
}

.btn-blue {
  background: linear-gradient(135deg, #3498db, #2980b9);
}

.btn-yellow {
  background: linear-gradient(135deg, #f39c12, #e67e22);
}

.btn-green {
  background: linear-gradient(135deg, #2ecc71, #27ae60);
}

.symbol {
  position: absolute;
  left: 15px;
  font-size: 1.5em;
  font-weight: 900;
}

.final-screen {
  background: white;
  border-radius: 20px;
  padding: 60px 40px;
  box-shadow: 0 20px 60px rgba(0,0,0,0.3);
  text-align: center;
  animation: popIn 0.6s cubic-bezier(0.68, -0.55, 0.265, 1.55);
}

.final-screen h2 {
  font-size: 2.5em;
  color: #2c3e50;
  margin-bottom: 20px;
  font-weight: 900;
}

.score-display {
  font-size: 5em;
  font-weight: 900;
  background: linear-gradient(135deg, #667eea, #764ba2);
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  margin: 30px 0;
}

.message {
  font-size: 1.5em;
  color: #7f8c8d;
  margin: 20px 0;
  font-weight: 600;
}

.restart-btn {
  background: linear-gradient(135deg, #667eea, #764ba2);
  color: white;
  border: none;
  padding: 18px 50px;
  border-radius: 50px;
  font-size: 1.2em;
  font-weight: 700;
  cursor: pointer;
  margin-top: 30px;
  box-shadow: 0 10px 30px rgba(102, 126, 234, 0.4);
  transition: all 0.3s ease;
  text-decoration: none;
  display: inline-block;
}

.restart-btn:hover {
  transform: translateY(-3px);
  box-shadow: 0 15px 40px rgba(102, 126, 234, 0.6);
}

.icon-triangle { content: '▲'; }
.icon-circle { content: '●'; }
.icon-square { content: '■'; }
.icon-diamond { content: '◆'; }
</style>
)rawliteral";
