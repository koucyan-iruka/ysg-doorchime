#include <LiquidCrystal.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2, 3); 
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

const int sensor = 4;     // the number of the pushbutton pin
// variables will change:
int State = 0;         // variable for reading the pushbutton status
int p = 0;
  LiquidCrystal lcd(7,8,9,10,11,12);

void setup() {
 lcd.begin( 16, 2 );
   pinMode(sensor, INPUT);
   pinMode(5,OUTPUT);

mySoftwareSerial.begin(9600);
  Serial.begin(9600);
 delay(50);
  lcd.setCursor(0, 0);
  lcd.print("Yashago Famima");
  lcd.setCursor(0,1);
  lcd.print("Doorbell V2");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  Serial.println("Initializing...");
  

   if (!myDFPlayer.begin(mySoftwareSerial)) {
    // 2秒以内に初期化できなかった場合はエラーメッセージを表示
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unable to Start.");
    lcd.setCursor(0,1);
    lcd.print("Check SD card.");
    Serial.println(F("Unable to Start:"));
    Serial.println(F("1.Please recheck the connection."));
    Serial.println(F("2.Please insert the SD card."));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println("Ready");
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
  
   State = digitalRead(sensor);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (State == HIGH) {
     digitalWrite(5,HIGH);
     p = p+1;
   Serial.println(p);
   lcd.setCursor(0,1);
   lcd.print(p);
   myDFPlayer.play(1);
   delay(10000);
   digitalWrite(5,LOW);
  } else {
    myDFPlayer.stop();
  }
}
