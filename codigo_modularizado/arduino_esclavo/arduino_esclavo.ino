#include <Wire.h>
#include "arduino_esclavo.h"

void setup() {
  iniciarEsclavo();
}

void loop() {
  actualizarSensores();
 
}
