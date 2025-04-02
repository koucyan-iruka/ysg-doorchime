#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2, 3); 
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
// the number of the pushbutton pin
// variables will change:
int State = 0;         // variable for reading the pushbutton status
int p = 0;
int s = 1;
void printDetail(uint8_t type, int value);

  LiquidCrystal_I2C lcd(0x27, 16,2);

void setup() {
  lcd.init();
  lcd.backlight();
   pinMode(7,OUTPUT);
   pinMode(4,INPUT);
   pinMode(9,INPUT);

mySoftwareSerial.begin(9600);
  Serial.begin(9600);
 delay(50);
  lcd.setCursor(0, 0);
  lcd.print("Yashago Famima");
  lcd.setCursor(0,1);
  lcd.print("Doorbell V4.5");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  Serial.println("Initializing...");
  

   if (!myDFPlayer.begin(mySoftwareSerial)) {
    // 2秒以内に初期化できなかった場合はエラーメッセージを表示
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error");
    lcd.setCursor(0,1);
    lcd.print("Unable to Start.");
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ready");
  delay(1000);
  lcd.clear();
  // initialize the pushbutton pin as an input:
  lcd.print("\xd4\xbc\xac\xba\xde Base \xcd\xd6\xb3\xba\xbf");
  lcd.setCursor(0,1);
  lcd.print(p);
  myDFPlayer.volume(30);
 }
void loop() {
  if (digitalRead(9) == HIGH) {
      s = 2;
    }else if (digitalRead(9) == LOW){
     s = 1;   
     }
   if(digitalRead(4) == LOW){
    digitalWrite(7,HIGH);
    p = p+1;
    lcd.setCursor(0,1);
    lcd.print(p);
   myDFPlayer.play(s);
   delay(10000);
   digitalWrite(7,LOW);

 }else{
  myDFPlayer.stop();
  }
  Serial.println(digitalRead(4));
}
