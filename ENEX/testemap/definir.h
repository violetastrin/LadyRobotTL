#ifndef rodar
#define rodar

//Bibliotecas
#include <Servo.h>    
#include <Ultrasonic.h>  
#include <SoftwareWire.h>
#include <Wire.h>
#include <Adafruit_TCS34725_SWwire.h>
#include <Arduino.h>
#include <MicroLCD.h>


Servo servoDir_t;
Servo servoEsq_f;
Servo servoEsq_t;
Servo servoDir_f;

LCD_SSD1306 display; /* for SSD1306 OLED module */

//ORDEM: ESQUERDA, REAJUSTE ESQUERDA, FRENTE, REAJUSTE DIREITA, DIREITA
const int sensor[] = {A2, A1, A4, A0, A3};

const int valorPreto[] = {550, 320, 210, 445, 570};

const int valorBranco[] = {984, 982, 988, 986, 988};

const int media[] = {50, 50, 50, 50, 50}; //!ver valores pra cada um dps

int leituraSensor[5] = {};

int sensorMap[5] = {};

bool valorSensor[5] = {};


// Função Leitura
void leiturainfra(){
for(int i = 0; i<5; i++){
  leituraSensor[i] = analogRead(sensor[i]);
  }

for (int i = 0; i<5; i++){
  sensorMap[i] = map(leituraSensor[i], valorPreto[i], valorBranco[i], 0, 100);
  sensorMap[i] = constrain(sensorMap[i], 0, 100);
}
}

//Funções motor 

void esquerdaFrente() {
  servoEsq_f.write(130);
  servoEsq_t.write(130);
}

void esquerdaRe() {
  servoEsq_f.write(50);
  servoEsq_t.write(50);
}

void esquerdaPara() {
  servoEsq_f.write(90);
  servoEsq_t.write(90);
}

///////////////////////////////

void direitaFrente() {
  servoDir_f.write(50);
  servoDir_t.write(50);
}

void direitaRe() {
  servoDir_f.write(130);
  servoDir_t.write(130);
}

void direitaPara() {
  servoDir_f.write(90);
  servoDir_t.write(90);
}

//////////////////////////////

void frente(){
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("frente");
  
    servoDir_f.write(70);
    servoDir_t.write(70);
    servoEsq_f.write(110);
    servoEsq_t.write(110);
}

void esquerda(){
    esquerdaRe();
    direitaFrente();
}

void direita(){
    esquerdaFrente();
    direitaRe();
}

void devagarEsquerda() {  // virando para esquerda devagar
  Serial.println("Esquerda devagar");
  servoEsq_f.write(60);
  servoEsq_t.write(60);
  servoDir_f.write(60);
  servoDir_t.write(60);
}

void devagarDireita() {  // virando para direita devagar
  Serial.println("Direita devagar");
  servoEsq_f.write(120);
  servoEsq_t.write(120);  
  servoDir_f.write(120);
  servoDir_t.write(120);
}

void reajusteDireita() {  
  Serial.println("reajuste direita");
  servoEsq_f.write(125);
  servoEsq_t.write(125);
  servoDir_f.write(75);
  servoDir_t.write(75);
}

void reajusteEsquerda() {                   
  Serial.println("reajuste esquerda");
  servoEsq_f.write(105);
  servoEsq_t.write(105);
  servoDir_f.write(55);
  servoDir_t.write(55);
}

void parar(){
    esquerdaPara();
    direitaPara();
}
void re(){
    esquerdaRe();
    direitaRe();
}

#endif