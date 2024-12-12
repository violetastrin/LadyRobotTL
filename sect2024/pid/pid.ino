#include "base.h"

void setup() {
  Serial.begin(9600);

  display.begin();
 
  display.setFontSize(FONT_SIZE_LARGE);

  servoDir_f.attach(12);
  servoDir_t.attach(11);
  servoEsq_f.attach(7);
  servoEsq_t.attach(6);



//  if (tcs_soft.begin(&sWire)) {
//   if (tcs_soft.begin(&sWire)) {
//     Serial.println("Found sensor soft");
//   } else {
//     display.println("No TCS soft found");
//     Serial.println("No TCS34725 found ... check your connections (soft)");
//     while (1)
//       ;
//   }

//   if (tcs_real.begin(&Wire)) {
//     Serial.println("Found sensor real");
//   } else {
//     display.println("No TCS real found");
//     Serial.println("No TCS34725 found ... check your connections (real)");
//     while (1)
//       ;
//   }
// }
}
void loop() {

  leiturainfra();

  distancia = ultrasonic.read();

  display.clearLine(0);
  display.setCursor(0, 0);

  leiturainfra();

   if (distancia <= 4 && distancia > 0) {  //--------- distancia do desvia obstaculo
    Serial.println("desviando");
    display.clear();
    display.setCursor(0, 0);
    display.setFontSize(FONT_SIZE_LARGE);
    display.println("desvia");
    desviaesq();
  }

  if (sensorMap[0] <= media[0]) {
    valorSensor[0] = 0;
  } else {
    valorSensor[0] = 1;
  }

  if (sensorMap[1] <= media[1]) {
    valorSensor[1] = 0;
  } else {
    valorSensor[1] = 1;
  }

  if (sensorMap[2] <= media[2]) {
    valorSensor[2] = 0;
  } else {
    valorSensor[2] = 1;
  }

  byte leitura = 0;
  for (int i = 0; i < 3; i++) {
    leitura |= valorSensor[i] << (2 - i);
  }

  Serial.print(leitura, BIN);
  display.println(leitura,BIN);

  switch (leitura) {
    case 0b011:
      novgrausEsquerda();
      break;
    case 0b101:
      pid();
      break;
    case 0b110:
      novgrausDireita();
      break;
    case 0b111:
      frente();
      break;

    default:
      frente();
      break;
  }
}


// funções de ladrilhos
void novgrausDireita() {  //90º direita
  display.println("90 graus - d");

  Serial.println("90 direita");

  frente();
  delay(150);

  while (analogRead(sensor[2]) >= 300) {
    leiturainfra();
    devagarDireita();
  }
}

void novgrausEsquerda() {  // 90º esquerda
  display.println("90 graus - e");

  Serial.println("90 esquerda");
  frente();
  delay(150);
while (analogRead(sensor[2]) >= 300) {
    devagarEsquerda();
    leiturainfra();
  }
}

void pid(){
    kp = 0.2;
    kd = 0.5;

    int leituraDireita = (analogRead(A0)); 
    int leituraEsquerda = (analogRead(A1)); 

    int err = leituraEsquerda - (leituraDireita);  // erro positivo -> robo a direita
    int d = err - error_passado;

    float pwme = 90 + vbase + err * kp + d * kd;
    float pwmd = 90 - vbase + err * kp + d * kd;


    servoDir_f.write(pwmd);
    servoDir_t.write(pwmd);

    servoEsq_f.write(pwme);
    servoEsq_t.write(pwme);


    error_passado = err;

  display.clear();
  display.setCursor(0, 0);
  display.setFontSize(FONT_SIZE_LARGE);
  display.println("reajuste pid");

    Serial.print(pwme);
    Serial.print(" / ");
    Serial.println(pwmd); 
    Serial.println(err);
}