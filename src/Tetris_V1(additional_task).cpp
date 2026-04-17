#include <GameBoy.h>
#include "Blocks.h" // Підключаємо наші фігури

GameBoy gb;

// Змінна, яка пам'ятає номер поточної фігури (від 0 до 6, бо фігур всього 7)
int currentFigure = 0; 

void setup() {
    gb.begin(0);
    // Одразу малюємо першу фігуру при включенні
    showFigure(); 
}

// Наш "Художник", який малює будь-який переданий йому масив
void drawBlock(byte arr[4][4], int x, int y) {
    for (int i = 0; i < 4; i++) {       
        for (int j = 0; j < 4; j++) {     
            if (arr[j][i] == 1) {           
                gb.drawPoint(x + i, y + j);   
            }
        }
    }
}

// Функція, яка вирішує, яку саме фігуру зараз малювати
void showFigure() {
    gb.clearDisplay(); // Очищуємо екран від попередньої фігури

  // Малюємо фігуру по центру екрану (координати x=2, y=6)
    switch (currentFigure) {
        case 0: drawBlock(I_Block_1, 2, 6); break; // Палка
        case 1: drawBlock(J_Block_1, 2, 6); break; // J-блок
        case 2: drawBlock(L_Block_1, 2, 6); break; // L-блок
        case 3: drawBlock(O_Block_1, 2, 6); break; // Квадрат
        case 4: drawBlock(S_Block_1, 2, 6); break; // S-блок
        case 5: drawBlock(T_Block_1, 2, 6); break; // T-блок
        case 6: drawBlock(Z_Block_1, 2, 6); break; // Z-блок
    }
}

// ФУНКЦІЯ З ДОДАТКОВОГО ЗАВДАННЯ: Перемикання кнопок
void changeFigure() {
    // Якщо натиснута кнопка "Вправо" (код 5)
    if (gb.getKey() == 5) {
        currentFigure++; // Збільшуємо номер фігури на 1
    
        // Якщо доклацали до кінця (більше 6), повертаємось на першу (0)
        if (currentFigure > 6) {
            currentFigure = 0;
        }
    
        showFigure(); // Оновлюємо екран
        delay(250);   // Затримка, щоб від одного натискання не пролетіло 5 фігур
    }

    // Якщо натиснута кнопка "Вліво" (код 4)
    else if (gb.getKey() == 4) {
        currentFigure--; // Зменшуємо номер фігури
    
        // Якщо клацаємо вліво від першої фігури, переходимо на останню (6)
        if (currentFigure < 0) {
            currentFigure = 6;
        }
        showFigure(); // Оновлюємо екран
        delay(250);   // Затримка від "залипання" кнопки
    }
}

void loop() {
  // У головному циклі ми просто постійно чекаємо на натискання кнопок
    changeFigure();
}