//ORDEM: ESQUERDA, REAJUSTE ESQUERDA, FRENTE, REAJUSTE DIREITA, DIREITA

const int sensor[] = {A1, A0, A4, A2, A3};

const int valorPreto[] = {550, 320, 210, 445, 570};

const int valorBranco[] = {984, 982, 988, 986, 988};

const int media[] = {50, 50, 50, 50, 50};

int leituraSensor[5] = {};

int sensorMap[5] = {};

bool valorSensor[5] = {};

void setup() {
  Serial.begin(9600);
}

void loop() {

for(int i = 0; i<5; i++){
  leituraSensor[i] = analogRead(sensor[i]);
  }

for (int i = 0; i<5; i++){
  sensorMap[i] = map(leituraSensor[i], valorPreto[i], valorBranco[i], 0, 100);
  sensorMap[i] = constrain(sensorMap[i], 0, 100);
}

// for (int i = 0; i<5; i++){
//   Serial.print(leituraSensor[i]);
//   Serial.print(" /// ");
//   Serial.print(sensorMap[i]);
//   Serial.print(" /// "); 
//}
  //Serial.println();

  if (sensorMap[0] <= media[0] ){valorSensor[0] = 0;} else{valorSensor[0] = 1;}

  if (sensorMap[1] <= media[1] ){valorSensor[1] = 0;} else {valorSensor[1] = 1;}
    
  if (sensorMap[2] <= media[2] ){valorSensor[2] = 0;} else {valorSensor[2] = 1;}
    
  if (sensorMap[3] <= media[3] ){valorSensor[3] = 0;} else {valorSensor[3] = 1;}
    
  if (sensorMap[4] <= media[4] ){valorSensor[4] = 0;} else {valorSensor[4] = 1;}

// for (int i = 0; i<5; i++){
//  Serial.print(valorSensor[i]);
// Serial.print(" /// "); 
// }
// Serial.println();

byte leitura = 0;
  for(int i =  0; i<5; i++){
  leitura |= valorSensor[i] << (4-i);
  }

Serial.print("Valor lido: ");
Serial.println(leitura, BIN);

}
