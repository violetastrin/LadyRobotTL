#include "ladybase.h"

void setup() {

  Serial.begin(9600);
  display.begin();

  servodf.attach(8);
  servodt.attach(7);
  servoef.attach(9);
  servoet.attach(6);

  pinMode(ESQ, INPUT);
  pinMode(RESQ, INPUT);
  pinMode(MEIO, INPUT);
  pinMode(REDIR, INPUT);
  pinMode(DIR, INPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  //pinMode(led, OUTPUT);
  //pinMode(buzzer, OUTPUT);

  if (tcs_soft.begin(&sWire)) {
    Serial.println("Found sensor soft");
  } else {
    display.println("No TCS soft found");
    Serial.println("No TCS34725 found ... check your connections (soft)");
    while (1);
  }

  if (tcs_real.begin(&Wire)) {
    Serial.println("Found sensor real");
  } else {
    display.println("No TCS real found");
    Serial.println("No TCS34725 found ... check your connections (real)");
    while (1);
  }
}

void loop() {

  distancia = ultrasonic.read();

  leiturainfra();

  while(true) {
    frente();
  }

  //------------------------- sequencia de if's
  if (distancia <= 5 && distancia > 0) {  //--------- distancia do desvia obstaculo
    Serial.println("desviando");
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("desvia");
    desviaesq();
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
      roxo();
      break;

    //----------------------------------------------- 90 graus esquerda------------------------------------------------------
    case 0b00101:
    case 0b00111:
    case 0b01111:
    case 0b01101:
      novgrause();
      roxo();
      break;

    case 0b10100:
    case 0b11100:
    case 0b11110:
    case 0b10110:
      novgrausd();
      roxo();
      break;

    //----------------------------------------------- Reajuste ---------------------------------------------------
    case 0b10011:
    case 0b10111:
      reajd();
      roxo();
      break;

    case 0b11001:
    case 0b11101:
      reaje();
      roxo();
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
      verde();
      break;

      // ---------------------------------------------cinza & vermelho-------------------------------------------------

    // case 0b11111:
    //   gapetc();
    //   break;

      //--------------------------------------------------------------------------------------------------------------------
    default:
      frente();
      break;
  }
}


//------------------------------------------------------- funções de ladrilhos---------------------------------------------------------------------

void novgrausd() {  //------------------------ 90º direita
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("90 graus - d");
  Serial.println("90 direita");
  frente();
  delay(40);

  while (analogRead(MEIO) >= 390) {
    leiturainfra();
    devdireita();
  }
}

void novgrause() {  //------------------------ 90º esquerda
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("90 graus - e");
  Serial.println("90 esquerda");
  frente();
  delay(40);

  while (analogRead(MEIO) >= 390) {
    devesquerda();
    leiturainfra();
  }
}

void reajd() {  //------------------------ resjuste direita
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("reaj - d");
  Serial.println("reajuste direita");
  efrente();
  leiturainfra();
}

void reaje() {  //------------------------ resjuste esquerda
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("reaj - e");
  Serial.println("reajuste esquerda");
  dfrente();
  leiturainfra();
}

void encruzte() {  //------------------------ encruzilhada com T
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("encruzted");
  Serial.println("encruzilhada ou T");
  re();
  delay(180);
  pare();
  delay(200);
  leituraCorG();
  verdes();

  if (dverde == 1 && everde == 1) {  //------------------------ beco
    Serial.println("beco");

    frente();
    delay(300);
    esquerda();
    delay(2000);

    while (analogRead(MEIO) >= 350) {
      esquerda();
    }

  } else if (everde == 0 && dverde == 1) {  // direita verde
    Serial.print("direita verde");

    frente();
    delay(390);
    direita();
    delay(700);

    while (analogRead(MEIO) >= 340) {
      direita();
    }

  } else if (everde == 1 && dverde == 0) {  // esquerda verde
    Serial.print("esquerda verde");


    frente();
    delay(390);
    esquerda();
    delay(700);

    while (analogRead(MEIO) >= 340) {
      esquerda();
    }

  } else {
    frente();
    delay(410);
  }
}


/*void gapetc() {
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("gap");
  Serial.println("gap");
  pare();
  delay(200);
  leituraCorReC();

  if (dvermelho == 1 && evermelho == 1) {
    Serial.println("vermelho");  // final
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("vermelho");
    pare();
    delay(6000);
    resgateD2();                         //---------------------------------- esses resgates aqui é so escolher qual caso 
  } else if (dcinza == 1 && ecinza == 1) {  // resgate
    Serial.print("cinza");
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("cinza");
    pare();
    delay(6000);
    resgateD2();
  } else {
    frente();
    delay(30);
  }
}*/  
