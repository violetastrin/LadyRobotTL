#include <Servo.h>       //Biblioteca do servo
#include <Ultrasonic.h>  //Biblioteca do sensor de obstáculo

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

const int pretfront = 350;
const int pretesq = 330;   
const int pretdir = 210;   
const int pretresq = 450;  
const int pretrdir = 320; 


Ultrasonic ultrasonic(12,13);  // trig primeiro depois echo
int distancia;


void setup() {
  Serial.begin(9600);

  servodf.attach(10);
  servodt.attach(9);
  servoef.attach(11);
  servoet.attach(8);

  pinMode(ESQ, INPUT);
  pinMode(RESQ, INPUT);
  pinMode(MEIO, INPUT);
  pinMode(REDIR, INPUT);
  pinMode(DIR, INPUT);
}

void loop() {

  distancia = ultrasonic.read();

  //------------------------- sequencia de if's

  if (distancia <= 5 && distancia > 0) {
    Serial.println("desviando");
    desviaesq();
    while (analogRead(MEIO) >= pretfront) {
      giroabdir();
    }
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

  Serial.print("distandia = "); Serial.print(distancia); 
  Serial.print(" S_esq: " + String(esq));
  Serial.print(" S_front: " + String(front));
  Serial.print(" S_dir: " + String(dir));
  Serial.print(" S_redir: " + String(rdir));
  Serial.println(" S_resq: " + String(resq));

  int leituraEsq = esq;
  int leituraResq = resq;
  int leituraMeio = front;
  int leituraRedir = rdir;
  int leituraDir = dir;

  int estadoSensores = (leituraEsq << 4) | (leituraResq << 3) | (leituraMeio << 2) | (leituraRedir << 1) | leituraDir;

  switch (estadoSensores) {

    //frente 
    case 0b10001:
      frente();
      break;

    // 90 graus
    case 0b00101:
    case 0b00111:
    case 0b01101:
    case 0b01111:
      Serial.println("90 esquerda");
      frente();
      delay(100);
      while (analogRead(MEIO) >= pretfront) {
        devesquerda();
      }
      break;

    case 0b10100:
    case 0b10110:
    case 0b11100:
    case 0b11110:
      Serial.println("90 direita");
      frente();
      delay(100);
      while (analogRead(MEIO) >= pretfront) {
        devdireita();
      }
      break;

    // Reajuste
    case 0b10011:
      while ((analogRead(DIR) >= pretdir) || (analogRead(REDIR) >= pretrdir)) {
        devesquerda();
      }
      break;

    case 0b11001:
      while ((analogRead(ESQ) >= pretesq) || (analogRead(RESQ) >= pretresq)) {
        devdireita();
      }
      break;

    default:
      Serial.println("Default");
      frente();
      break;
  }
}

//------------------------------------------------------- funções básicas motor -------------------------------------------------------------------------------
void frente() {
  Serial.println("FRENTE");
  esqfrente();
  dirfrente();
}

void dfrente() {
  Serial.println("reajuste direita");
  fesqfrente();
  devdirfrente();
}

void efrente() {
  Serial.println("reajuste esquerda");
  devesqfrente();
  fdirfrente();
}

void re() {
  Serial.println("RÉ");
  esqre();
  dirre();
}

void esquerda() {
  Serial.println("ESQUERDA");
  esqre();
  dirfrente();
}

void devesquerda() {
  Serial.println("DEVESQUERDA");
  devesqre();
  devdirfrente();
}

void direita() {
  Serial.println("DIREITA");
  esqfrente();
  dirre();
}

void devdireita() {
  Serial.println("DEVDIREITA");
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
  servoef.write(115);
  servoet.write(115);
}

void devesqre() {
  servoef.write(65);
  servoet.write(65);
}

void devdirfrente() {
  servodf.write(65);
  servodt.write(65);
}

void devdirre() {
  servodf.write(115);
  servodt.write(115);
}

//--------------------- fast

void fesqfrente() {
  servoef.write(130);
  servoet.write(130);
}

void fesqre() {
  servoef.write(20);
  servoet.write(20);
}

void fdirfrente() {
  servodf.write(0);
  servodt.write(0);
}

void fdirre() {
  servodf.write(150);
  servodt.write(150);
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

//---------------------- funções desvia obstáculo

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

//----------------------  desvia obstáculo

void desviaesq() {
  re();
  delay(200);
  devesquerda();
  delay(1500);
  giroabdir();
  delay(1500);
  direita();
  delay(400);
  giroabdir();
  delay(600);
  direita();
  delay(550);
}
