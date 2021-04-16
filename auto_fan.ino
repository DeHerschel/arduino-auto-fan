#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h> 
#include <DHT.h>	
//LCD COLS AND ROWS
#define COLS 16
#define ROWS 2
//TEMP SENSOR
#define DHTPIN 7
#define DHTTYPE DHT11
const int motorPin = 13;
//Sonar pins
const int EchoPin = 8;
const int TriggerPin = 9;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(COLS, ROWS);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(13, OUTPUT); 
  dht.begin();
}

void loop() {
  delay(1000);
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    return;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(temp);
  int cm = ping(TriggerPin, EchoPin);
  lcd.setCursor(0,3);
  lcd.print("Distancia: ");
  lcd.print(cm);
  lcd.print("cm");
  if (temp > 26 ) {
    int cm = ping(TriggerPin, EchoPin);
    lcd.print("Distance: ");
    lcd.print(cm);
    lcd.print("cm");
    if (cm < 150) {
      digitalWrite(motorPin, HIGH);
    }
    else {
      digitalWrite(motorPin, LOW);
    }
  } else {
      digitalWrite(motorPin, LOW);
    }
}
int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   digitalWrite(TriggerPin, LOW);
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   duration = pulseIn(EchoPin, HIGH);
   distanceCm = duration * 10 / 292/ 2;
   return distanceCm;
}
