#include <LiquidCrystal.h>
#include <dht.h>
#define outPin 13
#define buttonPin A0

dht DHT;
int i, j;
int trigPin = 6;                  //Trig Pin
int echoPin = 9;                  //Echo Pin
long duration, cm, inches;
float t, h;
int buttonState, mode = 0;
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
 
void setup() {
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        // 定義輸入及輸出 
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2);
}

void show_tdo_dis(){
  //int temp, humid;
  lcd.setCursor(8, 0);
  lcd.print(cm);
  lcd.setCursor(13, 0);
  lcd.print("CM ");
  lcd.setCursor(8, 1);
  lcd.print(inches);
  lcd.setCursor(13, 1);
  lcd.print("inch");
}

void show_tdo_dis_reset(){
  for(j = 0; j < 2; j++) {
   for(i = 8; i < 13; i++) {
      lcd.setCursor(i, j);
      lcd.print(" ");
    } 
  }
  lcd.setCursor(13, 0);
  lcd.print("CM ");
  lcd.setCursor(13, 1);
  lcd.print("inch");
}

void show_tdo_TempHumid(){
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

void reset_lcd(){
  for(j = 0; j < 2; j++) {
   for(i = 0; i < 16; i++) {
      lcd.setCursor(i, j);
      lcd.print(" ");
    } 
  }
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  Serial.print(buttonState);
  Serial.print("\n");
  if(buttonState) {
    mode = (mode == 0)?1:0;
  }
  switch(mode) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("Length: ");
      
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
    
      pinMode(echoPin, INPUT);             // 讀取 echo 的電位
      duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
     
      cm = (duration/2) / 29.1;         // 將時間換算成距離 cm 或 inch  
      inches = (duration/2) / 74; 
    
      show_tdo_dis();
      delay(1000);
      show_tdo_dis_reset();
      break;
    case 1:
      int readData = DHT.read11(outPin);

      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.setCursor(0, 1);
      lcd.print("Humid: ");
    
      t = DHT.temperature;        // Read temperature
      h = DHT.humidity;           // Read humidity
      show_tdo_TempHumid();
      delay(2000); // wait two seconds
      break;
  }
  reset_lcd();
  /*
  Serial.print("Distance : ");  
  Serial.print(inches);
  Serial.print("in,   ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  */
}
