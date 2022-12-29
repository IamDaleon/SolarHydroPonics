/*
  DHT-11 Sensor
 */
#include "DHT.h"

#define DHTPIN 51     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

/*
  GAS Sensor
 */
int airquality;     //Gas Sensor

/*
  Ultrasonic Sensor HC-SR04
 */
int trigPin = 53;    // Trigger
int echoPin = 52;    // Echo
long duration, cm, inches, volume;
const int length = 23.5;
const int width = 14.5;
/*
DC Voltmeter Using a Voltage Divider
*/
float solarout, ccout, battout = 0.0;
float solar, chargecontroller, battery = 0.0;
float R1 = 30000.0; //  
float R2 = 7500.0; // 
int solarValue, cCValue, batteryValue = 0;

/*
  16 Channel Relay Module
 */
const int controlPin[16] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37}; // define pins
const int triggerType = LOW;    // your relay type

const int fan = controlPin[0];

//Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("DHT-11 | Gas Detector | 16-Channel Relay | Water level Detector");
  Serial.println("Solar Voltmeter | Charge Controller Voltmeter | Battery Voltmeter");
  Serial.println("------------------------- Initalized -------------------------- ");
  
  dht.begin();
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  //16 Channel Relay
  for(int i=0; i<16; i++)
  {
    pinMode(controlPin[i], OUTPUT);// set pin as output
    if(triggerType ==LOW){
      digitalWrite(controlPin[i], HIGH); // set initial state OFF for low trigger relay
    }else{
       digitalWrite(controlPin[i], LOW); // set initial state OFF for high trigger relay     
    }
  }
}

void loop() {
  solarValue = analogRead(A0);
  cCValue = analogRead(A1);
  batteryValue = analogRead(A2);
  airquality = analogRead(A15);
   
   
   solarout = (solarValue * 5.0) / 1024.0; // see text
   ccout = (cCValue * 5.0) / 1024.0;
   battout = (batteryValue * 5.0) / 1024.0;
   
   solar = solarout / (R2/(R1+R2));
   chargecontroller = ccout / (R2/(R1+R2));
   battery = battout / (R2/(R1+R2)); 
   
  Serial.print("Solar V= ");
  Serial.print(solar,2);
  Serial.print(" | Charge Controller V= ");
  Serial.print(chargecontroller,2);
  Serial.print(" | Battery V= ");
  Serial.println(battery,2);
  
  delay(5000);
     if(airquality > 240 && airquality < 350 ){
      Serial.println("Failed to read from Air Quality Sensor!"); 
      delay(1000);
      };
      if(airquality > 130 && airquality < 230){
      Serial.println("AirQuality has been compromised");
      Serial.println("Fan initalized | ");
      Serial.println("5min to stabilize the Air Quality");
      digitalWrite(fan, LOW); // set initial state OFF for low trigger relay
      delay(3500);                    // wait 6mins for next reading
      digitalWrite(fan, HIGH); // set initial state OFF for high trigger relay                           
     };
   if(airquality < 130){
    Serial.println("AirQuality is Good!");
   };

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  //Dew Point
  int dp = f-((100-h)/5);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Temperature: ");
  Serial.print(f);
  Serial.print(" *F | ");
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" % | ");
 
  Serial.print("Heat index: ");
  Serial.print(hif);
  Serial.print(" *F | ");

  Serial.print("Dew Point: ");
  Serial.print(dp);
  Serial.println(" *F");
  delay(1000);
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  volume = (inches * width * length)/100; //Multiple Length * Width * Height = Volume

  if (volume >= 90){
    Serial.println("Tank is empty | Please Refill \n");
    }
  else if (volume < 90 && volume >= 70){
    Serial.println("Tank is on Reserve \n");
    }
  else if (volume < 70 && volume >= 60){
    Serial.println("Tank is at Quarter Full \n");
    }
  else if (volume < 60 && volume >= 40){
    Serial.println("Tank is Half Full \n");
    }
  else if (volume < 40 && volume >= 25){
    Serial.println("Tank is three Quarter filled \n");
    }
  else{
    Serial.println("Tank is full \n");
    }
  delay(1000);
  Serial.println("-------------------------------------------------------------- ");
}
