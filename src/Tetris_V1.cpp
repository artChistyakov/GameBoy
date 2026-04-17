#include <GameBoy.h>
#include "Blocks.h" // Підключаємо наш файл з фігурами!

GameBoy gb;

void setup() {
  gb.begin(0);
}

// Функція "Художник", яка малює будь-який переданий їй масив 4x4
void drawBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {       // Перебираємо стовпці (X)
    for (int j = 0; j < 4; j++) {     // Перебираємо рядки (Y)
      if (arr[j][i] == 1) {           // Якщо в трафареті є 1...
        gb.drawPoint(x + i, y + j);   // ...малюємо її на екрані зі зсувом
      }
    }
  }
}

void loop() {
  // Анімація обертання фігури "I" (Палка)
  
  drawBlock(I_Block_1, 3, 0); // Малюємо 1-й стан у координаті (3,0)
  delay(500);
  gb.clearDisplay();

  drawBlock(I_Block_2, 3, 0); // Малюємо 2-й стан (поворот 90)
  delay(500);
  gb.clearDisplay();

  drawBlock(I_Block_3, 3, 0); // Малюємо 3-й стан (поворот 180)
  delay(500);
  gb.clearDisplay();

  drawBlock(I_Block_4, 3, 0); // Малюємо 4-й стан (поворот 270)
  delay(500);
  gb.clearDisplay();
}

