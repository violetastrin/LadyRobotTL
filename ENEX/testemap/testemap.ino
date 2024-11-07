#include "definir.h"

void setup() {
  Serial.begin(9600);
  
  display.begin();
 
  servoDir_f.attach(8);
  servoDir_t.attach(7);
  servoEsq_f.attach(9);
  servoEsq_t.attach(6);

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

leiturainfra();
//reajd();
//return;

  if (sensorMap[0] <= media[0] ){valorSensor[0] = 0;} else{valorSensor[0] = 1;}

  if (sensorMap[1] <= media[1] ){valorSensor[1] = 0;} else {valorSensor[1] = 1;}
    
  if (sensorMap[2] <= media[2] ){valorSensor[2] = 0;} else {valorSensor[2] = 1;}
    
  if (sensorMap[3] <= media[3] ){valorSensor[3] = 0;} else {valorSensor[3] = 1;}
    
  if (sensorMap[4] <= media[4] ){valorSensor[4] = 0;} else {valorSensor[4] = 1;}


byte leitura = 0;
  for(int i =  0; i<5; i++){
  leitura |= valorSensor[i] << (4-i);
  }

Serial.println(leitura, BIN);

switch (leitura) {

    //frente
    case 0b10001:
      frente();
      break;

    //90 graus, esquerda
    case 0b00101:
    case 0b00111:
    case 0b01111:
    case 0b01101:
      novgrausEsquerda();
      break;
      
    //90 graus, direita
    case 0b10100:
    case 0b11100:
    case 0b11110:
    case 0b10110:
      novgrausDireita();
      break;

    //Reajuste 
    case 0b10011:
    case 0b10111:
      reaje();
      break;

    case 0b11001:
    case 0b11101:
      reajd();
      break;

    //verde
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

      // cinza & vermelho

    // case 0b11111:
    //   gapetc();
    //   break;

      
    default:
      frente();
      Serial.println("frente");
      break;
  }
}


// funções de ladrilhos

void novgrausDireita() {  //90º direita
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("90 graus - d");

  Serial.println("90 direita");

  frente();
  delay(40);

  while (analogRead(sensor[2]) >= 390) {
    leiturainfra();
    devagarDireita();
  }
}

void novgrausEsquerda() {  // 90º esquerda
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("90 graus - e");

  Serial.println("90 esquerda");
  frente();
  delay(40);

  while (analogRead(sensor[2]) >= 390) {
    devagarEsquerda();
    leiturainfra();
  }
}

void reajd() {  //resjuste direita
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("reaj d");
  Serial.println("reajuste direita");
  reajusteDireita();
  leiturainfra();
}

void reaje() {  //resjuste esquerda
  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("reaj e");
  Serial.println("reajuste esquerda");
  reajusteEsquerda();
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
  parar();
  delay(200);
  leituraCorG();

  if (direita_verde == 1 && esquerda_verde == 1) {  //------------------------ beco
    Serial.println("beco");

    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("beco");

    // frente();
    // delay(300);
    // esquerda();
    // delay(2000);

    // while (analogRead(sensor[2]) >= 350) {
    //   esquerda();
   // }

  } else if (esquerda_verde == 0 && direita_verde == 1) {  // direita verde
    Serial.println("direita verde");

    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("direita verde");

    // frente();
    // delay(390);
    // direita();
    // delay(700);

    // while (analogRead(sensor[2]) >= 340) {
    //   direita();
    // }

  } else if (esquerda_verde == 1 && direita_verde == 0) {  // esquerda verde
    Serial.println("esquerda verde");

  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("esquerda verde");

    // frente();
    // delay(390);
    // esquerda();
    // delay(700);

    // while (analogRead(sensor[2]) >= 340) {
    //   esquerda();
    // }

  } //else {
  //   frente();
  //   delay(410);
  // } /
}
