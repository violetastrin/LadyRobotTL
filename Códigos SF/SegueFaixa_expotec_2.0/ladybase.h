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
bool dvermelho;
bool evermelho;
bool dcinza;
bool ecinza;

// Limiares para os sensores de linha
const int pretfront = 300;
const int pretesq = 290;
const int pretdir = 330;
const int pretresq = 320;
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
  servoef.write(120);
  servoet.write(120);
  servodf.write(60);
  servodt.write(60);
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

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);
  
  uint16_t medrbg1 = (r1 + b1 + g1) / 3;
  uint16_t medrbg2 = (r2 + b2 + g2) / 3;

  uint16_t med1 = medrbg1 * 1.05;
  uint16_t med2 = medrbg2 * 1.045;

  if (medrbg1 >= 7200) {
    dverde = 0;
  } else if (g1 >= med1){
    dverde = 1;
  }
  else{
    dverde = 0;
  }


  if (medrbg2 >= 7000)
  { everde = 0;
  }
   else if (g2 >= med2){
    everde = 1;
  }
  else{
    everde = 0;
  }
//------------------------------------------------------------------------
  if (r1 > medrbg1 && c1 <= 14000) {
    dvermelho = 1;
  }
  else {
    dvermelho = 0;
  }


  if (r2 > medrbg2 && c2 <= 14500) {
    evermelho = 1;
  }
  else {
    evermelho = 0;
  }
  // ---------------------------------------------------------------------
  if (c1 >= 999999) {
    dcinza = 1;
  }
  else {
    dcinza = 0;
  }


  if (c2 >= 999999) {
    ecinza = 1;
  }
  else {
    ecinza = 0;
  }
  //----------------------------------------------------------------------



  Serial.print("ESQ (soft): ");
  Serial.print(", Verde: ");
  Serial.print(g2);
  Serial.print(", Media: ");
  Serial.print(med2);

  Serial.print(" | DIR (real): ");
  Serial.print(", Verde: ");
  Serial.print(g1);
  Serial.print(", Media: ");
  Serial.println(med1);

  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_SMALL);
  display.print("Esq G: ");
  display.println(g2);
  display.print("Esq R: ");
  display.println(r2);
  display.print("Esq M: ");
  display.println(med2);
  display.print("Dir G: ");
  display.println(g1);
  display.print("Dir R: ");
  display.println(r1);
  display.print("Dir M: ");
  display.println(med1);
  delay(2500); // LEMBRAR DE TIRAR EH SO PARA DEBUG!!!!!!*/

  Serial.print("ESQ (soft): ");
  Serial.print(everde);

  Serial.print(" | DIR (real): ");
  Serial.print(dverde);


}
void verdes() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.print("Esq: ");
  display.println(everde);
  display.print("Dir: ");
  display.println(dverde);
  delay(600);
}

#endif
