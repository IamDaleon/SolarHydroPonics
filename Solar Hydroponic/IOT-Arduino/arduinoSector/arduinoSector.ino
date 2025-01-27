#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <WiFi.h>  // WiFi library for Arduino
#include "wifi_credentials.h"

// Define the SPI pins
#define BME_CS 13 // Chip select
#define BME_MOSI A1 // MOSI (SDI)
#define BME_MISO 2  // MISO (SDO)
#define BME_SCK A0  // Clock (SCK)

// Create BME680 object for SPI
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

// Raspberry Pi Server URL (replace with your Raspberry Pi IP or domain)
const char* serverName = "http://192.168.0.153/rpc";  // Change to your Raspberry Pi IP or hostname

// Pin connected to fan (5V fan)
const int fanPin = 9;

// Variable to store the last pressure reading
float lastPressure = 0.0;

void setup() {
  Serial.begin(115200); // Start Serial Monitor at 115200 baud
  while (!Serial); // Wait for Serial Monitor to open

  // Initialize the BME680
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320°C for 150 ms

  // Initialize fan pin as OUTPUT
  pinMode(fanPin, OUTPUT);

  // Connect to Wi-Fi
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to SSID: ");
  Serial.println(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.println();
}

void loop() {
  // Perform a reading
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  // Get CPU temperature (using mock function here)
  float cpuTempC = (analogRead(A2) / 1023.0) * 100.0;
  float cpuTempF = (cpuTempC * 9.0 / 5.0) + 32;

  // Get sensor data
  float sensorTempC = bme.temperature;
  float sensorTempF = (sensorTempC * 9.0 / 5.0) + 32;
  float sensorHumidity = bme.humidity;
  float sensorPressure = bme.pressure / 100.0;
  float sensorGasKOhms = bme.gas_resistance / 1000.0;

  // Calculate additional metrics
  float dewPointC = calculateDewPoint(sensorTempC, sensorHumidity);
  float dewPointF = dewPointC * 9.0 / 5.0 + 32;
  float heatIndexC = calculateHeatIndex(sensorTempC, sensorHumidity);
  float heatIndexF = heatIndexC * 9.0 / 5.0 + 32;
  
  Serial.print("CPU Temps: ");
  Serial.print(cpuTempF);
  Serial.print(" °F | ");
  Serial.print(cpuTempC);
  Serial.println(" °C");
  
  // Print sensor and calculated data
  Serial.print("Sensor Temperature = ");
  Serial.print(sensorTempF);
  Serial.print(" °F ");
  Serial.print(sensorTempC);
  Serial.println(" °C ");
  Serial.print("Humidity = ");
  Serial.print(sensorHumidity);
  Serial.println(" % ");
  Serial.print("Pressure = ");
  Serial.print(sensorPressure);
  Serial.println(" hPa ");

  Serial.print("Dew Point = ");
  Serial.print(dewPointF);
  Serial.print(" °F | ");
  Serial.print(dewPointC);
  Serial.println(" °C");

  Serial.print("Heat Index = ");
  Serial.print(heatIndexF);
  Serial.print(" °F | ");
  Serial.print(heatIndexC);
  Serial.println(" °C");
  
  

  detectWeatherTrend(sensorPressure);

  // Prepare and send the JSON payload
  String payload = "{";
  payload += "\"cpuTempC\":" + String(cpuTempC) + ",";
  payload += "\"cpuTempF\":" + String(cpuTempF) + ",";
  payload += "\"sensorTempC\":" + String(sensorTempC) + ",";
  payload += "\"sensorTempF\":" + String(sensorTempF) + ",";
  payload += "\"sensorHumidity\":" + String(sensorHumidity) + ",";
  payload += "\"sensorPressure\":" + String(sensorPressure) + ",";
  payload += "\"sensorGasKOhms\":" + String(sensorGasKOhms) + ",";
  payload += "\"dewPointC\":" + String(dewPointC) + ",";
  payload += "\"dewPointF\":" + String(dewPointF) + ",";
  payload += "\"heatIndexC\":" + String(heatIndexC) + ",";
  payload += "\"heatIndexF\":" + String(heatIndexF);
  payload += "}";

  WiFiClient client;
  if (client.connect(serverName, 80)) {
    Serial.println("Connected to server");

    client.println("POST /sensor_data HTTP/1.1");
    client.println("Host: 192.168.0.153"); // Replace with your Raspberry Pi IP
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(payload.length());
    client.println();
    client.println(payload);

    while (client.connected() || client.available()) {
      String line = client.readStringUntil('\n');
      Serial.print(line);
    }
    client.stop();
  } else {
    Serial.println("Connection to server failed");
    Serial.println();
  }

  delay(2000); // Wait 2 seconds before the next reading
}

// Calculate Dew Point
float calculateDewPoint(float tempC, float humidity) {
  return tempC - ((100 - humidity) / 5.0);
}

// Calculate Heat Index
float calculateHeatIndex(float tempC, float humidity) {
  float e = 6.112 * exp((17.67 * tempC) / (tempC + 243.5)) * (humidity / 100.0);
  return tempC + (0.5555 * (e - 10.0));
}

// Detect weather trends based on pressure
void detectWeatherTrend(float currentPressure) {
  if (lastPressure == 0.0) {
    lastPressure = currentPressure; // Initialize first reading
    return;
  }

  if (currentPressure > lastPressure) {
    Serial.println("Weather Trend: Improving (Rising Pressure)");
  } else if (currentPressure < lastPressure) {
    Serial.println("Weather Trend: Deteriorating (Falling Pressure)");
  } else {
    Serial.println("Weather Trend: Stable");
  }

  lastPressure = currentPressure; // Update last pressure
}
