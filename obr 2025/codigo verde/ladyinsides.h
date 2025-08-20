#ifndef rodar
#define rodar

//Bibliotecas
#include <Servo.h>
#include <Ultrasonic.h>


//  sensor de cor              26 LED VERDE RGB ESQUERDA; 28 LED VERMELHO RGB ESQUERDA; 22 LED VERDE RGB DIREITA; 24 LED VERMELHO RGB DIREITA;
#define eledverde 26
#define eledverm 28
#define dledverde 22
#define dledverm 24

//  ldr                                                         A9 LDR ESQUERDA; A8 LDR DIREITA
#define core A10
#define cord A11

//                          ORDEM: ESQUERDA PONTA (EP) A3, ESQUERDA MEIO (EM) A2, FRENTE (F) A4, DIREITA MEIO (DM) A1, DIREITA PONTA (DP) A0
const int sensor[] = { A3, A2, A4, A1, A0 };

const int valorBranco[] = { 720, 650, 740, 670, 730 };

const int valorPreto[] = { 40, 40, 40, 40, 40 };

const int media[] = { 50, 50, 50, 50, 50 };

int leituraSensor[5] = {};

int sensorMap[5] = {};

bool valorSensor[5] = {};

Servo servoDir_t;
Servo servoEsq_f;
Servo servoEsq_t;
Servo servoDir_f;

Ultrasonic ultrasonic(A5, A6);  // trig primeiro depois echo
int distancia;

int velEsq(int x) {
  return x + 90;
}

int velDir(int y) {
  return 90 - y;
}

bool esquerdaverde, direitaverde, esquerdaverm, direitaverm;


void leiturainfra() {
  for (int i = 0; i < 5; i++) {
    leituraSensor[i] = analogRead(sensor[i]);
  }

  for (int i = 0; i < 5; i++) {
    sensorMap[i] = map(leituraSensor[i], valorPreto[i], valorBranco[i], 0, 100);
    sensorMap[i] = constrain(sensorMap[i], 0, 100);
  }
}

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
  servoDir_f.write(130);
  servoDir_t.write(130);
}

void direitaPara() {
  servoDir_f.write(velDir(0));
  servoDir_t.write(velDir(0));
}

//////////////////////////////

void frente() {

  servoDir_f.write(velDir(25));
  servoDir_t.write(velDir(25));
  servoEsq_f.write(velEsq(30));
  servoEsq_t.write(velEsq(30));
}

void esquerda() {
  esquerdaRe();
  direitaFrente();
}

void direita() {
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

void reajusteDireita() {
  Serial.println("reajuste direita");
  servoEsq_f.write(velEsq(10));
  servoEsq_t.write(velEsq(10));   //20
  servoDir_f.write(velDir(-10));  //10
  servoDir_t.write(velDir(-10));
}

void reajusteEsquerda() {
  Serial.println("reajuste esquerda");
  servoEsq_f.write(velEsq(-10));
  servoEsq_t.write(velEsq(-10));
  servoDir_f.write(velDir(10));
  servoDir_t.write(velDir(10));
}

void parar() {
  esquerdaPara();
  direitaPara();
}
void re() {
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
