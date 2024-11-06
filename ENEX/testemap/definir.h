#ifndef rodar
#define rodar

//Bibliotecas
#include <Servo.h>    
#include <Ultrasonic.h>  
#include <SoftwareWire.h>
#include <Wire.h>
#include <Adafruit_TCS34725_SWwire.h>
#include <Arduino.h>
// #include <MicroLCD.h>


Servo servoDir_t;
Servo servoEsq_f;
Servo servoEsq_t;
Servo servoDir_f;



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