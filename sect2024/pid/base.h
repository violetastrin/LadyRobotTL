#ifndef rodar
#define rodar

//Bibliotecas
#include <Servo.h>    
#include <Ultrasonic.h>  
#include <Arduino.h>
#include <MicroLCD.h>

//pid
float kp;
float kd;
float error_passado = 0;
int vbase = 20;

//servos
Servo servoDir_t;
Servo servoEsq_f;
Servo servoEsq_t;
Servo servoDir_f;


//display oled
LCD_SSD1306 display; /* for SSD1306 OLED module */

//ultra sonico
Ultrasonic ultrasonic(A5, A6);  // trig primeiro depois echo
int distancia;


//ORDEM: ESQUERDA, REAJUSTE ESQUERDA, FRENTE, REAJUSTE DIREITA, DIREITA
const int sensor[] = {A2, A4, A3};

const int esq_dir[] = {A1, A0}

const int valorPreto[] = {90, 330, 600}; 

const int valorBranco[] = {340, 988, 988};

const int media[] = {30, 50, 30}; //!ver valores pra cada um dps

int leituraSensor[3] = {};

int sensorMap[3] = {};

bool valorSensor[3] = {};


// Função Leitura
void leiturainfra(){
for(int i = 0; i<3; i++){
  leituraSensor[i] = analogRead(sensor[i]);
  }

for (int i = 0; i<3; i++){
  sensorMap[i] = map(leituraSensor[i], valorPreto[i], valorBranco[i], 0, 100);
  sensorMap[i] = constrain(sensorMap[i], 0, 100);
}
}

int velEsq(int x){
  return x + 90;
}

int velDir(int y){
  return 90 - y;
}


/*Os valores variam de -90 até 90, 
sendo -90 a velocidade máxima para trás; 0 para parar o motor e 90 a velocidade máxima para frente.
Os valores funcionam de forma igual na esquerda e direita.

obs: os motores provavelmente ficarão parados caso os valores estejam entre -10 e o 10.*/

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
  servoEsq_f.write(velEsq(0));
  servoEsq_t.write(velEsq(0));
}

///////////////////////////////

void direitaFrente() {
  servoDir_f.write(40);
  servoDir_t.write(40);
}

void direitaRe() {
  servoDir_f.write(140);
  servoDir_t.write(140);
}

void direitaPara() {
  servoDir_f.write(velDir(0));
  servoDir_t.write(velDir(0));
}

//////////////////////////////

void frente(){
  servoDir_f.write(velDir(20));
  servoDir_t.write(velDir(20));
  servoEsq_f.write(velEsq(20));
  servoEsq_t.write(velEsq(20));
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
  servoEsq_f.write(velEsq(-30));
  servoEsq_t.write(velEsq(-30));
  servoDir_f.write(velDir(30));
  servoDir_t.write(velDir(30));
  
}

void devagarDireita() {  // virando para direita devagar
  servoEsq_f.write(velEsq(30));
  servoEsq_t.write(velEsq(30));
  servoDir_f.write(velDir(-30));
  servoDir_t.write(velDir(-30));
}

void parar(){
    esquerdaPara();
    direitaPara();
}
void re(){
    esquerdaRe();
    direitaRe();
}

//---------------------- funções desvia obstáculo (NAO MUDAR!)

void esqfrente2() {
  servoEsq_f.write(velEsq(35)); 
  servoEsq_t.write(velEsq(35)); 
}

void dirfrente2() {
  servoDir_f.write(velDir(35)); 
  servoDir_t.write(velDir(35));
}

void dirre2() {
  servoDir_f.write(velDir(-35));
  servoDir_t.write(velDir(-35));
}

void esqre2() {
  servoEsq_f.write(velEsq(-35));
  servoEsq_t.write(velEsq(-35));
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

//----------------------  desvia obstáculo -------------------------------------------------------------------------

void desviaesq() {
  re2();
  delay(150);
  esquerda2();
  delay(1300);
  frente2();
  delay(1200);
  direita2();
  delay(1400);
  frente2();
  delay(2700);
  direita2();
  delay(1400);
  frente2();
  delay(50);
  while (analogRead(sensor[3]) > 600) {
    frente2();
  }

  while (analogRead(sensor[2]) > 400) {
    esquerda2();
  }
}

void desviadir() {
  re2();
  delay(150);
  direita2();
  delay(1500);
  frente2();
  delay(1350);
  esquerda2();
  delay(1250);
  frente2();
  delay(2300);
  esquerda2();
  delay(1000);
  frente2();
  delay(50);
  while (analogRead(sensor[3]) > 650) {
    frente2();
  }

  while (analogRead(sensor[2]) > 400) {
    direita2();
  }
}




#endif
