#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Hello ESP32C3!!");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}