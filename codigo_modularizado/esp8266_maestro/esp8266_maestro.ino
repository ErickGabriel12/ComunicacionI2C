#include <Wire.h>
#include "esp8266_maestro.h"

void setup() {
  esp8266_maestro_init();
}

void loop() {
  esp8266_maestro_leer();
}
