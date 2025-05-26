#include <Wire.h>
#include <DHT.h>

// -------------------- CONFIGURACIÓN --------------------
#define SLAVE_ADDRESS 8
#define DHTPIN 2
#define DHTTYPE DHT11
const int mq2Pin = A0;
const int umbralGas = 150;
const float umbralTemp = 30.0;

DHT dht(DHTPIN, DHTTYPE);

float temperatura = 0.0;
float humedad = 0.0;
int lecturaMQ2 = 0;
String datosSensor = "Sin datos";
String alerta = "";


void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(enviarDatos);
  dht.begin();

  Serial.println("Esclavo I2C con sensores DHT11 + MQ2 iniciado");
}


void loop() {
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  lecturaMQ2 = analogRead(mq2Pin);

  alerta = "";  // reiniciar alerta

  if (isnan(temperatura) || isnan(humedad)) {
    datosSensor = "Error sensores";
  } else {
    // verificar alertas
    if (temperatura > umbralTemp) {
      alerta += " Alta Temp ";
    }

    if (lecturaMQ2 > umbralGas) {
      alerta += " Gas ";
    }

    // construir mensaje final
    datosSensor = "T:" + String(temperatura, 1) + "C ";
    datosSensor += "H:" + String(humedad, 1) + "% ";
    datosSensor += "MQ2:" + String(lecturaMQ2);

    // si hay alerta, agregarla
    if (alerta.length() > 0) {
      datosSensor += " | " + alerta;
    }
  }

  Serial.println("Mensaje generado: " + datosSensor);
  delay(2000);
}

// -------------------- ENVÍO I2C --------------------
void enviarDatos() {
  String msg = datosSensor.substring(0, 31);  // evitar desbordar el buffer
  Wire.write(msg.c_str());
}
