#ifndef rodar
#define rodar

//Bibliotecas
#include <Servo.h>
#include <Ultrasonic.h>
#include <MicroLCD.h>
// #include <PCD8544.h>
// #include <SSD1306.h>
#include <Arduino.h>
// #include <MicroLCD.h>

LCD_SSD1306 display;


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

const int valorPreto[] = { 60, 60, 60, 60, 60 };      // branco

const int valorBranco[] = { 800, 680, 780, 720, 750 };   // preto

const int media[] = {
  (valorPreto[0] + valorBranco[0]) / 2,
  (valorPreto[1] + valorBranco[1]) / 2,
  (valorPreto[2] + valorBranco[2]) / 2,
  (valorPreto[3] + valorBranco[3]) / 2,
  (valorPreto[4] + valorBranco[4]) / 2
};

int leituraSensor[5] = {};

int sensorMap[5] = {};

bool valorSensor[5] = {};

Servo servoDir_t;
Servo servoEsq_f;
Servo servoEsq_t;
Servo servoDir_f;

Ultrasonic ultrasonic(A14, A15);  // trig primeiro depois echo
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

void esqfrente2() {                     //esquerda frente
  servoEsq_f.write(velEsq(45)); 
  servoEsq_t.write(velEsq(45)); 
}

void dirfrente2() {                     //direita frente
  servoDir_f.write(velDir(40)); 
  servoDir_t.write(velDir(40));
}

void esqre2() {                         //esquerda tras
  servoEsq_f.write(velEsq(-45));
  servoEsq_t.write(velEsq(-45));
}

void dirre2() {                        //direita tras
  servoDir_f.write(velDir(-40));
  servoDir_t.write(velDir(-40));
}

void reajDirdesv(){                    //direita desvia
  servoEsq_f.write(velEsq(40));
  servoEsq_t.write(velEsq(40));
  servoDir_f.write(velDir(-45));
  servoDir_t.write(velDir(-45));
}

void reajEsqdesv(){                    //esquerda desvia
  servoEsq_f.write(velEsq(-45));
  servoEsq_t.write(velEsq(-45));
  servoDir_f.write(velDir(40));
  servoDir_t.write(velDir(40));
}

void reajEsqdesv2(){                  //girando no proprio eixo esquerda no final
  servoEsq_f.write(velEsq(-90));
  servoEsq_t.write(velEsq(-90));
  servoDir_f.write(velDir(40));
  servoDir_t.write(velDir(40));
}

void reajDirdesv2(){                  //girando no proprio eixo direita no final
  servoEsq_f.write(velEsq(40));
  servoEsq_t.write(velEsq(40));
  servoDir_f.write(velDir(-90));
  servoDir_t.write(velDir(-90));
}

void virarDireixo(){                 //girando no proprio eixo direita (no meio)
  servoEsq_f.write(velEsq(30));
  servoEsq_t.write(velEsq(30));
  servoDir_f.write(velDir(-90));
  servoDir_t.write(velDir(-90));
}

void virarEsqeixo(){                 //girando no proprio eixo esquerda (no meio)
  servoEsq_f.write(velEsq(-90));
  servoEsq_t.write(velEsq(-90));
  servoDir_f.write(velDir(30));
  servoDir_t.write(velDir(30));
}

void re2() {                         //todo ré
  esqre2();
  dirre2();
}

void esquerda2() {                   //
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

void retornoDIR(){
  reajDirdesv();
}

void retornoESQ(){
  reajEsqdesv();
}

//----------------------  desvia obstáculo -------------------------------------------------------------------------

void desviaesq() {
  re2();
  delay(200);
  esquerda2();
  delay(1350);
  frente2();
  delay(1400);
  reajDirdesv();
  delay(1300);
  frente2();
  delay(1900);
  virarDireixo();
  delay(800);
  frente2();
  delay(700);
  direita2();
  delay(300);
  frente2();
  delay(900);
  reajEsqdesv();
  delay(1000);
  while (analogRead(sensor[0]) < 600) {
    frente2();
  }
  while (analogRead(sensor[2]) < 570) {
    esquerda2();
  }
}

void desviadir() {
  re2();
  delay(200);
  direita2();
  delay(1350);
  frente2();
  delay(1400);
  reajEsqdesv();
  delay(1500);
  frente2();
  delay(2450);
  virarEsqeixo();
  delay(1300);
  frente2();
  delay(300);
  while (analogRead(sensor[4]) < 600) {
    frente2();
  }
  frente2();
  delay(250);
  while (analogRead(sensor[2]) < 570) {
    direita2();
  }
}

// -------------------------------------------------------------------------------------------------------------------------------------------------

bool contagem = false;
int tempoo = 0;
int estado = 0;


bool lendoBranco() {
  return (valorSensor[0] == 1 && valorSensor[1] == 1 && valorSensor[2] == 1 && valorSensor[3] == 1 && valorSensor[4] == 1);
}

unsigned long tempoBranco = 0;          // guarda o momento que começou a ler branco
const unsigned long esperaBranco = 3000; // tempo de espera (3 segundos)

void saladeresgate(){

  frente();
  delay(1900);

  virarDireixo();
  delay(1500);

  frente();
  delay(5120);

  virarEsqeixo();
  delay(1650);

  frente();
  delay(500);

  while (analogRead(sensor[4]) < 600) {
  frente();
  }
}

void confere() {
  if (lendoBranco()) {
    if (tempoBranco == 0) {
      tempoBranco = millis();  //contagrm
    } else if (millis() - tempoBranco >= esperaBranco) {
      // 3 segundos
      saladeresgate();
      tempoBranco = 0; // reseta
    }
  } else {
    tempoBranco = 0; // se ver preto, zera contagem
  }

}

//    while (true) {
//     long distanciaFrente = ultrasonic.read();

//     // Serial.print("Frente: ");
//     // Serial.print(distanciaFrente);
//     // Serial.print(" cm | Direita: ");
//     // Serial.print(distanciaDireita);
//     // Serial.println(" cm");

//     switch (estado) {

//       case 0: // Frente até obstáculo
//         if (ultrasonic.read() > 10) {
//           frente();
//         } else {
//           parar();
//           estado = 3;
//           delay(200);
//         }
//         break;

//       case 3: // Vira esquerda
//         virarEsqeixo();
//         delay(1250);
//         parar();
//         estado = 0; // volta ao ciclo
//         break;
//     }

//     delay(100);
//   }
// }

#endif
