int sensor[] = {A2, A1, A4, A0, A3};
// ORDEM: ESQUERDA, REAJUSTE ESQUERDA, FRENTE, REAJUSTE DIREITA, DIREITA

void setup() {

  Serial.begin(9600);                    // Inicial Serial em 9600 Baud Rate.
  Serial.println("Serial Trabalhando");  // Teste para verificar se serial está funcionando ou não

for(int i = 0; i>5; i++){
  pinMode(sensor[i], INPUT);
}
}

void loop() {
  //-----------------------------------------Testando os Sensores--------------------------------------------------------
  Serial.print(" sensorESQ = ");
  Serial.println(analogRead(sensor[0]));
  Serial.print(" sensorRE = ");
  Serial.print(analogRead(sensor[1]));
  Serial.print(" sensorMEIO = ");
  Serial.print(analogRead(sensor[2]));
  Serial.print(" sensorRD = ");
  Serial.print(analogRead(sensor[3]));
  Serial.print(" sensorDIR = ");
  Serial.print(analogRead(sensor[4]));
}
