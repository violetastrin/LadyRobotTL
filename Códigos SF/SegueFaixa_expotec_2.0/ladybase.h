#ifndef rodar
#define rodar

#include <Servo.h>       // Biblioteca do servo
#include <Ultrasonic.h>  // Biblioteca do sensor de obstáculo
#include <SoftwareWire.h>
#include <Wire.h>
#include <Adafruit_TCS34725_SWwire.h>
#include <Arduino.h>
#include <MicroLCD.h>

LCD_SSD1306 display; /* for SSD1306 OLED module */

SoftwareWire sWire(A6, A7);

Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_16X);
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_16X);

uint16_t r1, g1, b1, c1;
uint16_t r2, g2, b2, c2;

uint16_t medrbg1;
uint16_t medrbg2;

Servo servodf;
Servo servodt;
Servo servoef;
Servo servoet;

#define ESQ A2
#define RESQ A3
#define MEIO A0
#define REDIR A4
#define DIR A1

bool front;
bool esq;
bool dir;
bool resq;
bool rdir;
bool dverde;
bool everde;

float red, green, blue;
float red2, green2, blue2;

// Limiares para os sensores de linha
const int pretfront = 320;
const int pretesq = 400;
const int pretdir = 480;
const int pretresq = 350;
const int pretrdir = 300;

Ultrasonic ultrasonic(8, 9);  // trig primeiro depois echo
int distancia;
//-----------------FUNÇOES SERVOS ------------------------------- FUNÇOES SERVOS --------------------------------- FUNÇOES SERVOS -------------------------------------
//------------------- normal

void esqfrente() {
  servoef.write(130);
  servoet.write(130);
}

void esqre() {
  servoef.write(50);
  servoet.write(50);
}

void dirfrente() {
  servodf.write(50);
  servodt.write(50);
}

void dirre() {
  servodf.write(130);
  servodt.write(125);
}

//-------------------- slow

void devesqfrente() {
  servoef.write(120);
  servoet.write(120);
}

void devesqre() {
  servoef.write(60);
  servoet.write(60);
}

void devdirfrente() {
  servodf.write(60);
  servodt.write(60);
}

void devdirre() {
  servodf.write(120);
  servodt.write(120);
}

//---------------------- parar

void esqpare() {
  servoef.write(90);
  servoet.write(90);
}

void dirpare() {
  servodf.write(90);
  servodt.write(90);
}

//------------------------- frente normal (padrão)
void frente() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("frente");
  Serial.println("FRENTE");
  servoef.write(125);
  servoet.write(125);
  servodf.write(55);
  servodt.write(55);
}
//---------------------- funções desvia obstáculo (NAO MUDAR!)

void giroabdir() {
  servoef.write(180);  // esquerda fast
  servoet.write(180);  // esquerda fast
  servodf.write(80);   // direita slow
  servodt.write(80);   // direita slow
}

void giroabesq() {
  servoef.write(100);  // esquerda slow
  servoet.write(100);  // esquerda slow
  servodf.write(0);    // direita fast
  servodt.write(0);    // direita fast
}

void esqfrente2() {
  servoef.write(125);
  servoet.write(125);
}

void dirfrente2() {
  servodf.write(55);
  servodt.write(55);
}

void dirre2() {
  servodf.write(125);
  servodt.write(125);
}

void esqre2() {
  servoef.write(55);
  servoet.write(55);
}

void re2() {
  esqre2();
  dirre2();
}

void esquerda2() {
  esqre2();
  dirfrente2();
}

void direita2() {
  esqfrente2();
  dirre2();
}

void frente2() {
  dirfrente2();
  esqfrente2();
}

void leiturainfra() {
  Serial.print(" S_esq: " + String(esq));
  Serial.print(" S_front: " + String(front));
  Serial.print(" S_dir: " + String(dir));
  Serial.print(" S_redir: " + String(rdir));
  Serial.println(" S_resq: " + String(resq));
}

void leituraCor() {

  // tcs_soft.getRGB(&red, &green, &blue);
  // tcs_real.getRGB(&red2, &green2, &blue2);

  // Serial.print("Re:\t"); Serial.print(int(red)); 
  // Serial.print("\tGe:\t"); Serial.print(int(green)); 
  // Serial.print("\tBe:\t"); Serial.print(int(blue));
  // Serial.print("\n");

  // Serial.print("Rd:\t"); Serial.print(int(red2)); 
  // Serial.print("\tGd:\t"); Serial.print(int(green2)); 
  // Serial.print("\tBd:\t"); Serial.print(int(blue2));
  // Serial.print("\n");

  
  

 /* if (green > 90 < 100 && blue < 90) {
    dverde = 1; 
  } else {
    dverde = 0;  
  }

  if (green2 > 102 && blue2 < 120) {
    everde = 1;        
  } else {
    everde = 0;        
  }*/

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  uint16_t medrbg1 = (r1 + b1 + g1) / 3;
  uint16_t medrbg2 = (r2 + b2 + g2) / 3;

  Serial.print("ESQ (soft): ");
  // Serial.print("Vermelho: ");
  // Serial.print(r2);
  Serial.print(", Verde: ");
  Serial.print(g2);
  Serial.print(", Media: ");
  Serial.print(medrbg2 * 1.05);
  // Serial.print(", Azul: ");
  // Serial.print(b2);
  // Serial.print(", Claro: ");
  // Serial.print(c2);

  Serial.print(" | DIR (real): ");
  // Serial.print("Vermelho: ");
  // Serial.print(r1);
  Serial.print(", Verde: ");
  Serial.print(g1);
  Serial.print(", Media: ");
  Serial.println(medrbg1 * 1.10);
  // Serial.print(", Azul: ");
  // Serial.print(b1);
  // Serial.print(", Claro: ");
  // Serial.println(c1);

  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.print("Esq G: ");
  display.println(g2);
  display.print("Esq M: ");
  display.println(medrbg2 * 1.05);
  display.print("Dir G: ");
  display.println(g1);
  display.print("Dir M: ");
  display.println(medrbg1 * 1.10);
  delay(2500); // LEMBRAR DE TIRAR EH SO PARA DEBUG!!!!!!

  if (medrbg1 >= 2900) {
    dverde = 0;
  } else if (g1 >= medrbg1 * 1.10){
    dverde = 1;
  }
  else{
    dverde = 0;
  }

  // if (medrbg2 >= 2700) {
  //   everde = 0;
  // } else 
  if (g2 >= medrbg2 * 1.05){
    everde = 1;
  }
  else{
    everde = 0;
  }

  Serial.print("ESQ (soft): ");
  Serial.print(everde);

  Serial.print(" | DIR (real): ");
  Serial.print(dverde);

  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.print("Esq: ");
  display.println(everde);
  display.print("Dir: ");
  display.println(dverde);
delay(2500);


}
void verdes() {
  Serial.print("everde: ");
  Serial.print(everde);
  Serial.print("  dverde: ");
  Serial.println(dverde);
}

#endif
