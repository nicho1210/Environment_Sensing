#include <LiquidCrystal.h>
#include <dht.h>        // Include library
#define outPin 7        // Defines pin number to which the sensor is connected

dht DHT;                // Creates a DHT object

float t;
float h;

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void show_tdo(){
  int temp, humid;
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.setCursor(12, 0);
  lcd.print("C ");
  lcd.setCursor(6, 1);
  lcd.print(h);
  lcd.setCursor(12, 1);
  lcd.print("%");
}

void loop() {
  int readData = DHT.read11(outPin);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");

  t = DHT.temperature;        // Read temperature
  h = DHT.humidity;           // Read humidity
  show_tdo();
  delay(2000); // wait two seconds
}
