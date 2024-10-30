#define sensor1 A1           // direita
#define sensor2 A2          // r dir queimado capenga 
#define sensor3 A3          //r esq 
#define sensor4 A4          // frente
#define sensor5 A0           // esquerda

void setup() {

  Serial.begin(9600);                    // Inicial Serial em 9600 Baud Rate.
  Serial.println("Serial Trabalhando");  // Teste para verificar se serial está funcionando ou não

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
}

void loop() {
  //-----------------------------------------Testando os Sensores--------------------------------------------------------
  Serial.print(" sensor1 = ");
  Serial.println(analogRead(sensor5));
  Serial.print(" sensor2 = ");
  Serial.print(analogRead(sensor1));
  Serial.print(" sensor3 = ");
  Serial.print(analogRead(sensor2));
  Serial.print(" sensor4 = ");
  Serial.print(analogRead(sensor4));
  Serial.print(" sensor5 = ");
  Serial.print(analogRead(sensor3));
}
