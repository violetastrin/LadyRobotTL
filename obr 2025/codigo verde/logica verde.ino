#include "ladyinsides.h"

void setup() {
  Serial.begin(9600);

  servoDir_f.attach(12);
  servoDir_t.attach(11);
  servoEsq_f.attach(6);
  servoEsq_t.attach(7);
}

void loop() {
    
  leiturainfra();
  distancia = ultrasonic.read();

  Serial.print(" sensorESQ = ");
  Serial.print(analogRead(sensor[0]));
  Serial.print(" sensorRE = ");
  Serial.print(analogRead(sensor[1]));
  Serial.print(" sensorMEIO = ");
  Serial.print(analogRead(sensor[2]));
  Serial.print(" sensorRD = ");
  Serial.print(analogRead(sensor[3]));
  Serial.print(" sensorDIR = ");
  Serial.println(analogRead(sensor[4]));

  if (distancia <= 4 && distancia > 0) {  //--------- distancia do desvia obstaculo
    desviaesq();
  }

  if (analogRead(core) >= 350 && analogRead(core) <= 500) {
    esquerdaverde = 1;
  } else {
    esquerdaverde = 0;
  }


  if (analogRead(cord) >= 200 && analogRead(cord) <= 300) {
    direitaverde = 1;
  } else {
    direitaverde = 0;
  }

  if (sensorMap[0] >= media[0]) {
    valorSensor[0] = 0;
  } else {
    valorSensor[0] = 1;
  }

  if (sensorMap[1] >= media[1]) {
    valorSensor[1] = 0;
  } else {
    valorSensor[1] = 1;
  }

  if (sensorMap[2] >= media[2]) {
    valorSensor[2] = 0;
  } else {
    valorSensor[2] = 1;
  }

  if (sensorMap[3] >= media[3]) {
    valorSensor[3] = 0;
  } else {
    valorSensor[3] = 1;
  }

  if (sensorMap[4] >= media[4]) {
    valorSensor[4] = 0;
  } else {
    valorSensor[4] = 1;
  }

  byte leitura = 0;
  for (int i = 0; i < 5; i++) {
    leitura |= valorSensor[i] << (4 - i);
  }

  Serial.print(leitura, BIN);
  Serial.print(" / ");
  Serial.println(analogRead(A2));

  switch (leitura) {

    //                    0 = preto; 1 = branco
    //                                                                  --frente--
    case 0b11011:  //frente (F)
      frente();
      break;

    //                                                            --90 graus esquerda--
    case 0b00111:  //esquerda ponta (EP); esquerda meio(E)
    case 0b01111:  //esquerda ponta (EP)
      parar();
      delay(200);
      novgrausEsquerda();
      break;

    //                                                            --90 graus direita--
    case 0b11100:  //direita ponta (DP); direita meio(D)
    case 0b11110:  //direita ponta (DP);
      parar();
      delay(200);
      novgrausDireita();
      break;

    //                                                                --Reajuste--
    case 0b10011:  //esquerda meio(EM); meio (M)
    case 0b10111:  //esquerda meio(E)
      reaje();
      break;

    case 0b11001:  //direita meio(DM); meio (M)
    case 0b11101:  //direita meio(DM)
      reajd();
      break;

    //                                                                  --gap--
    default:
      frente();
      break;


    //                                                                 --verde--
    case 0b00000:
    case 0b00011:
    case 0b11000:
    case 0b00100:
    case 0b10000:
    case 0b00001:
      re();
      delay(200);
      parar();
      delay(1000);
      verde();
      break;


      // case 0b00101:             90 esquerda       com EP, EM e DM
      // case 0b01101:             90 esquerda       com EP e DM
      // case 0b10100:             90 direita        com EM, DM e DP
      // case 0b10110:             90 direita        com EM e DP
  }
}

void verde() {
  analogWrite(eledverde, 255);
  analogWrite(dledverde, 255);
  delay(2000);
  
  Serial.print("Valor core (esquerda): ");
  Serial.print(analogRead(core));
  Serial.print("Valor cord (direita): ");
  Serial.println(analogRead(cord)); 


  if (analogRead(core) >= 350 && analogRead(core) <= 550 && analogRead(cord) >= 200 && analogRead(cord) <= 350) {
    Serial.print("Beco");
    parar();
    delay(1000);
    frente();
    delay(300);
    esquerda();
    delay(2000);
    digitalWrite(eledverde, LOW);
    digitalWrite(dledverde, LOW);

    while (analogRead(sensor[2]) <= 500) {
      esquerda();
    }
  } else if (analogRead(core) >= 350 && analogRead(core) <= 550 && direitaverde == 0) {
    Serial.print("Beco esquerda");
    parar();
    delay(1000);
    frente();
    delay(300);
    esquerda();
    delay(500);
    digitalWrite(eledverde, LOW);
    digitalWrite(dledverde, LOW);

    while (analogRead(sensor[2]) <= 500) {
      esquerda();
    }
  } else if (esquerdaverde == 0 && analogRead(cord) >= 200 && analogRead(cord) <= 350) {
    Serial.print("Beco direita");
    parar();
    delay(1000);
    frente();
    delay(20);
    direita();
    delay(500);
    digitalWrite(eledverde, LOW);
    digitalWrite(dledverde, LOW);

    while (analogRead(sensor[2]) <= 500) {
      direita();
    }
  } else {
    Serial.print("Sem verde");
    frente();
    delay(500);
    digitalWrite(eledverde, LOW);
    digitalWrite(dledverde, LOW);
  }
}

void everde() {
  digitalWrite(eledverde, HIGH);
  if (esquerdaverde == 1) {
    parar();
    delay(1000);
    frente();
    delay(300);
    esquerda();
    delay(2000);

    while (analogRead(sensor[2]) <= 500) {
      esquerda();
    }
  } else {
    frente();
    delay(300);
  }
}

void dverde() {
  digitalWrite(dledverde, HIGH);
  if (direitaverde == 1) {
    parar();
    delay(1000);
    frente();
    delay(20);
    direita();
    delay(500);

    while (analogRead(sensor[2]) <= 500) {
      direita();
    }
  } else {
    frente();
    delay(300);
  }
}

void novgrausDireita() {
  Serial.println("90 direita");
  frente();
  delay(20);

  while (analogRead(sensor[2]) <= 570) {
    direita();
  }
}

void novgrausEsquerda() {
  Serial.println("90 esquerda");
  frente();
  delay(20);

  while (analogRead(sensor[2]) <= 570) {
    esquerda();
  }
}


void reajd() {
  reajusteDireita();
}

void reaje() {
  reajusteEsquerda();
}
