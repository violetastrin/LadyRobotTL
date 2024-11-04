//ORDEM: ESQUERDA, REAJUSTE ESQUERDA, FRENTE, REAJUSTE DIREITA, DIREITA

const int sensor[] = {A1, A0, A4, A2, A3};

const int valorPreto[] = {325, 184, 450, 445, 434};

const int valorBranco[] = {984, 982, 988, 986, 988};

int valorSensor[] = {0, 0, 0, 0, 0};

int sensorMap[] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
}

void loop() {

for(int i = 0; i<5; i++){
  valorSensor[i] = analogRead(sensor[i]);
  }

for (int i = 0; i<5; i++){
  sensorMap[i] = map(valorSensor[i], valorPreto[i], valorBranco[i], 0, 100);
  sensorMap[i] = constrain(sensorMap[i], 0, 100);
}

for (int i = 0; i<5; i++){
  Serial.print(valorSensor[i]);
  Serial.print(" /// ");
  Serial.print(sensorMap[i]);
  Serial.print(" /// "); 
}
  Serial.println();

}
