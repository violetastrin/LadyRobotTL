#include "ladybase.h"

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

  if (tcs_soft.begin(&sWire)) {
    Serial.println("Found sensor soft");
  } else {
    Serial.println("No TCS34725 found ... check your connections (soft)");
    while (1)
      ;
  }

  if (tcs_real.begin(&Wire)) {
    Serial.println("Found sensor real");
  } else {
    Serial.println("No TCS34725 found ... check your connections (real)");
    while (1)
      ;
  }
}
void loop() {

  distancia = ultrasonic.read();
  Serial.print("distancia = ");
  Serial.print(distancia);

  leiturainfra();

  //------------------------- sequencia de if's
  if (distancia <= 5 && distancia > 0) {
    Serial.println("desviando");
    desviadir();
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

  int leituraEsq = esq;
  int leituraResq = resq;
  int leituraMeio = front;
  int leituraRedir = rdir;
  int leituraDir = dir;

  int estadoSensores = (leituraEsq << 4) | (leituraResq << 3) | (leituraMeio << 2) | (leituraRedir << 1) | leituraDir;

  switch (estadoSensores) {

      //----------------------------------------------- frente--------------------------------------------------------------
    case 0b10001:
      frente();
      break;

    //----------------------------------------------- 90 graus esquerda------------------------------------------------------
    case 0b00101:
    case 0b00111:
    case 0b01111:
    case 0b01101:
      novgrause();
      break;

    case 0b10100:
    case 0b11100:
    case 0b11110:
    case 0b10110:
      novgrausd();
      break;

    //----------------------------------------------- Reajuste ---------------------------------------------------
    case 0b10011:
      reajd();
      break;

    case 0b11001:
      reaje();
      break;

    //----------------------------------------------verde-----------------------------------------------------------
    case 0b00100: // T
    case 0b00000:
    case 0b00010:
    case 0b00110:
    case 0b01000:
    case 0b01100:
      encruzte();
      break;

    case 0b10000: //direita
    case 0b10010:
    case 0b11000:
      divd();
      break;


    case 0b00001: //esquerda
    case 0b00011:
    case 0b01001:
      dive();
      break;


    default:
      Serial.println("random");
      frente();
      break;
  }
}


//------------------------------------------------------- funções de ladrilhos---------------------------------------------------------------------

  void novgrausd() {
    Serial.println("90 direita");
      frente();
      delay(110);
      while (analogRead(MEIO) >= pretfront) {
        leiturainfra();
        devdireita();
      }
  }

  void novgrause() {
    Serial.println("90 esquerda");
      frente();
      delay(110);
      while (analogRead(MEIO) >= pretfront) {
        devesquerda();
        leiturainfra();
      }
  }

  void reajd() {
    Serial.println("reajuste direita");
      efrente();
      leiturainfra();
  }

  void reaje() {
   Serial.println("reajuste esquerda");
      dfrente();
      leiturainfra();
  }

  void encruzte() {
    Serial.println("encruzilhada ou T");
      pare();
      delay(500);
      leituraCor();

      if (dverde == 1 && everde == 1) { // dois verde
        Serial.println("beco");
        esquerda();
        delay(3000);
      }
      else if (everde == 0 && dverde == 1) { // direita verde
        Serial.print("direita verde");
        frente();
        delay(200);
        direita();
        delay(500);
        while (analogRead(MEIO) >= pretfront){
          direita();
        }
      }
      else if (everde == 1 && dverde == 0 ) { // esquerda verde
        Serial.print("esquerda verde");
        frente();
        delay(200);
        esquerda();
        delay(500);
        while (analogRead(MEIO) >= pretfront){
          esquerda();
        }
      }
      else{
        frente();
      }
  }
  void divd() {
    Serial.println("t - dir");
      pare();
      delay(300);
      leituraCor();

      if (dverde == 1) {
        Serial.print("direita verde");
      } else {
        frente();
      }
  }

  void dive() {
    Serial.println("t - esq");
      pare();
      delay(300);
      leituraCor();

      if (everde == 1) {
        Serial.print("esquerda verde");
      } else {
        frente();
      }
  }

//------------------------------------------------------- funções básicas motor -------------------------------------------------------------------------------

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
  delay(2400);
  direita2();
  delay(1600);
  while (analogRead(RESQ) > pretesq) {
    frente2();
  }
  while (analogRead(MEIO) > pretfront) {
    esquerda();
  }
}

void desviadir() {
  re2();
  delay(150);
  direita2();
  delay(1500);
  frente2();
  delay(1500);
  esquerda2();
  delay(1500);
  frente2();
  delay(2500);
  esquerda2();
  delay(1500);
  while (analogRead(RESQ) > pretesq) {
    frente2();
  }
  while (analogRead(MEIO) > pretfront) {
    direita();
  }
}

void leituraCor() {

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  Serial.print("ESQ (soft): ");
  Serial.print("Vermelho: "); Serial.print(r2);
  Serial.print(", Verde: "); Serial.print(g2);
  Serial.print(", Azul: "); Serial.print(b2);
  Serial.print(", Claro: "); Serial.print(c2);

  Serial.print(" | DIR (real): ");
  Serial.print("Vermelho: "); Serial.print(r1);
  Serial.print(", Verde: "); Serial.print(g1);
  Serial.print(", Azul: "); Serial.print(b1);
  Serial.print(", Claro: "); Serial.println(c1);

  uint16_t medrb1 = (r1 + b1) / 2;
  uint16_t medrb2 = (r2 + b2) / 2;

  if (c1 < 1400 && g1 > medrb1) {
    dverde = 1;
  } else {
    dverde = 0;
  }

  if (c2 < 2000 && g2 > medrb2) {
    everde = 1;
  } else {
    everde = 0;
  }
}