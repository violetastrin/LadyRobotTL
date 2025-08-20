//TESTE DOS SENSORES DE VERDE

#define core  A9
#define cord  A8 

int direitaverde = 0 ;
int esquerdaverde = 0;

void setup() {
Serial.begin(9600);
}

void loop() {
 /*if (analogRead(core) >= ) {
    esquerdaverde = 1;
  } else {
    esquerdaverde = 0;
  }


  if (analogRead(cord) >= 1) {
    direitaverde = 1;
  } else {
    diretaverde = 0;
  }*/

  
char texto[50];

direitaverde = analogRead(cord);
esquerdaverde = analogRead(core);

  // Usando sprintf() para formatar a string
sprintf(texto, "Direita verde = %d, esquerda verde = %d", direitaverde, esquerdaverde);
  // Imprime a string formatada no monitor serial
Serial.println(texto);

}
