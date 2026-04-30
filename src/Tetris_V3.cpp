#include <GameBoy.h>
#include "Blocks.h" // Підключаємо наші фігури

GameBoy gb;


int rot = 0;
int x = 2, y = -1;

void drawBlock(byte arr[4][4], int x, int y) {
    for (int i = 0; i < 4; i++) {       
        for (int j = 0; j < 4; j++) {     
            if (arr[j][i] == 1) {           
                gb.drawPoint(x + i, y + j);   
            }
        }
    }
}

void createBlock(int num) {
    x = 2; y = -1; rot = random (0, 4);
    if(num == 0) gb.generateBlock(gb.block, I_Block_1, I_Block_2, I_Block_3, I_Block_4);
    if(num == 1) gb.generateBlock(gb.block, Z_Block_1, Z_Block_2, Z_Block_3, Z_Block_4);
    if(num == 2) gb.generateBlock(gb.block, S_Block_1, S_Block_2, S_Block_3, S_Block_4);
    if(num == 3) gb.generateBlock(gb.block, L_Block_1, L_Block_2, L_Block_3, L_Block_4);
    if(num == 4) gb.generateBlock(gb.block, J_Block_1, J_Block_2, J_Block_3, J_Block_4);
    if(num == 5) gb.generateBlock(gb.block, T_Block_1, T_Block_2, T_Block_3, T_Block_4);
    if(num == 6) gb.generateBlock(gb.block, O_Block_1, O_Block_2, O_Block_3, O_Block_4);
}

void makeMove() {
    if (gb.getKey() == 4) {
        if (!gb.checkBlockCollision(gb.block[rot], x - 1, y)) {
            x--;
        }
    }
    if (gb.getKey() == 5) {
        if (!gb.checkBlockCollision(gb.block[rot], x + 1, y)) {
            x++;
        }
    }

    if (gb.getKey() == 1) {
        if (!gb.checkBlockCollision(gb.block[rot + 1], x + 1, y)) {
            if (rot == 3) {
                rot = 0;
            } else {
                rot++;
            }
        }
    }
}

void setup() {
    randomSeed(analogRead(0) + analogRead(5));
    gb.begin(0);
    createBlock(random(0, 7));
}


void loop() {
    makeMove();
    if (gb.checkBlockCollision(gb.block[rot], x, y + 1)) {
        gb.memBlock(gb.block[rot], x, y);
        createBlock(random(0, 7));
    } else {
        y++;
    }
    gb.drawDisplay();
    drawBlock(gb.block[rot], x, y);
    delay(100);
}