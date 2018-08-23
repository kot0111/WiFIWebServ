//Проект веб сервера IOT
//Код для Arduino UNO
//Автор - Kot0111
#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <math.h>
#define REL_PIN 12
#define TEMP_PIN A3
SoftwareSerial esp(4, 5);
Servo myServo;
void setup() {
// Настройка GPIO
//Запуск serial
  esp.begin(9600);
  pinMode(REL_PIN, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(REL_PIN, LOW);
  myServo.attach(10);
  digitalWrite(2,HIGH);
  myServo.write(0);
  delay(500);
  digitalWrite(2,LOW);  

}
void loop() {
//Обработка входящих запросов
  String command = esp.readStringUntil('\n');
  command.trim();
  if (command == "turn1On") {
    
    digitalWrite(REL_PIN, HIGH);
  }
  if (command == "turn1Off") {
    digitalWrite(REL_PIN, LOW);
  }
  if (command == "tempUpd") {
    float voltage = analogRead(TEMP_PIN) / 1024.0 * 5.0 - 0.5;
    float temp = voltage * 100.0;
    esp.println  (temp);//Отправка данных о температуре на ESP8266
  }
  if (command == "Servo180") {
      digitalWrite(2,HIGH);
    myServo.write(180);
      delay(500);
      digitalWrite(2,LOW); 
  }
  if (command == "Servo0") {
      digitalWrite(2,HIGH);
    myServo.write(0);
      delay(500);
      digitalWrite(2,LOW); 
  }
}
