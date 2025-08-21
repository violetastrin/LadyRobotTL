#include "ladyinsides.h"

bool contagem = false;
int tempoo = 0;
int estado = 0;

void saladeresgate() {
  Serial.println("Entrando na sala de resgate!");
  while (true) {
    long distanciaFrente = ultrasonic.read();
    long distanciaDireita = ultrasonic2.read();

    Serial.print("Frente: ");
    Serial.print(distanciaFrente);
    Serial.print(" cm | Direita: ");
    Serial.print(distanciaDireita);
    Serial.println(" cm");

    // Caso 1: pode andar pra frente
    if (distanciaFrente > 4 || distanciaDireita <= 7) {
      frente();
    }
    // Caso 2: virar para a direita
    else if (distanciaFrente <= 4 && distanciaDireita > 7) {
      direita();
    }
    // Caso 3: virar para a esquerda
    else if (distanciaFrente <= 4 && distanciaDireita <= 7) {
      esquerda();
    }

    delay(100); // pequena pausa para estabilidade
  }
}

void verificasala() {

  int leitEsqP = digitalRead(sensor[0]);
  int leitEsqM = digitalRead(sensor[1]);
  int leitMeio = digitalRead(sensor[2]);
  int leitDirM = digitalRead(sensor[3]);
  int leitDirP = digitalRead(sensor[4]);

    if (leitEsqP == 1 && leitEsqM == 1 && leitMeio == 1 && leitDirM && leitDirP) {
      if (!contagem) {
        contagem = true;
        tempoo = millis(); 
      } 
      else {
        if (millis() - tempoo >= 3000) {
          estado = 1;  // Troca estado no switch-case
        }
      }
    } else {
      contagem = false; // Resetar contagem se sair do branco
    }

  // Switch-case para estados
  static int estado = 0;
  switch (estado) {
    case 0b00000:           //tudo preto
    case 0b11110:           //direita ponta
    case 0b11101:           //direita meio
    case 0b11100:           //direita meio; direita ponta
    case 0b11000:           //meio; direita meio; direita ponta
    case 0b11011:           //meio
    case 0b00011:           // esquerda ponta; esquerda meio; meio
    case 0b00111:           //esquerda meio; esquerda ponta
    case 0b10111:           //esquerda meio
    case 0b01111:           //esquerda ponta
    case 0b01110:           //esquerda ponta; direita ponta
    case 0b10101:           //esquerda meio; direita meio
    case 0b00101:           //esquerda ponta; esquerda meio; direita meio
    case 0b10100:           //esquerda meio; direita meio; direita ponta
    case 0b01100:           //esquerda ponta; direita meio; direita ponta
    case 0b00110:           //esquerda ponta; esquerda meio; direita ponta
      break;

    case 0b11111:
      saladeresgate();
      estado = 0;
      break;
  }
}
