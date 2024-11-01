
int sensor[] = {A1, A0, A4, A2, A3};
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
  Serial.print(" sensor1 = ");
  Serial.println(analogRead(sensor[0]));
  Serial.print(" sensor2 = ");
  Serial.print(analogRead(sensor[1]));
  Serial.print(" sensor3 = ");
  Serial.print(analogRead(sensor[2]));
  Serial.print(" sensor4 = ");
  Serial.print(analogRead(sensor[3]));
  Serial.print(" sensor5 = ");
  Serial.print(analogRead(sensor[4]));
}
