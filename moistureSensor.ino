#include "DHT.h"
#include <stdio.h>

#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int GLED= 13; // Wet Indicator at Digital PIN D13
int RLED= 12; // Dry Indicator at Digital PIN D12
int SENSE= 0; // Soil Sensor input at Analog PIN A0
int value= 0;
void setup() {
  Serial.begin(9600);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  dht.begin();
}

const char * printData(int h, int f, int value) {
  char str[100];
  sprintf(str, "{'humidity': %d, 'temperature': %d, 'moisture': %d}", h, f, value);
  Serial.println(str);
  return 0;
}

void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  value = analogRead(SENSE);
  value = value/10;

  const char* values = printData(h,f,value);
  values;

  if(value<50)
  {
    digitalWrite(GLED, HIGH);
  }
  else
  {
    digitalWrite(RLED,HIGH);
  }
  delay(1000);
  digitalWrite(GLED,LOW);
  digitalWrite(RLED, LOW);
}
