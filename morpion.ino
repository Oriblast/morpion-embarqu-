#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuration OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configuration joystick
#define JOY_X_PIN 34
#define JOY_Y_PIN 35
#define JOY_BTN_PIN 32

// Grille de jeu
char grid[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

// position actuelle du curseur
int cursorX = 0, cursorY = 0;

// Variables de jeu
int currentPlayer = 1;  // 1 = X, 2 = O
bool gameOver = false;


void setup() {
  Serial.begin(9600);

  // Initialiser l'écran OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erreur de communication avec l'écran OLED"));
    for (;;);
  }

  // Effacer l'écran et afficher la grille
  display.clearDisplay();
  display.display();
  
  pinMode(JOY_BTN_PIN, INPUT_PULLUP);  // Bouton poussoir du joystick
}

void loop() {
  if (!gameOver) {
    updateJoystick();
    drawGrid();
    checkWin();
  } else {
    displayGameOver();
  }

  delay(100); 
}

void updateJoystick() {
  int xVal = analogRead(JOY_X_PIN);
  int yVal = analogRead(JOY_Y_PIN);
  int buttonState = digitalRead(JOY_BTN_PIN);

  // Mouvement du curseur
  if (xVal < 1000) cursorX = max(0, cursorX - 1);  // Gauche
  if (xVal > 3000) cursorX = min(2, cursorX + 1);  // Droite
  if (yVal < 1000) cursorY = max(0, cursorY - 1);  // Haut
  if (yVal > 3000) cursorY = min(2, cursorY + 1);  // Bas

  //(appui sur le bouton du joystick)
  if (buttonState == LOW && grid[cursorY][cursorX] == ' ') {
    grid[cursorY][cursorX] = (currentPlayer == 1) ? 'X' : 'O';
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
  }
}

// Dessine la grille
void drawGrid() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Dessiner la grille
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      int posX = x * 40;
      int posY = y * 20;

      // Afficher le curseur
      if (x == cursorX && y == cursorY) {
        display.drawRect(posX, posY, 40, 20, SSD1306_WHITE);
      }

      // Afficher X ou O
      display.setCursor(posX + 10, posY + 5);
      display.print(grid[y][x]);
    }
  }

  display.display();
}

// Vérifie les conditions de victoire
void checkWin() {
  // Vérifier les lignes, colonnes, et diagonales
  for (int i = 0; i < 3; i++) {
    if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ') gameOver = true;
    if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ') gameOver = true;
  }
  if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ') gameOver = true;
  if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ') gameOver = true;
}

// Affiche le message de fin de partie
void displayGameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.print("Game Over!");
  display.display();
}
