#include <GameBoy.h>
#include "Blocks.h"

GameBoy gb;

int paddleX = 3;
int paddleY = 14;

int ballX = 4;
int ballY = 13;
int directionX = 1;
int directionY = -1;

void setup() {
  gb.begin(0);
}

void drawPaddle(byte arr[3], int x, int y) {
  for (int i = 0; i < 3; i++) {
    if (arr[i] == 1) {
      gb.drawPoint(x + i, y);
    }
  }
}

void makePaddle() {
  if (gb.getKey() == 4 && paddleX > 0) {
    paddleX--;
  }
  if (gb.getKey() == 5 && paddleX < 5) {
    paddleX++;
  }
}

void checkCollision() {
  if (ballX <= 0 || ballX >= 7) directionX = -directionX;
  if (ballY <= 0 || ballY >= 15) directionY = -directionY;

  if (ballY == paddleY - 1 && ballX >= paddleX && ballX <= paddleX + 3) {
    directionY = -1;
  }
}

void ball() {
  ballX += directionX;
  ballY += directionY;
  checkCollision();
  gb.drawPoint(ballX, ballY);
}

void loop() {
  gb.drawDisplay();
  ball();
  makePaddle();
  drawPaddle(paddle, paddleX, paddleY);
  delay(200); 
}