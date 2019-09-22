// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN1 2     // Digital pin connected to the DHT sensor
#define DHTPIN2 7
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht1.begin();
  dht2.begin();

  //fan pinout
  pinMode(3,OUTPUT);
  pinMode(5, OUTPUT);
  //pin for led
  pinMode(13, OUTPUT);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  float t1 = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f1 = dht1.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1) || isnan(f1)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht1.computeHeatIndex(f1, h1);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht1.computeHeatIndex(t1, h1, false);

  Serial.print(F("Humidity @ Bottom (Pin2): "));
  Serial.print(h1);
  Serial.print(F("%  Temperature @ Bottom (Pin2): "));
  //Serial.print(t);
  //Serial.print(F("°C "));
  Serial.print(f1);
  Serial.print(F("°F  Heat index @ Bottom (Pin2): "));
 // Serial.print(hic);
  //Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));



  //sensor 2 at top
    float h2 = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  float t2 = dht2.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f2 = dht2.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif2 = dht2.computeHeatIndex(f2, h2);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic2 = dht2.computeHeatIndex(t2, h2, false);

  //double variable to calculate average temp
 double averageTemp = ((f1+f2)/2);
 
  Serial.print(F("Humidity @ Top (Pin7): "));
  Serial.print(h2);
  Serial.print(F("%  Temperature @ Top (Pin7): "));
  //Serial.print(t);
  //Serial.print(F("°C "));
  Serial.print(f2);
  Serial.print(F("°F  Heat index @ Top (Pin7): "));
 // Serial.print(hic);
  //Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  Serial.print("Average Temp: ");
  Serial.println(averageTemp);
  Serial.println();

  //code for fans
   if(averageTemp > 75){
    digitalWrite(3,HIGH);//turn on fan
    delay(2000);//at 100%
    digitalWrite(5,HIGH);//turn on fan
    delay(2000);//at 100%
    //led on
    digitalWrite(13, HIGH);   
   delay(1000);              
   //digitalWrite(13, LOW);   
   //delay(1000);
  }
  else if(averageTemp < 75){
     digitalWrite(3,LOW);//turn on fan
    //delay(2000);//at 100%
    digitalWrite(5,LOW);
    digitalWrite(13, LOW);   
    delay(1000);
  }
  
}
