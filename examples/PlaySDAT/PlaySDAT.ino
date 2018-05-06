#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif


#include <AudioOutputI2S.h>
#include <AudioGeneratorNDS.h>
#include <AudioFileSourcePROGMEM.h>

#include "sdat.h"

AudioGeneratorNDS *nds;
AudioFileSourcePROGMEM *sdat;
AudioOutputI2S *dac;
int song=0;

void setup()
{
  WiFi.mode(WIFI_OFF); 

  Serial.begin(115200);
  Serial.println("Starting up...\n");

  sdat = new AudioFileSourcePROGMEM(sdatFile, sizeof(sdatFile));
  dac = new AudioOutputI2S();
  nds = new AudioGeneratorNDS();
  Serial.printf("BEGIN...\n");
  nds->begin(sdat, dac, song);
}

void loop()
{
  if (nds->isRunning()) {
    if (!nds->loop()) {
      uint32_t e = millis();
      nds->stop();
    }
  } else {
    song++;
    nds->begin(sdat, dac, song);
    Serial.println(song);
    delay(1000);
  }
}

