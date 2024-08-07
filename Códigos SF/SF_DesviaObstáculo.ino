#include <Servo.h>       // Biblioteca do servo
#include <Ultrasonic.h>  // Biblioteca do sensor de obstáculo

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

// Limiares para os sensores de linha
const int pretfront = 270;
const int pretesq = 410;
const int pretdir = 500;
const int pretresq = 350;
const int pretrdir = 300;

Ultrasonic ultrasonic(8, 9);  // trig primeiro depois echo
int distancia;

void setup() {
  Serial.begin(9600);

  servodf.attach(6);
  servodt.attach(7);
  servoef.attach(4);
  servoet.attach(5);

  pinMode(ESQ, INPUT);
  pinMode(RESQ, INPUT);
  pinMode(MEIO, INPUT);
  pinMode(REDIR, INPUT);
  pinMode(DIR, INPUT);
}

void loop() {
  distancia = ultrasonic.read();

  //------------------------- sequencia de if's
  if (distancia <= 4 && distancia > 0) {
    Serial.println("desviando");
    desviadir();
    //while (analogRead(MEIO) >= pretfront) {
    //  giroabesq();
    //}
  }

  if (analogRead(MEIO) >= pretfront) {
    front = 1;
  } else {
    front = 0;
  }

  if (analogRead(RESQ) >= pretresq) {
    resq = 1;
  } else {
    resq = 0;
  }

  if (analogRead(REDIR) >= pretrdir) {
    rdir = 1;
  } else {
    rdir = 0;
  }

  if (analogRead(DIR) >= pretdir) {
    dir = 1;
  } else {
    dir = 0;
  }

  if (analogRead(ESQ) >= pretesq) {
    esq = 1;
  } else {
    esq = 0;
  }

  Serial.print("distancia = ");
  Serial.print(distancia);
  leiturainfra();

  int leituraEsq = esq;
  int leituraResq = resq;
  int leituraMeio = front;
  int leituraRedir = rdir;
  int leituraDir = dir;

  int estadoSensores = (leituraEsq << 4) | (leituraResq << 3) | (leituraMeio << 2) | (leituraRedir << 1) | leituraDir;

  switch (estadoSensores) {

      //----------------------------------------------- frente
    case 0b10001:
      frente();
      break;

    //----------------------------------------------- 90 graus esquerda
    case 0b00101:
    case 0b00111:
    case 0b01101:
    case 0b01111:
      Serial.println("90 esquerda");
      frente();
      delay(100);
      while (analogRead(MEIO) >= pretfront) {
        leiturainfra();
        devesquerda();
      }
      break;

    //----------------------------------------------- 90 graus direita
    case 0b10100:
    case 0b10110:
    case 0b11100:
    case 0b11110:
      Serial.println("90 direita");
      frente();
      delay(100);
      while (analogRead(MEIO) >= pretfront) {
        leiturainfra();
        devdireita();
      }
      break;

    //----------------------------------------------- Reajuste
    case 0b10011:
      Serial.println("reajuste direita");
      re();
      delay(85);
      while (analogRead(REDIR) >= pretrdir) {
        efrente();
        leiturainfra();
      }
      break;

    case 0b11001:
      Serial.println("reajuste esquerda");
      re();
      delay(85);
      while (analogRead(RESQ) >= pretresq) {
        dfrente();
        leiturainfra();
      }
      break;
    
  }
}

//------------------------------------------------------- funções básicas motor -------------------------------------------------------------------------------
void leiturainfra() {
  Serial.print(" S_esq: " + String(esq));
  Serial.print(" S_front: " + String(front));
  Serial.print(" S_dir: " + String(dir));
  Serial.print(" S_redir: " + String(rdir));
  Serial.println(" S_resq: " + String(resq));
}

void frente() {
  Serial.println("FRENTE");
  esqfrente();
  dirfrente();
}

void dfrente() {  //                   ---- reajuste direita frente
  Serial.println("reajuste direita");
  esqfrente();
  devdirfrente();
}

void efrente() {  //                  ----- reajuste esquerda frente
  Serial.println("reajuste esquerda");
  devesqfrente();
  dirfrente();
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

void reajesq() {
  Serial.println("RESJUSTE ESQ");
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

void reajdir() {
  Serial.println("REAJUSTE DIR");
  devesqfrente();
  devdirre();
}

void pare() {
  Serial.println("PARE");
  esqpare();
  dirpare();
}

//------------------- normal

void esqfrente() {
  servoef.write(125);
  servoet.write(125);
}

void esqre() {
  servoef.write(55);
  servoet.write(55);
}

void dirfrente() {
  servodf.write(55);
  servodt.write(55);
}

void dirre() {
  servodf.write(125);
  servodt.write(125);
}

//-------------------- slow

void devesqfrente() {
  servoef.write(110);
  servoet.write(110);
}

void devesqre() {
  servoef.write(70);
  servoet.write(70);
}

void devdirfrente() {
  servodf.write(70);
  servodt.write(70);
}

void devdirre() {
  servodf.write(110);
  servodt.write(110);
}

//--------------------- fast

void fesqfrente() {
  servoef.write(170);
  servoet.write(170);
}

void fesqre() {
  servoef.write(10);
  servoet.write(10);
}

void fdirfrente() {
  servodf.write(10);
  servodt.write(10);
}

void fdirre() {
  servodf.write(170);
  servodt.write(170);
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

//----------------------  desvia obstáculo
void desviaesq() {
  re2();
  delay(200);
  esquerda2();
  delay(1400);
  frente2();
  delay(1500);
  direita2();
  delay(400);
  frente2();
  delay(1000);
  direita2();
  delay(600);
  while (analogRead(RESQ) > pretresq){
    frente2();
  }
  frente();
  delay(50);
  while (analogRead(MEIO) > pretfront){
    esquerda();
  }
}

void desviadir() {
  re2();
  delay(200);
  direita2();
  delay(1400);
  frente2();
  delay(1500);
  esquerda2();
  delay(400);
  frente2();
  delay(1000);
  esquerda2();
  delay(600);
  while (analogRead(RESQ) > pretresq){
    frente2();
  }
  frente();
  delay(50);
  while (analogRead(MEIO) > pretfront){
    direita();
  }
}
