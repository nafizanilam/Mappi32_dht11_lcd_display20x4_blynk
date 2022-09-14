#define BLYNK_TEMPLATE_ID "TMPLdsy2gy98"
#define BLYNK_DEVICE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "r3owW3WBNJGg3a2OD4cajiLA_y3tqrSU"
#define BLYNK_PRINT Serial

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 , 20, 4); // GANTI 0x3F Ke 0x27 kalau LCD ga muncul
#include <DHT.h>
#include <Wire.h>
#include <analogWrite.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
int Con = 100;

DHT dht(32, DHT11); //Pin, Jenis DHT

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KMTek"; //nama wifix
char pass[] = "KMTek123"; //password wifi

BlynkTimer timer;


void myTimerEvent()
{
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup() {
  analogWrite(100, Con);
  lcd.begin();
  Wire.begin();
  Blynk.begin(auth, ssid, pass);
  Serial.begin(112500);
  dht.begin();
}

void loop() {

  Blynk.run();
  timer.run();

  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();

  Serial.print("kelembaban: ");
  Serial.print(kelembaban);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(suhu);

  Blynk.virtualWrite(V1, kelembaban);
  Blynk.virtualWrite(V2, suhu);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kelembaban: ");
  lcd.setCursor(11, 0);
  lcd.print(kelembaban);
  lcd.setCursor(0, 1);
  lcd.print("Suhu: ");
  lcd.setCursor(5, 1);
  lcd.print(suhu);
  delay(1000);
  lcd.clear();
}
