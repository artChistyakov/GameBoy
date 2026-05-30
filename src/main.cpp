#include <Arduino.h> // Обов'язково для PlatformIO
#include <QuantSensors.h> // Бібліотека датчиків Quant

// Точні піни відповідно до шовкографії вашої плати Q 312
#define MOTOR_L_PIN1 6   // Лівий мотор (D6)
#define MOTOR_L_PIN2 5   // Лівий мотор (D5)

#define MOTOR_R_PIN1 10  // Правий мотор (D10)
#define MOTOR_R_PIN2 9   // Правий мотор (D9)

// --- ПРОТОТИПИ ФУНКЦІЙ (для коректної компіляції в PlatformIO) ---
void setSpeed(int level);
void forward();
void backward();
void left();
void right();
void stp();

// Калібрувальні коефіцієнти швидкості (за потреби змініть для рівного ходу)
float motor_a_koef = 1.0;
float motor_b_koef = 0.78;

// Поточні робочі швидкості двигунів
int speed_A = 150;
int speed_B = 150;

QuantLine line;

void setup() {
  Serial.begin(9600);
  
  // Ініціалізація датчиків лінії
  line.begin(true);    
  line.setLevel(100);  

  // Налаштування пінів двигунів на вихід
  pinMode(MOTOR_L_PIN1, OUTPUT);
  pinMode(MOTOR_R_PIN1, OUTPUT);
  
  // Встановлюємо середню швидкість руху (рівень 6 з 10)
  setSpeed(6); 
  
  // Початкова зупинка перед стартом
  stp();
  delay(2000); // Пауза 2 секунди, щоб встигнути поставити робота на підлогу
}

void loop() {
  Serial.println("--- Початок циклу руху ---");

  // 1. Рух вперед протягом 2 секунд
  Serial.println("Рух вперед...");
  forward();
  delay(2000);

  // Зупинка на 1 секунду
  Serial.println("Зупинка...");
  stp();
  delay(1000);

  // 2. Рух назад протягом 2 секунд
  Serial.println("Рух назад...");
  backward();
  delay(2000);

  // Зупинка на 1 секунду
  Serial.println("Зупинка...");
  stp();
  delay(1000);

  // 3. Поворот ліворуч на місці протягом 1.5 секунди
  Serial.println("Поворот ліворуч...");
  left();
  delay(1500);

  // Зупинка на 1 секунду
  Serial.println("Зупинка...");
  stp();
  delay(1000);

  // 4. Поворот праворуч на місці протягом 1.5 секунди
  Serial.println("Поворот праворуч...");
  right();
  delay(1500);

  // Довга зупинка на 3 секунди перед повторенням всього циклу
  Serial.println("Очікування перед наступним циклом...");
  stp();
  delay(3000); 
}

// --- РЕАЛІЗАЦІЯ ФУНКЦІЙ КЕРУВАННЯ ---

// Функція розрахунку швидкості з урахуванням коефіцієнтів
void setSpeed(int level) {
  int base = map(level, 0, 10, 0, 255);
  speed_A = base * motor_a_koef;
  speed_B = base * motor_b_koef;
}

void forward() {
  // Лівий двигун вперед (D6 = LOW, D5 = PWM)
  digitalWrite(MOTOR_L_PIN1, LOW);
  analogWrite(MOTOR_L_PIN2, speed_A);
  
  // Правий двигун вперед (D10 = HIGH, D9 = PWM із інверсією 255-speed) [7]
  digitalWrite(MOTOR_R_PIN1, HIGH);
  analogWrite(MOTOR_R_PIN2, 255 - speed_B);
}

void backward() {
  // Лівий двигун назад (D6 = HIGH, D5 = PWM із інверсією 255-speed) [7]
  digitalWrite(MOTOR_L_PIN1, HIGH);
  analogWrite(MOTOR_L_PIN2, 255 - speed_A);
  
  // Правий двигун назад (D10 = LOW, D9 = PWM) [7]
  digitalWrite(MOTOR_R_PIN1, LOW);
  analogWrite(MOTOR_R_PIN2, speed_B);
}

void left() {
  // Розворот ліворуч (Лівий назад, Правий вперед)
  digitalWrite(MOTOR_L_PIN1, HIGH);
  analogWrite(MOTOR_L_PIN2, 255 - speed_A);
  
  digitalWrite(MOTOR_R_PIN1, HIGH);
  analogWrite(MOTOR_R_PIN2, 255 - speed_B);
}

void right() {
  // Розворот праворуч (Лівий вперед, Правий назад)
  digitalWrite(MOTOR_L_PIN1, LOW);
  analogWrite(MOTOR_L_PIN2, speed_A);
  
  digitalWrite(MOTOR_R_PIN1, LOW);
  analogWrite(MOTOR_R_PIN2, speed_B);
}

void stp() {
  // Активне гальмування двигунів (на обидва канали подається HIGH)
  digitalWrite(MOTOR_L_PIN1, HIGH);
  analogWrite(MOTOR_L_PIN2, 255);
  
  digitalWrite(MOTOR_R_PIN1, HIGH);
  analogWrite(MOTOR_R_PIN2, 255);
}