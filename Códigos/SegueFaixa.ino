#include <Servo.h>

Servo servodf;
Servo servodt;
Servo servoef;
Servo servoet;

#define ESQ A10
#define RESQ A11
#define MEIO A8
#define REDIR A12
#define DIR A9

bool front;
bool esq;
bool dir;
bool resq;
bool rdir;

const int pretfront = 300;
const int pretesq = 250;//290
const int pretdir = 430;//470
const int pretresq = 520;//480
const int pretrdir = 440;//400

void setup() {
  Serial.begin(9600);

  servodf.attach(11);
  servodt.attach(10);
  servoef.attach(12);
  servoet.attach(9);

  pinMode(ESQ, INPUT);
  pinMode(RESQ, INPUT);
  pinMode(MEIO, INPUT);
  pinMode(REDIR, INPUT);
  pinMode(DIR, INPUT);
}

void loop() {

  if (analogRead(MEIO) >= pretfront) {
    front = 1;
  }
  else{front = 0;}

  if (analogRead(RESQ) >= pretresq) {
    resq = 1;
  }
  else{ resq = 0;}

  if (analogRead(REDIR) >= pretrdir) {
    rdir = 1;
  }
  else{ rdir = 0;}

  if (analogRead(DIR) >= pretdir) {
    dir = 1;
  }
  else{ dir = 0;}

  if (analogRead(ESQ) >= pretesq) {
    esq = 1;
  }
  else{ esq = 0;}


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
    // 90 graus
    case 0b00101:  
    case 0b00111:
    case 0b01101:
    case 0b01111:
      frente();
      delay(200);
      while (analogRead(MEIO) >= pretfront) {
        devesquerda();
      }
      break;
    
    case 0b10100: 
    case 0b10110: 
    case 0b11100: 
    case 0b11110:
      frente();
      delay(200);
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
void dirpare() {
  servodf.write(90);
  servodt.write(90);
}
