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

//servos
Servo servoDir_t;
Servo servoEsq_f;
Servo servoEsq_t;
Servo servoDir_f;


//display oled
LCD_SSD1306 display; /* for SSD1306 OLED module */

//ultra sonico
Ultrasonic ultrasonic(A5, A6);  // trig primeiro depois echo

//sensor de cor
SoftwareWire sWire(5, 4);

Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_4X);
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_4X);

uint16_t r1, g1, b1, c1;
uint16_t r2, g2, b2, c2;

uint16_t media_rbg1;
uint16_t media_rbg2;

bool direita_verde, esquerda_verde, direita_vermelho, esquerda_vermelho, direita_cinza, esquerda_cinza;

//ORDEM: ESQUERDA, REAJUSTE ESQUERDA, FRENTE, REAJUSTE DIREITA, DIREITA
const int sensor[] = {A2, A1, A4, A0, A3};

const int valorPreto[] = {325, 475, 180, 503, 470};

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

int velEsq(int x){
  return x + 90;
}

int velDir(int y){
  return 90 - y;
}

void leituraCorG() {

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  media_rbg1 = (r1 + b1 + g1) / 3;
  media_rbg2 = (r2 + b2 + g2) / 3;

  uint16_t media1 = media_rbg1 * 1.065;
  uint16_t media2 = media_rbg2 * 1.08;

  if (media_rbg1 <= 3000) {
    esquerda_verde = 0;
  } else if (g1 >= media1) {
    esquerda_verde = 1;
  } else {
    esquerda_verde = 0;
  }

  if (media_rbg2 <= 2000) {
    direita_verde = 0;
  } else if (g2 >= media2) {
    direita_verde = 1;
  } else {
    direita_verde = 0;
  }
  Serial.print(" esq: ");
  Serial.print(", Verde: ");
  Serial.print(g1);
  Serial.print(", vermelho: ");
  Serial.print(r1);
  Serial.print(", azul: ");
  Serial.print(b1);
  Serial.print(", Media: ");
  Serial.print(media1);
  Serial.print(", esq verde: ");
  Serial.print(esquerda_verde);

    Serial.print("  | | |  dir: ");
  Serial.print(", Verde: ");
  Serial.print(g2);
  Serial.print(", vermelho: ");
  Serial.print(r2);
  Serial.print(", azul: ");
  Serial.print(b2);
  Serial.print(", Media: ");
  Serial.print(media2);
  Serial.print(", dir verde: ");
  Serial.print(direita_verde);


  Serial.println();

  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_SMALL);

  display.print(esquerda_verde);
  display.print("||");
  display.println(direita_verde);

  display.println();

  // display.print("DG: ");
  // display.print(g2);
  // display.print("DR: ");
  // display.println(r2);
  // display.print("DB: ");
  // display.print(b2);
  // display.print("DM: ");
  // display.println(media2);

  // display.print(" EG: ");
  // display.print(g1);
  // display.print(" ER: ");
  // display.println(r1);
  // display.print(" EB: ");
  // display.print(b1);
  // display.print(" EM: ");
  // display.println(media1);
  //delay(2500);  // LEMBRAR DE TIRAR EH SO PARA DEBUG!!!!!!*
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

void reajusteDireita() {  
  Serial.println("reajuste direita");
  servoEsq_f.write(velEsq(15));
  servoEsq_t.write(velEsq(15)); //20
  servoDir_f.write(velDir(10));  //10
  servoDir_t.write(velDir(10)); 
}

void reajusteEsquerda() {                   
  Serial.println("reajuste esquerda");
  servoEsq_f.write(velEsq(10));
  servoEsq_t.write(velEsq(10)); 
  servoDir_f.write(velDir(15));
  servoDir_t.write(velDir(15));
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
  servoDir_f.write(velDir(35));
  servoDir_t.write(velDir(35));
}

void esqre2() {
  servoEsq_f.write(velEsq(35));
  servoEsq_f.write(velEsq(35));
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
  delay(1500);
  frente2();
  delay(1300);
  direita2();
  delay(1500);
  frente2();
  delay(2300);
  direita2();
  delay(1500);
  frente2();
  delay(500);
  while (analogRead(sensor[1]) > valorSensor[1]) {
    frente2();
  }
  frente2();
  delay(100);
  while (analogRead(sensor[2]) > valorSensor[2]) {
    esquerda2();
  }
}

void desviadir() {
  re2();
  delay(150);
  direita2();
  delay(1500);
  frente2();
  delay(1300);
  esquerda2();
  delay(1500);
  frente2();
  delay(2400);
  esquerda2();
  delay(1500);
  frente2();
  delay(200);
  while (analogRead(sensor[1]) > valorSensor[1]) {
    frente2();
  }
  while (analogRead(sensor[2]) > valorSensor[2]) {
    direita2();
  }
}




#endif
