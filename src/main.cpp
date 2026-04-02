#include <GameBoy.h>

GameBoy gb;

int snakeX[15];
int snakeY[10];
int lenSnake = 5;
int up = 1;
int right = 2;
int bottom = 3;
int left = 4;
int direction = right;
int eatX;
int eatY;
bool state;
int modeCount;
int enemy_x = 2;
int car_speed = 100;
int mycar_x = 2;
int mycar_y = 12;
int modes;

void makeMove() {
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
void loss(){
  delay(1000);
  gb.clearDisplay();
  for (int i = 0;i < lenSnake;i++){
    snakeX[i] = 0;
    snakeY[i] = 0;
  }
  direction = right;
  eatX = 3;
  eatY = 3;
  lenSnake = 5;
  snakeX[0] = 4;
  snakeY[0] = 7;
  
}

void drawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]);
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

void drawFruit() {
  state = !state;
  if (state == true) {
    gb.drawPoint(eatX, eatY);
  } else {
    gb.wipePoint(eatX, eatY);
  }
}

void move() {
  if ((snakeX[0] == eatX) && (snakeY[0] == eatY)) {
    lenSnake++;
    makeFruit();
    gb.sound(SCORE);
  }
  for(int i = lenSnake - 1;i > 0;i--){
    if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]){
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

void enemyCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y - 1);
  gb.drawPoint(x, y - 2);
  gb.drawPoint(x - 1, y - 1);
  gb.drawPoint(x + 1, y - 1);
  gb.drawPoint(x - 1, y - 3);
  gb.drawPoint(x + 1, y - 3);
}

void playerCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y + 1);
  gb.drawPoint(x, y + 2);
  gb.drawPoint(x - 1, y + 1);
  gb.drawPoint(x + 1, y + 1);
  gb.drawPoint(x - 1, y + 3);
  gb.drawPoint(x + 1, y + 3);
}

void setup() {
  gb.begin(0);
  snakeX[0] = 4;
  snakeY[0] = 7;
  randomSeed(analogRead(0));
  makeFruit();
  playerCar(mycar_x, mycar_y);
  randomSeed(analogRead(0));
}

byte ARROWS[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 0, 0, 1, 1, 1},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

byte SNAKE[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,0,0,1,1,0},
  {0,1,1,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,1,1,0},
  {0,1,1,0,0,1,1,0},
  {0,0,1,1,1,1,0,0} 
};

byte CAR[8][8] = {
  {0,1,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,1,1,1,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,1,0,1,0}
};

void gameSnake() {
  makeMove();
  move();
  
  gb.clearDisplay();
  drawSnake();
  drawFruit();
  delay(250);
}

void clearPlayerCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y + 1);
  gb.wipePoint(x, y + 2);
  gb.wipePoint(x - 1, y + 1);
  gb.wipePoint(x + 1, y + 1);
  gb.wipePoint(x - 1, y + 3);
  gb.wipePoint(x + 1, y + 3);
}

void clearEnemyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y - 1);
  gb.wipePoint(x, y - 2); 
  gb.wipePoint(x - 1, y - 1);
  gb.wipePoint(x + 1, y - 1);
  gb.wipePoint(x - 1, y - 3);
  gb.wipePoint(x + 1, y - 3);
}

void createLine ( int y) {
  gb.drawPoint(0, y);
  gb.drawPoint(0, y + 1);
  gb.drawPoint(0, y + 2);
  
  gb.drawPoint(7, y);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 2);
}

void clearLine (int y) {
  gb.wipePoint(0, y);
  gb.wipePoint(0, y + 1);
  gb.wipePoint(0, y + 2);
  
  gb.wipePoint(7, y);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 2);
}

bool Collision(int mycar_x, int mycar_y, int enemy_car_x, int enemy_car_y){
  if (mycar_y == enemy_car_y and mycar_x == enemy_car_x){
    return true;
  }
  if(mycar_x==enemy_car_x and enemy_car_y>12){
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
  for (int enemy_y = 0; enemy_y < 16; enemy_y++) {
    createLine(enemy_y);
    createLine(enemy_y + 5);
    createLine(enemy_y + 10);
    createLine(enemy_y + 15);
    createLine(enemy_y - 5);
    createLine(enemy_y - 10);
    createLine(enemy_y - 15);
    enemyCar(enemy_x, enemy_y);

    if (gb.getKey() == 4) { 
      mycar_x = 2;
      clearPlayerCar(5, 12);
      playerCar(2, 12);
    } 
    else if (gb.getKey() == 5) { 
      mycar_x = 5;
      clearPlayerCar(2, 12);
      playerCar(5, 12);
    }
playerCar(mycar_x,mycar_y);
if (Collision(mycar_x, mycar_y, enemy_x, enemy_y) == true){
  gb.sound(COLLISION);
  gb.testMatrix(10);
  gb.clearDisplay();
  return;
}
if(enemy_y > 14){
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
    clearEnemyCar(enemy_x, enemy_y);
  }
 
}

int modeSelector() {
  if(gb.getKey() == 4) {
    modeCount++;
    delay(250);
    if(modeCount > 1) {
      modeCount = 0;
    }
  } 
  else if(gb.getKey() == 5) {
    modeCount--;
    delay(250);
    if(modeCount < 0) {
      modeCount = 1;
    }
  }
  return modeCount;
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
  else if (modeSelector() == 1) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        gb.wipePoint(i, 8 + j);
        gb.setLed(i, 8 + j, SNAKE[j][i]);
      }
    }
  }
}

void switchMode(int mode) {
  switch (mode) {
    case 0: mainMenu();
      break;
    case 1: mainRaicing();
      break;
    case 2: gameSnake();
  }
}

void loop() {
  if(gb.getKey() == 2 && modeSelector() == 0) {
    gb.clearDisplay();
    modes = 1;
  }
  else if(gb.getKey() == 2 && modeSelector() == 1) {
    gb.clearDisplay();
    modes = 2;
  }
  else if(gb.getKey() == 1) {
    gb.clearDisplay();
    modes = 0;
  }
  switchMode(modes);
}