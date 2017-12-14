#define BLYNK_PRINT Serial

#include "ESP8266WiFi.h"
#include "BlynkSimpleEsp8266.h"
#include "Adafruit_Si7021.h"

char auth[] = "";

char ssid[] = "";
char pass[] = "";

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");
  
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true);
  }
}

void loop() {
  Serial.print("Humidity:    "); Serial.print(sensor.readHumidity(), 2);
  Serial.print("\tTemperature: "); Serial.println(sensor.readTemperature(), 2);
  delay(1000);
}
