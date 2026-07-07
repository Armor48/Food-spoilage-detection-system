#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define DHTPIN 7    // Pin for DHT22 sensor
#define DHTTYPE DHT11   // DHT 22 (AM2302)

LiquidCrystal_I2C lcd(0x3F, 20, 4);
DHT dht(DHTPIN, DHTTYPE);

#define LDRPIN2 10   // Pin for LDR module
#define LDRPIN1 9   // Pin for LDR module
#define MQ3PIN A0    // GPIO pin for MQ-3 gas sensor

// SoftwareSerial Serial(10, 11); // RX, TX

void setup() {

  // Serial.begin(9600);     // Serial Monitor
  Serial.begin(9600);  // ESP8266 Serial
  delay(100);
  Serial.println("Initializing...");
  pinMode(LDRPIN2, INPUT);
  pinMode(LDRPIN1, INPUT);
  pinMode(MQ3PIN, INPUT);

  lcd.begin();
  lcd.clear();
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int ldrValue1 = digitalRead(LDRPIN1);
  int ldrValue2 = analogRead(LDRPIN2);
  int mq3Value = analogRead(MQ3PIN);

  lcd.setCursor(2,0);
  lcd.print("Temp");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, LDR Value: ");
  Serial.print(ldrValue2/10);
  Serial.print(", ");
  Serial.print(ldrValue1);
  Serial.print(", MQ3 Value: ");
  Serial.println(mq3Value/10);

  delay(2000);
}
