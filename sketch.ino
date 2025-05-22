#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_PIN 34

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C 16x2, alamat 0x27

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Wire.begin(21, 22); // SDA, SCL ESP32 default

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Sensor siap...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int adcValue = analogRead(SENSOR_PIN);
  float phValue = (adcValue / 4095.0) * 14.0;        // Skala pH 0-14
  float glucoseValue = (adcValue / 4095.0) * 1000.0; // Skala glukosa mg/dL 0-1000

  // Tampilkan di Serial
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | pH: ");
  Serial.print(phValue, 2);
  Serial.print(" | Glukosa: ");
  Serial.print(glucoseValue, 1);
  Serial.println(" mg/dL");

  // Tampilkan di LCD: baris 1 = pH, baris 2 = Glukosa
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(phValue, 2);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print("Glu: ");
  lcd.print(glucoseValue, 1);
  lcd.print(" mg/dL ");

  delay(1000);
}
