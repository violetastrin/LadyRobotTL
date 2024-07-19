#include <SoftwareWire.h>
#include <Wire.h>
#include <Adafruit_TCS34725_SWwire.h>

SoftwareWire sWire(A2, A3);

Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_499MS, TCS34725_GAIN_60X);
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_499MS, TCS34725_GAIN_60X);

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

  Serial.print("ESQ (soft): ");
  Serial.print("Vermelho: "); Serial.print(r2);
  Serial.print(", Verde: "); Serial.print(g2);
  Serial.print(", Azul: "); Serial.print(b2);
  Serial.print(", Claro: "); Serial.print(c2);

  Serial.print(" | DIR (real): ");
  Serial.print("Vermelho: "); Serial.print(r1);
  Serial.print(", Verde: "); Serial.print(g1);
  Serial.print(", Azul: "); Serial.print(b1);
  Serial.print(", Claro: "); Serial.println(c1);


  uint16_t medgeral1  = (r1+g1+b1)/3;
  uint16_t medgb1 = (g1+b1)/2;
  uint16_t medrb1 = (r1+b1)/2;

  uint16_t medgeral2  = (r2+g2+b2)/3;
  uint16_t medgb2 = (g2+b2)/2;
  uint16_t medrb2 = (r2+b2)/2;

  Serial.print("direita(real): ");
  if(r1 > medgb1)
    Serial.print("vermelho");
  else if(g1 > medrb1)
    Serial.print("verde");
  else {
    if(c1 >= 11500) //1050
      Serial.print("branco");
    else 
      Serial.print("preto");
  }

  Serial.print(" / ");

  Serial.print("esquerda(soft): ");
  if(r2 > medgb2)
    Serial.print("vermelho");
  else if(g2 > medrb2)
    Serial.print("verde");
  else {
    if(medgeral2 >= 11500) //1050
      Serial.print("branco");
    else 
      Serial.print("preto");
  }

  Serial.println("");




}
