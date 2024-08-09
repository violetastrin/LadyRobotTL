#ifndef rodar
#define rodar

#include <Servo.h>       // Biblioteca do servo
#include <Ultrasonic.h>  // Biblioteca do sensor de obstáculo
#include <SoftwareWire.h>
#include <Wire.h>
#include <Adafruit_TCS34725_SWwire.h>

SoftwareWire sWire(A6, A7);

Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_4X);
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_4X);

uint16_t r1, g1, b1, c1;
uint16_t r2, g2, b2, c2;

uint16_t medrb1;
uint16_t medrb2;

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

// Limiares para os sensores de linha
const int pretfront = 270;
const int pretesq = 420;
const int pretdir = 500;
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

void esqfrente2() {
  servoef.write(125);
  servoet.write(125);
}

void esqre2() {
  servoef.write(55);
  servoet.write(55);
}

void dirfrente2() {
  servodf.write(55);
  servodt.write(55);
}

void dirre2() {
  servodf.write(125);
  servodt.write(125);
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

#endif