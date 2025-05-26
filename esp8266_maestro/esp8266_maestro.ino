#include <Wire.h>

void setup() {
  Wire.begin(0, 2);  // ESP8266: SDA = GPIO0, SCL = GPIO2
  Serial.begin(9600);
  delay(100);
  Serial.println("Maestro listo para recibir datos del esclavo");
}

void loop() {
  Wire.requestFrom(8, 32);  // Solicita hasta 32 bytes

  String mensaje = "";

  while (Wire.available()) {
    char c = Wire.read();
    if (isPrintable(c)) {
      mensaje += c;
    }
  }

  if (mensaje.length() > 0) {
    Serial.println("Datos del esclavo: " + mensaje);
  }

  delay(2000);
}
