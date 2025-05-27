#include <Wire.h>
#include <DHT.h>
#include "arduino_esclavo.h"

void enviarDatosAlMaestro();  // Declaración anticipada

// -------------------- CONFIGURACIÓN --------------------
#define I2C_SLAVE_ADDRESS 8
#define DHT_PIN 2
#define DHT_TYPE DHT11
#define MQ2_PIN A0

const int UMBRAL_GAS = 150;
const float UMBRAL_TEMP = 30.0;
const unsigned long SERIAL_BAUDRATE = 9600;  // Velocidad del puerto serial
const unsigned long LECTURA_DELAY = 2000;    // Tiempo entre lecturas

DHT dht(DHT_PIN, DHT_TYPE);

float temperatura = 0.0;
float humedad = 0.0;
int lecturaMQ2 = 0;
String mensajeParaMaestro = "Sin datos";

// -------------------- SETUP --------------------
void iniciarEsclavo() {
  Serial.begin(SERIAL_BAUDRATE);
  dht.begin();
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(enviarDatosAlMaestro);
  Serial.println("Arduino esclavo I2C con sensores listo.");
}

// -------------------- LOOP --------------------
void actualizarSensores() {
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  lecturaMQ2 = analogRead(MQ2_PIN);

  // Mostrar SIEMPRE los valores en el Monitor Serial
  Serial.print("Temp: ");
  Serial.print(temperatura);
  Serial.print(" °C | Humedad: ");
  Serial.print(humedad);
  Serial.print(" % | MQ2: ");
  Serial.println(lecturaMQ2);

  if (isnan(temperatura) || isnan(humedad)) {
    mensajeParaMaestro = "Error sensores";
    return;
  }

  // Verificación de umbrales
  bool alertaTemperatura = temperatura > UMBRAL_TEMP;
  bool alertaGas = lecturaMQ2 > UMBRAL_GAS;

  if (alertaTemperatura || alertaGas) {
 mensajeParaMaestro = "PELIGRO: ";
mensajeParaMaestro += "T:";
mensajeParaMaestro += String(temperatura, 1);
mensajeParaMaestro += "C H:";
mensajeParaMaestro += String(humedad, 1);
mensajeParaMaestro += "% MQ2:";
mensajeParaMaestro += String(lecturaMQ2);
  } else {
    mensajeParaMaestro = "Valores ambientales normales";
  }

  Serial.println("Mensaje al maestro: " + mensajeParaMaestro);
   delay(LECTURA_DELAY);
}

// -------------------- RESPUESTA I2C --------------------
void enviarDatosAlMaestro() {
  String respuesta = mensajeParaMaestro.substring(0, 31);  // por límite I2C
  Wire.write(respuesta.c_str());
}
