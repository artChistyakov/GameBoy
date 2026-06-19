#include <GameBoy.h>

#include  "BlocksAndMenu.h"

GameBoy gb;

//Menu var
int modes = 0;
int modeCount = 0;

//CAR
int enemy_x = 2;
int car_speed = 100;
int mycar_x = 2;
int mycar_y = 12;
volatile int line_y = 0;

//SNAKE
int snakeX[108];
int snakeY[108];

int up    = 0;
int right  = 1;
int bottom = 2;
int left   = 3;
int direction = right;

int eatX, eatY;

bool state;

int lenSnake = 7;
const int numRows = 8;
const int numCols = 16;

//TETRIS
int rot = 0;
int x = 2, y = -1;
int acc = 1;
int speed = 200;
int score = 0;
int level = 0;

//ARKANOID
int paddleX = 3;
int paddleY = 14;

int ballX = 4;
int ballY = 13;
int directionX = 1;
int directionY = -1;

bool stateLevel = true;
int numLevel = 1;

int countBricks = 0;
int scoreArkanoid = 0;


int modeSelector() {
  if (gb.getKey() == 4) {
    modeCount++;
    delay(250);
    if (modeCount > 3) {
      modeCount = 0;
    }
  } else if (gb.getKey() == 5) {
    modeCount--;
    delay(250);
    if (modeCount < 0) {
      modeCount = 3;
    }
  }
  return modeCount;
}



void enemyCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y - 1);
  gb.drawPoint(x - 1, y - 1);
  gb.drawPoint(x + 1, y - 1);
  gb.drawPoint(x, y - 2);
  gb.drawPoint(x - 1, y - 3);
  gb.drawPoint(x + 1, y - 3);
}

void playerCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y + 1);
  gb.drawPoint(x - 1, y + 1);
  gb.drawPoint(x + 1, y + 1);
  gb.drawPoint(x, y + 2);
  gb.drawPoint(x - 1, y + 3);
  gb.drawPoint(x + 1, y + 3);
}



void clearPlayerCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y + 1);
  gb.wipePoint(x - 1, y + 1);
  gb.wipePoint(x + 1, y + 1);
  gb.wipePoint(x, y + 2);
  gb.wipePoint(x - 1, y + 3);
  gb.wipePoint(x + 1, y + 3);
}

void clearEnemyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y - 1);
  gb.wipePoint(x - 1, y - 1);
  gb.wipePoint(x + 1, y - 1);
  gb.wipePoint(x, y - 2);
  gb.wipePoint(x - 1, y - 3);
  gb.wipePoint(x + 1, y - 3);
}

void createLine(int y) {
  gb.drawPoint(0, y);
  gb.drawPoint(0, y + 1);
  gb.drawPoint(0, y + 2);

  gb.drawPoint(7, y);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 2);
}

void clearLine(int y) {
  gb.wipePoint(0, y);
  gb.wipePoint(0, y + 1);
  gb.wipePoint(0, y + 2);

  gb.wipePoint(7, y);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 2);
}


bool Collision(int mycar_x, int mycar_y, int enemy_car_x, int enemy_car_y) {
  if (mycar_y == enemy_car_y and mycar_x == enemy_car_x) {
    return true;
  }
  if (mycar_x == enemy_car_x and enemy_car_y > 12 ) {
    return true;
  }
  return false;
}


void mainRaicing() {
  enemy_x = random(0, 10);
  if (enemy_x > 5) {
    enemy_x = 2;
  }
  else {
    enemy_x = 5;
  }
  for (int enemy_y = -3; enemy_y < 16; enemy_y++)
  {
    createLine(enemy_y);
    createLine(enemy_y + 5);
    createLine(enemy_y + 10);
    createLine(enemy_y + 15);
    createLine(enemy_y - 5);
    createLine(enemy_y - 10);
    createLine(enemy_y - 15);
    enemyCar(enemy_x, enemy_y + 4);
    if (gb.getKey() == 4) {
      mycar_x = 2;
      clearPlayerCar(5, 12);
    }
    else if (gb.getKey() == 5) {
      mycar_x = 5;
      clearPlayerCar(2, 12);
    }
    playerCar(mycar_x, mycar_y);
    if (Collision(mycar_x, mycar_y, enemy_x, enemy_y) == true) {
      gb.sound(COLLISION);
      gb.testMatrix(10);
      gb.clearDisplay();
      return;
    }
    if (enemy_y > 14) {
      gb.sound(SCORE);
    }
    delay(car_speed);
    clearLine(enemy_y);
    clearLine(enemy_y + 5);
    clearLine(enemy_y + 10);
    clearLine(enemy_y + 15);
    clearLine(enemy_y - 5);
    clearLine(enemy_y - 10);
    clearLine(enemy_y - 15);
    clearEnemyCar(enemy_x, enemy_y + 4);
  }
}




void makeMoveSnake() {
  if (gb.getKey() == 4 && direction != right) {
    direction = left;
  }
  if (gb.getKey() == 5 && direction != left) {
    direction = right;
  }
  if (gb.getKey() == 6 && direction != up) {
    direction = bottom;
  }
  if (gb.getKey() == 3 && direction != bottom) {
    direction = up;
  }
}

boolean isPartOfSnake(int x, int y) {
  for (int i = 0; i < lenSnake - 1; i++) {
    if ((x == snakeX[i]) && (y == snakeY[i])) {
      return true;
    }
  }
  return false;
}

void makeFruit() {
  eatX = random(0, 8);
  eatY = random(0, 16);
  while (isPartOfSnake(eatX, eatY)) {

    eatX = random(0, 8);
    eatY = random(0, 16);
  }
}


void loss() {
  delay(1000);
  gb.clearDisplay();
  for (int i = 0; i < lenSnake; i++) {
    snakeX[i] = 0;
    snakeY[i] = 0;
  }
  direction = right;
  eatX = 3;
  eatY = 3;
  lenSnake = 4;
  snakeX[0] = 4;
  snakeY[0] = 7;
}


void move() {
  if ((snakeX[0] == eatX) and (snakeY[0] == eatY)) {
    lenSnake++;
    makeFruit();
    gb.sound(SCORE);
  }
  for (int i = lenSnake - 1; i > 0; i--) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gb.sound(COLLISION);
      loss();
    }
  }
  for (int i = lenSnake - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  if (direction == up) {
    if (snakeY[0] == 0) {
      snakeY[0] = 15;
    } else {
      snakeY[0]--;
    }
  } else if (direction == bottom) {
    if (snakeY[0] == 15) {
      snakeY[0] = 0;
    } else {
      snakeY[0]++;
    }
  } else if (direction == left) {
    if (snakeX[0] == 0) {
      snakeX[0] = 7;
    } else {
      snakeX[0]--;
    }
  } else if (direction == right) {
    if (snakeX[0] == 7) {
      snakeX[0] = 0;
    } else {
      snakeX[0]++;
    }
  }
}

void drawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]);
  }
}

void drawFruit() {
  state = !state;
  if ( state == true) {
    gb.drawPoint(eatX, eatY);
  }
  else {
    gb.wipePoint(eatX, eatY);
  }
}

bool win() {
  if (score >= 20) {
    return true;
  }
  return false;
}

bool lossTetris() {
  if (gb.checkBlockCollision(gb.block[rot], x, 0)) {
    return true;
  }
  else {
    return false;
  }
}


void drawBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        gb.drawPoint(x + i, y + j);
      }
    }
  }
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

  if (gb.getKey() == 3) {
    if (!gb.checkBlockCollision(gb.block[rot + 1], x + 1, y)) {
      if (rot == 3) {
        rot = 0;
      } else {
        rot++;
      }
    }
  }
  if (gb.getKey() == 6) {
    acc = 4;
  } else {
    acc = 1;
  }
}




void createBlock(int num) {
  x = 2; y = -1; rot = random(0, 4);
  if (num == 0) gb.generateBlock(gb.block, I_Block_1, I_Block_2, I_Block_3, I_Block_4);
  if (num == 1) gb.generateBlock(gb.block, Z_Block_1, Z_Block_2, Z_Block_3, Z_Block_4);
  if (num == 2) gb.generateBlock(gb.block, S_Block_1, S_Block_2, S_Block_3, S_Block_4);
  if (num == 3) gb.generateBlock(gb.block, L_Block_1, L_Block_2, L_Block_3, L_Block_4);
  if (num == 4) gb.generateBlock(gb.block, J_Block_1, J_Block_2, J_Block_3, J_Block_4);
  if (num == 5) gb.generateBlock(gb.block, T_Block_1, T_Block_2, T_Block_3, T_Block_4);
  if (num == 6) gb.generateBlock(gb.block, O_Block_1, O_Block_2, O_Block_3, O_Block_4);
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

  if (ballY == paddleY - 1 && ballX >= paddleX && ballX <= paddleX + 3 ) {
    directionY = -1;
  }

  if (gb.checkCollision(ballX, ballY)) {
    gb.wipePoint(ballX, ballY);
    directionY = 1;
    gb.sound(SCORE);
    scoreArkanoid++;
  }
}

void ball() {
  ballX += directionX;
  ballY += directionY;
  checkCollision();
  gb.drawPoint(ballX, ballY);
}

void drawBricks(byte arr[4][8]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      if (arr[i][j] == 1) {
        gb.memDisplay(j, i);
        countBricks++;
      }
    }
  }
}


void memClear() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      gb.display[j][i] = 0;
    }
  }
}

void createLevel() {
  
  if (numLevel == 1 && stateLevel) {
    memClear();
    gb.clearDisplay();
    drawBricks(Block_level_1);
    stateLevel = false;
  }
  else if (numLevel == 2 && stateLevel) {
    memClear();
    gb.clearDisplay();
    drawBricks(Block_level_2);
    stateLevel = false;
  }
}

bool lossArkanoid() {
  if (ballY >= 14) {
    return true;
  }
  else {
    return false;
  }
}

bool winArkanoid() {
  if (scoreArkanoid >= countBricks) {
    return true;
  }
  return false;
}

void restart() {
  paddleX = 3;
  paddleY = 14;

  ballX = 4;
  ballY = 13;
  directionX = 1;
  directionY = -1;

  stateLevel = true;
  numLevel = 1;

  createLevel();
}



void mainMenu() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(i, j);
      gb.setLed(i, j, ARROWS[j][i]);
    }
  }
  if (modeSelector() == 0) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        gb.wipePoint(i, 8 + j);
        gb.setLed(i, 8 + j, CAR[j][i]);
      }
    }
  }
  if (modeSelector() == 1) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        gb.wipePoint(i, 8 + j);
        gb.setLed(i, 8 + j, SNAKE[j][i]);
      }
    }
  }
  if (modeSelector() == 2) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        gb.wipePoint(i, 8 + j);
        gb.setLed(i, 8 + j, TETRIS[j][i]);
      }
    }
  }
  if (modeSelector() == 3) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        gb.wipePoint(i, 8 + j);
        gb.setLed(i, 8 + j, ARKANOID[j][i]);
      }
    }
  }
}

//CAR
void gameCar() {
  mainRaicing();
}


//SNAKE

void gameSnake() {
  makeMoveSnake();
  move();
  gb.clearDisplay();
  drawSnake();
  drawFruit();
  delay(250);
}

//TETRIS
void gameTetris() {
  if (lossTetris() == true) {
    Serial.println("You lost the game");
  }

  if (lossTetris() == true) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
      }
    }
    gb.sound(COLLISION);
    gb.testMatrix(10);
  }
  if (win() == true) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
        gb.setLed(i, j, WIN[j][i]);
      }
    }
    delay(2000);
    gb.clearDisplay();
    score = 0;
    level = 0;
  }
  makeMove();
  if (gb.checkBlockCollision(gb.block[rot], x, y + 1)) {
    gb.memBlock(gb.block[rot], x, y);
    int lines = gb.fullLine();
    if (lines != 0) {
      score += lines;
      level += lines;
    }
    if (level >= 5) {
      gb.sound(SCORE);
      acc += 1;
      level = 0;
    }
    createBlock(random(0, 7));
  }
  else {
    y++;
  }
  gb.drawDisplay();
  drawBlock(gb.block[rot], x, y);
  delay(speed / acc);
}


//ARKANOID
void gameArkanoid() {
  createLevel();
  if (lossArkanoid() == true) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
      }
    }
    memClear();
    gb.sound(COLLISION);
    gb.testMatrix(10);
    restart();
  }

  if (winArkanoid() == true) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
        gb.setLed(i, j, WIN[j][i]);
      }
    }
    delay(2000);
    gb.clearDisplay();
    scoreArkanoid = 0;
    restart();
  }

  ball();
  makePaddle();
  drawPaddle(paddle, paddleX, paddleY);
  delay(100);
  gb.drawDisplay();
}

//MENU
void switchMode(int mode) {
  switch (mode) {
    case 0: mainMenu();
      break;
    case 1: gameCar();
      break;
    case 2: gameSnake();
      break;
    case 3: gameTetris();
      break;
    case 4: gameArkanoid();
  }
}

void setup() {
  gb.begin(8);
  randomSeed(analogRead(0) + analogRead(5));
  //CAR
  playerCar(mycar_x, mycar_y);
  //SNAKE
  snakeX[0] = 4;
  snakeY[0] = 7;
  makeFruit();

  //TETRIS
  createBlock(random(0, 7));

  //ARKANOID
  

}

void loop() {
  if (gb.getKey() == 2 and modeSelector() == 0) {
    gb.clearDisplay();
    modes = 1;
  } else if (gb.getKey() == 2 and modeSelector() == 1) {
    gb.clearDisplay();
    modes = 2;
  } else if (gb.getKey() == 2 and modeSelector() == 2) {
    gb.clearDisplay();
    modes = 3;
  } else if (gb.getKey() == 2 and modeSelector() == 3) {
    gb.clearDisplay();
    modes = 4;
  } else if (gb.getKey() == 1) {
    gb.clearDisplay();
    modes = 0;
  }
  switchMode(modes);
}

