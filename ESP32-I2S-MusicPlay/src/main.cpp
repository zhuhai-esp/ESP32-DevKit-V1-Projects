#include "Audio.h"
#include <Arduino.h>
#include <WiFi.h>

#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC 26

long check300ms = 0;
uint8_t ledOn = 0;
Audio audio;

void inline autoConfigWifi() {
  Serial.println("Start WiFi Connect!");
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin();
  for (int i = 0; WiFi.status() != WL_CONNECTED && i < 100; i++) {
    delay(100);
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.beginSmartConfig();
    Serial.println("Config WiFi with ESPTouch App!");
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
    WiFi.stopSmartConfig();
    WiFi.mode(WIFI_MODE_STA);
  }
  Serial.printf("WiFi Connected: %s\n", WiFi.localIP().toString().c_str());
}

void inline initAudioDevice() {
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(20);
  audio.connecttohost("http://ting8.yymp3.com/new18/murongxx2/5.mp3");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello ESP32!!");
  pinMode(LED_BUILTIN, OUTPUT);
  autoConfigWifi();
  initAudioDevice();
}

void loop() {
  audio.loop();
  auto ms = millis();
  if (ms - check300ms > 300) {
    check300ms = ms;
    ledOn = !ledOn;
    digitalWrite(LED_BUILTIN, ledOn);
  }
}