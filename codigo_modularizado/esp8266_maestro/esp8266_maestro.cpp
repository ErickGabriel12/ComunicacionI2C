#include <Wire.h>
#include <Arduino.h>
#include "esp8266_maestro.h"

// -------------------- CONFIGURACIÓN --------------------
#define SDA_PIN = 0;          // D3 = GPIO0
#define SCL_PIN = 2;          // D4 = GPIO2
#define SLAVE_ADDRESS = 8;    // Dirección I2C del Arduino
#define  MAX_BYTES = 32;       // Tamaño máximo de mensaje
const unsigned long SERIAL_BAUDRATE = 9600;  // Velocidad del puerto serial
const unsigned long LECTURA_DELAY = 2000;    // Tiempo entre lecturas

// -------------------- FUNCIONES --------------------
void esp8266_maestro_init() {
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(SERIAL_BAUDRATE);
  delay(100);
  Serial.println("ESP8266 Maestro I2C listo para recibir datos");
}

void esp8266_maestro_leer() {
  Wire.requestFrom(SLAVE_ADDRESS, MAX_BYTES);

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

  delay(LECTURA_DELAY);
}
