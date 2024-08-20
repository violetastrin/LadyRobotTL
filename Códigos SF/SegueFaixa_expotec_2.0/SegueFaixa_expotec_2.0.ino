#include "ladybase.h"

void setup() {
  Serial.begin(9600);
  display.begin();

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
  
  /*tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  uint16_t medrbg1 = (r1 + b1 + g1) / 3;
  uint16_t medrbg2 = (r2 + b2 + g2) / 3;

    uint16_t med1 = medrbg1 * 1.075;
  uint16_t med2 = medrbg2 * 1.05;

  Serial.print("ESQ (soft): ");
  Serial.print("Verde: ");
  Serial.print(g2);
  Serial.print(", Media: ");
  Serial.print(medrbg2);
  Serial.print(" - ");
  Serial.print(med2);

  Serial.print(" | DIR (real): ");
  Serial.print("Verde: ");
  Serial.print(g1);
  Serial.print(", Media: ");
  Serial.print(medrbg1);
  Serial.print(" - ");
  Serial.println(med1);

  if (medrbg1 >= 4000) {
    dverde = 0;
  } else if (g1 >= med1){
    dverde = 1;
  }
  else{
    dverde = 0;
  }
  
  if (medrbg2 >= 4000)
  { everde = 0;
  }
   else if (g2 >= med2){
    everde = 1;
  }
  else{
    everde = 0;
  }
  Serial.print("ESQ (soft): ");
  Serial.print(everde);

  Serial.print(" | DIR (real): ");
  Serial.print(dverde);
  Serial.print(" / ");
  
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

  int estadoSensores = (esq << 4) | (resq << 3) | (front << 2) | (rdir << 1) | dir;

  Serial.println(estadoSensores, BIN);  
  delay(1000);
  return;*/

  distancia = ultrasonic.read();
  // Serial.print("distancia = ");
  // Serial.print(distancia);

  leiturainfra();

  //------------------------- sequencia de if's
  if (distancia <= 5 && distancia > 0) {
    Serial.println("desviando");
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("desvia");
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

  int estadoSensores = (esq << 4) | (resq << 3) | (front << 2) | (rdir << 1) | dir;

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
    case 0b00100:  // T
    case 0b00000:
    case 0b00010:
    case 0b00110:
    case 0b01000:
    case 0b01100:
    case 0b10000:  //direita
    case 0b10010:
    case 0b11000:
    case 0b00001:  //esquerda
    case 0b00011:
    case 0b01001:
      encruzte();
      break;

    /*case 0b10000:  //direita
    case 0b10010:
    case 0b11000:
      divd();
      break;


    case 0b00001:  //esquerda
    case 0b00011:
    case 0b01001:
      dive();
      break;*/


    default:
      Serial.println("random");
      frente();
      break;
  }
}


//------------------------------------------------------- funções de ladrilhos---------------------------------------------------------------------

void novgrausd() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("90 graus - d");
  Serial.println("90 direita");
  frente();
  delay(110);
  while (analogRead(MEIO) >= pretfront) {
    leiturainfra();
    devdireita();
  }
}

void novgrause() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("90 graus - e");
  Serial.println("90 esquerda");
  frente();
  delay(110);
  while (analogRead(MEIO) >= pretfront) {
    devesquerda();
    leiturainfra();
  }
}

void reajd() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("reaj - d");
  Serial.println("reajuste direita");
  efrente();
  leiturainfra();
}

void reaje() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("reaj - e");
  Serial.println("reajuste esquerda");
  dfrente();
  leiturainfra();
}

void encruzte() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("encruzte");
  Serial.println("encruzilhada ou T");
  re();
  delay(200);
  pare();
  delay(800);
  leituraCor();
  verdes();

  if (dverde == 1 && everde == 1) {  // dois verde                           [esse ta dando certo]
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("beco");
    Serial.println("beco");

    frente();
    delay(220);
    esquerda();
    delay(2500);

    while (analogRead(MEIO) >= pretfront) {
      esquerda();
    }

  } else if (everde == 0 && dverde == 1) {  // direita verde
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("dverde");
    Serial.print("direita verde");

    frente();
    delay(220);
    direita();
    delay(600);

    while (analogRead(MEIO) >= pretfront) {
      direita();
    }

  } else if (everde == 1 && dverde == 0) {  // esquerda verde
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("everde");
    Serial.print("esquerda verde");


    frente();
    delay(220);
    esquerda();
    delay(600);

    while (analogRead(MEIO) >= pretfront) {
      esquerda();
    }

  } else {
    frente();
    delay(160);
  }
}
/*void divd() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("divd");
  Serial.println("t - dir");
  verdes();

  pare();
  delay(500);
  leituraCor();

  if (dverde == 1 && everde == 1) {  // dois verde                           [esse ta dando certo]
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("beco");
    Serial.println("beco");

    frente();
    delay(220);
    esquerda();
    delay(2500);

    while (analogRead(MEIO) >= pretfront) {
      esquerda();
    }

  } else if (everde == 0 && dverde == 1) {  // direita verde
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("dverde");
    Serial.print("direita verde");

    frente();
    delay(220);
    direita();
    delay(600);

    while (analogRead(MEIO) >= pretfront) {
      direita();
    }

  } else if (everde == 1 && dverde == 0) {  // esquerda verde
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("everde");
    Serial.print("esquerda verde");


    frente();
    delay(220);
    esquerda();
    delay(600);

    while (analogRead(MEIO) >= pretfront) {
      esquerda();
    }

  } else {
    frente();
    delay(160);
  }
}

void dive() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("dive");
  Serial.println("t - esq");
  verdes();

  pare();
  delay(500);
  leituraCor();

  if (dverde == 1 && everde == 1) {  // dois verde                           [esse ta dando certo]
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("beco");
    Serial.println("beco");

    frente();
    delay(220);
    esquerda();
    delay(2500);

    while (analogRead(MEIO) >= pretfront) {
      esquerda();
    }

  } else if (everde == 0 && dverde == 1) {  // direita verde
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("dverde");
    Serial.print("direita verde");

    frente();
    delay(220);
    direita();
    delay(600);

    while (analogRead(MEIO) >= pretfront) {
      direita();
    }

  } else if (everde == 1 && dverde == 0) {  // esquerda verde
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("everde");
    Serial.print("esquerda verde");


    frente();
    delay(220);
    esquerda();
    delay(600);

    while (analogRead(MEIO) >= pretfront) {
      esquerda();
    }

  } else {
    frente();
    delay(160);
  }
}*/

//------------------------------------------------------- funções básicas motor -------------------------------------------------------------------------------

void dfrente() {  //                   ---- reajuste direita frente
  Serial.println("reajuste direita");
  servoef.write(160);
  servoet.write(160);
  servodf.write(70);
  servodt.write(70);
}

void efrente() {  //                  ----- reajuste esquerda frente
  Serial.println("reajuste esquerda");
  servoef.write(110);
  servoet.write(110);
  servodf.write(20) ;
  servodt.write(20);
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
