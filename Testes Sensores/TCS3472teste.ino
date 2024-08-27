#include <SoftwareWire.h>
#include <Wire.h>
#include <Adafruit_TCS34725_SWwire.h>

SoftwareWire sWire(A6, A7);

Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_16X);
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_16X);


bool dvermelho;
bool evermelho;
bool dcinza;
bool ecinza;


void setup(void) { 
  Serial.begin(9600);

  if (tcs_soft.begin(&sWire)) {
    Serial.println("Found sensor soft");
  } else {
    Serial.println("No TCS34725 found ... check your connections (soft)");
    while (1);
  }

  if (tcs_real.begin(&Wire)) {
    Serial.println("Found sensor real");
  } else {
    Serial.println("No TCS34725 found ... check your connections (real)");
    while (1);
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r1, g1, b1, c1;
  uint16_t r2, g2, b2, c2;

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  uint16_t t1  = (r1+g1+b1)/3;
  uint16_t tr1 = (g1+b1)/2;
  uint16_t tg1 = (r1+b1)/2;

  uint16_t t2  = (r2+g2+b2)/3;
  uint16_t tr2 = (g2+b2)/2;
  uint16_t tg2 = (r2+b2)/2;

  uint16_t medrbg1 = (r1 + b1 + g1) / 3;
  uint16_t medrbg2 = (r2 + b2 + g2) / 3;

  uint16_t med1 = medrbg1 * 1.05;
  uint16_t med2 = medrbg2 * 1.045;


  if (r1 > 4300 && c1 < 16000) {
    dvermelho = 1;
    //Serial.println("vermelho direita");
  } else {
    dvermelho = 0;
    //Serial.println("                              branco direita");
  }

  if (r2 > medrbg2) {
    evermelho = 1;
    //Serial.println("vermelho esquerda");
  } else {
    evermelho = 0;
    //Serial.println("branco esquerda");
  }
  // ---------------------------------------------------------------------
  if (medrbg1 <= 6800 && c1 > medrbg1) {  // ESQ (soft): Vermelho: 5359, Verde: 6707, Azul: 7441, Claro: 19596 | DIR (real): Vermelho: 4126, Verde: 5991, Azul: 7038, Claro: 16439
    dcinza = 1;
    Serial.println("cinza direita"); // ESQ (soft): Vermelho: 6780, Verde: 8229, Azul: 8984, Claro: 23597 | DIR (real): Vermelho: 6163, Verde: 8526, Azul: 9827, Claro: 23062
  } else {
    dcinza = 0;
    Serial.println("branco direita");
  }


  if (medrbg2 <= 6100 && c2 > medrbg2) {
    ecinza = 1;
    Serial.println("cinza esquerda");
  } else {
    ecinza = 0;
    Serial.println("branco esquerda");
  }


  Serial.print("ESQ (soft): ");
  Serial.print("Vermelho: "); Serial.print(r2);
  Serial.print(", Verde: "); Serial.print(g2);
  Serial.print(", Azul: "); Serial.print(b2);
  Serial.print(", Claro: "); Serial.println(c2);
  Serial.print("Media esq: ");
  Serial.println(medrbg2);

  Serial.print("DIR (real): ");
  Serial.print("Vermelho: "); Serial.print(r1);
  Serial.print(", Verde: "); Serial.print(g1);
  Serial.print(", Azul: "); Serial.print(b1);
  Serial.print(", Claro: "); Serial.println(c1);
  Serial.print("Media dir: ");
  Serial.println(medrbg1);

}
