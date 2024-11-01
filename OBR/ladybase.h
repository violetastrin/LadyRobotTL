#ifndef rodar
#define rodar
#define blue 11
#define green 12
#define red 13
//#define led 19
//#define buzzer 20

#include <Servo.h>       // Biblioteca do servo
#include <Ultrasonic.h>  // Biblioteca do sensor de obstáculo
#include <SoftwareWire.h>
#include <Wire.h>
#include <Adafruit_TCS34725_SWwire.h>
#include <Arduino.h>
#include <MicroLCD.h>

LCD_SSD1306 display; /* for SSD1306 OLED module */

SoftwareWire sWire(5, 4);

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

#define ESQ A0
#define RESQ A3
#define MEIO A4
#define REDIR A5
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
// ORDEM: ESQUERDA, REAJUSTE ESQUERDA, FRENTE, REAJUSTE DIREITA, DIREITA
int valoresPreto[] = {325, 184, 450, 445, 434};

int valoresBranco[] = {984, 982, 988, 986, 988};

/*const int pretfront = 300;
const int pretesq = 310;
const int pretdir = 390;
const int pretresq = 410;
const int pretrdir = 300;*/

Ultrasonic ultrasonic(8, 9);  // trig primeiro depois echo
int distancia;

//-----------------FUNÇOES SERVOS ------------------------------- FUNÇOES SERVOS --------------------------------- FUNÇOES SERVOS -------------------------------------

//------------------- função giro 360º
// void giro360(){
//     direita2();
//     delay(5600);
// }

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
  servoef.write(110);
  servoet.write(110);
  servodf.write(70);
  servodt.write(70);
}

//------------------------- esquerda para resgate

void esquerdinha() {
  servodf.write(70);
  servodt.write(70);
  servoef.write(70);
  servoet.write(70);
}

//------------------------- direita para resgate

void direitinha() {
  servodf.write(110);
  servodt.write(110);
  servoef.write(110);
  servoet.write(110);
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

//------------------------------------------------------- funções básicas motor -------------------------------------------------------------------------------

void dfrente() {  //                   ---- reajuste direita frente
  Serial.println("reajuste direita");
  servoef.write(125);
  servoet.write(125);
  servodf.write(75);
  servodt.write(75);
}

void efrente() {  //                  ----- reajuste esquerda frente
  Serial.println("reajuste esquerda");
  servoef.write(105);
  servoet.write(105);
  servodf.write(55);
  servodt.write(55);
}

void re() {
  Serial.println("RÉ");
  esqre();
  dirre();
}

void esquerda() {  //--------------- virando para esquerda
  Serial.println("ESQUERDA");
  esqre();
  dirfrente();
}
void devesquerda() {  //----------------- virando para esquerda devagar
  Serial.println("DEVESQUERDA");
  devesqre();
  devdirfrente();
}

void direita() {  //----------------- virando para direta
  Serial.println("DIREITA");
  esqfrente();
  dirre();
}

void devdireita() {  //----------------- virando para direita devagar
  Serial.println("DEVDIREITA");
  devesqfrente();
  devdirre();
}

void pare() {
  Serial.println("PARE");
  esqpare();
  dirpare();
}


void leiturainfra() {
  Serial.print(" S_esq: " + String(esq));
  Serial.print(" S_front: " + String(front));
  Serial.print(" S_dir: " + String(dir));
  Serial.print(" S_redir: " + String(rdir));
  Serial.println(" S_resq: " + String(resq));
  Serial.print(analogRead(ESQ));
  Serial.print("             ");
  Serial.print(analogRead(RESQ));
  Serial.print("             ");
  Serial.print(analogRead(MEIO));
  Serial.print("             ");
  Serial.print(analogRead(REDIR));
  Serial.print("             ");
  Serial.println(analogRead(DIR));
}

void leituraCorG() {

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  uint16_t medrbg1 = (r1 + b1 + g1) / 3;
  uint16_t medrbg2 = (r2 + b2 + g2) / 3;

  uint16_t med1 = medrbg1 * 1.062;
  uint16_t med2 = medrbg2 * 1.025;

  if (medrbg1 >= 8000) {
    dverde = 0;
  } else if (g1 >= med1) {
    dverde = 1;
  } else {
    dverde = 0;
  }


  if (medrbg2 >= 8000) {
    everde = 0;
  } else if (g2 >= med2) {
    everde = 1;
  } else {
    everde = 0;
  }
  Serial.print("ESQ (soft): ");
  Serial.print(", Verde: ");
  Serial.print(g2);
  Serial.print(", vermelho: ");
  Serial.print(r2);
  Serial.print(", azul: ");
  Serial.print(b2);
  Serial.print(", Media: ");
  Serial.println(med2);


  Serial.print(" | DIR (real): ");
  Serial.print(", Verde: ");
  Serial.print(g1);
  Serial.print(", vermelho: ");
  Serial.print(r1);
  Serial.print(", azul: ");
  Serial.print(b1);
  Serial.print(", Media: ");
  Serial.println(med2);

  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_SMALL);
  display.print("EG: ");
  display.print(g2);
  display.print("ER: ");
  display.println(r2);
  display.print("EB: ");
  display.print(b2);
  display.print("EM: ");
  display.println(med2);

  display.print(" DG: ");
  display.print(g1);
  display.print(" DR: ");
  display.println(r1);
  display.print(" DB: ");
  display.print(b1);
  display.print(" DM: ");
  display.println(med1);
  delay(2500);  // LEMBRAR DE TIRAR EH SO PARA DEBUG!!!!!!*
}

void leituraCorReC() {

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  uint16_t medrbg1 = (r1 + b1 + g1) / 3;
  uint16_t medrbg2 = (r2 + b2 + g2) / 3;

  uint16_t med1 = medrbg1 * 1.05;
  uint16_t med2 = medrbg2 * 1.045;

  //------------------------------------------------------------------------
  if (r1 > medrbg1 && c1 < 18000) {
    dvermelho = 1;
    Serial.println("vermelho direita");
  } else {
    dvermelho = 0;
    Serial.println("branco direita");
  }

  if (r2 > 4200) {
    evermelho = 1;
    Serial.println("vermelho esquerda");
  } else {
    evermelho = 0;
    Serial.println("branco esquerda");
  }
  // ---------------------------------------------------------------------
  if (medrbg1 < 7200 && c1 > medrbg1) {  // ESQ (soft): Vermelho: 5359, Verde: 6707, Azul: 7441, Claro: 19596 | DIR (real): Vermelho: 4126, Verde: 5991, Azul: 7038, Claro: 16439
    dcinza = 1;
    Serial.println("cinza direita");  // ESQ (soft): Vermelho: 6780, Verde: 8229, Azul: 8984, Claro: 23597 | DIR (real): Vermelho: 6163, Verde: 8526, Azul: 9827, Claro: 23062
  } else {
    dcinza = 0;
    Serial.println("branco direita");
  }


  if (medrbg2 <= 8000 && c2 > medrbg2) {
    ecinza = 1;
    Serial.println("cinza esquerda");
  } else {
    ecinza = 0;
    Serial.println("branco esquerda");
  }
  //----------------------------------------------------------------------



  Serial.print("ESQ (soft): ");
  Serial.print("Vermelho: ");
  Serial.print(r2);
  Serial.print(", Verde: ");
  Serial.print(g2);
  Serial.print(", Azul: ");
  Serial.print(b2);
  Serial.print(", Claro: ");
  Serial.println(c2);
  Serial.print("Media esq: ");
  Serial.println(medrbg2);


  Serial.print("DIR (real): ");
  Serial.print("Vermelho: ");
  Serial.print(r1);
  Serial.print(", Verde: ");
  Serial.print(g1);
  Serial.print(", Azul: ");
  Serial.print(b1);
  Serial.print(", Claro: ");
  Serial.println(c1);
  Serial.print("Media dir: ");
  Serial.println(medrbg1);

  // display.clear();
  // display.setCursor(0, 0);
  // display.setFontSize(FONT_SIZE_SMALL);
  // display.print("Esq R: ");
  // display.println(r2);
  // display.print("Esq M: ");
  // display.println(medrbg2);
  // display.print("Dir R: ");
  // display.println(r1);
  // display.print("Dir M: ");
  // display.println(medrbg1);
  // delay(1000);  // LEMBRAR DE TIRAR EH SO PARA DEBUG!!!!!!*/
}

void verdes() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.print("Esq: ");
  display.println(everde);
  display.print("Dir: ");
  display.println(dverde);
  delay(500);
}

void vermelhos() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.print("Esq: ");
  display.println(evermelho);
  display.print("Dir: ");
  display.println(dvermelho);
  delay(500);
}

void roxo() {
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(green, LOW);
}

void verde() {
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, HIGH);
}

void ciano() {
  digitalWrite(red, LOW);
  digitalWrite(blue, HIGH);
  digitalWrite(green, HIGH);
}

void brancoo() {
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  digitalWrite(green, HIGH);
}



//----------------------------------------------------------------------- caso peçam para acender um led ----------------------------------------------------------------------------

//lembrar que é preciso descomentar o pino 19 e o pinMode no void setup

// void ledpiscar(){                       //----------------- teste do que pode ser o desafio surpresa com o led
//     digitalWrite(led, HIGH);
//     delay(2000);
//     digitalWrite(led, LOW);
//   }
// }


//----------------------------------------------------------------------- caso peçam para tocar um buzzer ----------------------------------------------------------------------------

// lemrar que é preciso descomenta o pino 20 do buzzer e o pinMode no void setup


// void buzzerdesafio(){
//   digitalWrite(buzzer, HIGH);
//   delay(2000);
//   digitalWrite(buzzer, LOW);
// }

//------------------------------------------------------------------- salas de resgate ----------------------------------------------------------------------

void resgateD1() {  //--------- resgate sala esquerda lado maior; ---------- se a saida estiver na frente ou esquerda frente
  brancoo();
  frente();
  delay(1000);
  esquerda();
  delay(1200);
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println(ultrasonic.read());
  pare();
  delay(200);
  if (ultrasonic.read() <= 20) {
    direita();
    delay(1200);
    while (ultrasonic.read() > 7) {
      frente();
    }
  }

  esquerdinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq)
      frente();
  }

  else {
    direitinha();
    delay(5900);
  }
}

void resgateD2() {  //--------- resgate sala esquerda lado maior -------------------- se a saida estiver direita frente ou direita esquerda
  brancoo();
  frente();
  delay(1000);
  esquerda();
  delay(1200);
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println(ultrasonic.read());
  pare();
  delay(200);
  if (ultrasonic.read() <= 20) {
    direita();
    delay(1200);
  }

  frente();
  delay(3100);

  direitinha();
  delay(1200);

  frente();
  delay(3800);

  while (ultrasonic.read() <= 9){
    frente();
  }

  direitinha();
  delay(1400);

  while (ultrasonic.read() > 6) {
    frente();
  }

  esquerdinha();
  delay(3000);

  while (analogRead(RESQ) > pretresq){
    frente();
  }
}
  // if (ultrasonic.read() > 89) {
  //   while (analogRead(RESQ) > pretresq && analogRead(REDIR) > pretrdir && analogRead(MEIO) > pretfront && analogRead(ESQ) > pretesq && analogRead(DIR) > pretdir) {
  //     frente();
  //   }
  // }

  // else {
  //   esquerdinha();
  //   delay(3000);
  // }

  // if (ultrasonic.read() > 89) {
  //   while (analogRead(RESQ) > pretresq) {
  //     frente();
  //   }
  // }
// }

void resgateD3() {  //--------- resgate sala direita com os dois triangulos em cima
  brancoo();
  frente();
  delay(1000);
  esquerda();
  delay(1200);
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println(ultrasonic.read());
  pare();
  delay(200);
  if (ultrasonic.read() <= 20) {
    direita();
    delay(1200);
    while (ultrasonic.read() > 7) {
      frente();
    }
  }

  esquerdinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(2900);
  }

  frente();
  delay(2500);

  direitinha();
  delay(2000);

  frente();
  delay(4500);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(4200);
  }
  frente();
  delay(4800);

  esquerdinha();
  delay(2000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(3000);
  }

  frente();
  delay(2900);

  esquerdinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}


void resgateE1() {  //--------- resgate sala esquerda lado maior; ---------- se a saida estiver na frente ou direita frente
  brancoo();
  frente();
  delay(1000);
  direita();
  delay(1200);
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println(ultrasonic.read());
  pare();
  delay(200);
  if (ultrasonic.read() <= 20) {
    esquerda();
    delay(1200);
    while (ultrasonic.read() > 7) {
      frente();
    }
  }

  direitinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq)
      frente();
  }

  else {
    esquerdinha();
    delay(5900);
  }
}

void resgateE2() {  //--------- resgate sala esquerda lado maior -------------------- se a saida estiver esquerda frente ou esquerda direita
  brancoo();
  frente();
  delay(1000);
  direita();
  delay(1200);
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println(ultrasonic.read());
  pare();
  delay(200);
  if (ultrasonic.read() <= 20) {
    esquerda();
    delay(1200);
    while (ultrasonic.read() > 7) {
      frente();
    }
  }

  direitinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(2900);
  }

  frente();
  delay(2300);

  esquerdinha();
  delay(2000);

  frente();
  delay(4500);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}

void resgateE3() {  //--------- resgate sala esquerda com os dois triangulos em cima
  brancoo();
  frente();
  delay(1000);
  direita();
  delay(1200);
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println(ultrasonic.read());
  pare();
  delay(200);
  if (ultrasonic.read() <= 20) {
    esquerda();
    delay(1200);
    while (ultrasonic.read() > 7) {
      frente();
    }
  }

  direitinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(2900);
  }

  frente();
  delay(2500);

  esquerdinha();
  delay(2000);

  frente();
  delay(4500);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(4200);
  }
  frente();
  delay(4800);

  direitinha();
  delay(2000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(3000);
  }

  frente();
  delay(2900);

  direitinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}

//----------------------  desvia obstáculo -------------------------------------------------------------------------

void desviaesq() {
  ciano();
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
  while (analogRead(RESQ) > pretesq) {
    frente2();
  }
  frente();
  delay(100);
  while (analogRead(MEIO) > pretfront) {
    esquerda();
  }
}

void desviadir() {
  ciano();
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
  while (analogRead(RESQ) > pretdir) {
    frente2();
  }
  while (analogRead(MEIO) > pretfront) {
    direita();
  }
}


//------------------------------------------------------ voids resgate para entrada do lado menor

void resgatepeqE1() {  // ---------------------- pra frente ou esquerda
  while (ultrasonic.read() > 7) {
    frente();
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}

void resgatepeqE2() {  // ----------------------- na diagonal direita
  while (ultrasonic.read() > 7) {
    frente();
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(4500);
  }

  frente();
  delay(2500);

  direitinha();
  delay(3200);

  frente();
  delay(4500);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}

void resgatepeqE3() {  // -------------------------- embaixo no oposto da entrada
  while (ultrasonic.read() > 7) {
    frente();
  }

  esquerdinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(5950);
  }

  frente();
  delay(3000);

  direitinha();
  delay(3200);

  frente();
  delay(3000);

  direitinha();
  delay(3000);

  frente();
  delay(5500);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}

void resgatepeqD1() {  // ---------------------- pra frente ou direita
  while (ultrasonic.read() > 7) {
    frente();
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}

void resgatepeqD2() {  // ----------------------- na diagonal esquerda
  while (ultrasonic.read() > 7) {
    frente();
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(4500);
  }

  frente();
  delay(2500);

  esquerdinha();
  delay(3200);

  frente();
  delay(4500);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}

void resgatepeqD3() {  // -------------------------- embaixo no oposto da entrada
  while (ultrasonic.read() > 7) {
    frente();
  }

  direitinha();
  delay(3000);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    esquerdinha();
    delay(5950);
  }

  frente();
  delay(3000);

  esquerdinha();
  delay(3200);

  frente();
  delay(3000);

  esquerdinha();
  delay(3000);

  frente();
  delay(5500);

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }

  else {
    direitinha();
    delay(3000);
  }

  if (ultrasonic.read() > 89) {
    while (analogRead(RESQ) > pretresq) {
      frente();
    }
  }
}

#endif
