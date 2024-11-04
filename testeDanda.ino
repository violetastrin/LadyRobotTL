int valorMap;
int sensor[] = {A1, A0, A4, A2, A3};

int valorPreto[] = {325, 184, 450, 445, 434};

int valorBranco[] = {984, 982, 988, 986, 988};

int valorSensor[] = {0, 0, 0, 0, 0};

int sensorMap[] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
}

void loop() {

  valorSensor[0] = analogRead(sensor[0]);
  valorSensor[1] = analogRead(sensor[1]);
  valorSensor[2] = analogRead(sensor[2]);
  valorSensor[3] = analogRead(sensor[3]);
  valorSensor[4] = analogRead(sensor[4]);


sensorMap[0] = map(valorSensor[0], valorPreto[0], valorBranco[0], 0, 100);
sensorMap[0] = constrain(sensorMap[0], 0, 100);

sensorMap[1] = map(valorSensor[1], valorPreto[1], valorBranco[1], 0, 100);
sensorMap[1] = constrain(sensorMap[1], 0, 100);

sensorMap[2] = map(valorSensor[2], valorPreto[2], valorBranco[2], 0, 100);
sensorMap[2] = constrain(sensorMap[2], 0, 100);

sensorMap[3] = map(valorSensor[3], valorPreto[3], valorBranco[3], 0, 100);
sensorMap[3] = constrain(sensorMap[3], 0, 100);

sensorMap[4] = map(valorSensor[4], valorPreto[4], valorBranco[4], 0, 100);
sensorMap[4] = constrain(sensorMap[4], 0, 100);

  Serial.print(valorSensor[0]);
  Serial.print(" /// ");
  Serial.print(sensorMap[0]);
  Serial.print(" /// "); 

  Serial.print(valorSensor[1]);
    Serial.print(" /// ");
  Serial.print(sensorMap[1]);
  Serial.print(" /// ");

  Serial.print(valorSensor[2]);
    Serial.print(" /// ");
  Serial.print(sensorMap[2]);
  Serial.print(" /// ");

  Serial.print(valorSensor[3]);
  Serial.print(" /// ");
  Serial.print(sensorMap[3]);
  Serial.print(" /// ");

  Serial.print(valorSensor[4]);
  Serial.print(" /// ");
  Serial.print(sensorMap[4]);
  Serial.println();

}

