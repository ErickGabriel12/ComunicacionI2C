# 🛰️ Comunicación I2C entre ESP8266 y Arduino Uno con sensores

## 👥 Integrantes del grupo

- Erick Gabriel Alarcon Albornoz
- Mariana Rios
- Dacar Tirado

Este proyecto muestra cómo implementar una comunicación **I2C maestro-esclavo** donde un **ESP8266** actúa como maestro y un **Arduino Uno** como esclavo. El Arduino tiene conectados dos sensores:

- 🌡️ **DHT11** para temperatura y humedad
- 🔥 **MQ2** para detección de gases

Los datos son leídos por el Arduino y enviados al ESP8266 de manera continua.

---

## ⚙️ Componentes utilizados

- ESP8266 
- Arduino Uno
- Sensor DHT11
- Sensor de gas MQ2
- Jumpers y protoboard

---

## 📡 Conexiones I2C

| Maestro (ESP8266) | Esclavo (Arduino Uno) |
|-------------------|------------------------|
| GPIO0 (D3 - SDA)  | A4 (SDA)               |
| GPIO2 (D4 - SCL)  | A5 (SCL)               |
| GND               | GND                    |

Ambos dispositivos deben compartir la misma tierra (**GND**).

---

## 🔁 Funcionamiento

1. El Arduino mide temperatura, humedad y gas.
2. El ESP8266 recibe los datos vía I2C.
3. El Arduino responde con los valores formateados (o alerta si hay gas o alta temperatura).

---

## 📂 Archivos

- `esp8266_maestro/esp8266_maestro.ino`: Código del ESP8266 (maestro)
- `arduino_esclavo/arduino_esclavo.ino`: Código del Arduino (esclavo)
- `docs/conexion_i2c_diagrama.png`: Imagen de las conexiones 

---
