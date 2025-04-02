#include <LiquidCrystal_I2C.h>
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
void printDetail(uint8_t type, int value);
int TRIG = 4;
int ECHO = 5;

double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25;

  LiquidCrystal_I2C lcd(0x27, 16,2);

void setup() {
  lcd.init();
  lcd.backlight();
   pinMode(sensor, INPUT);
   pinMode(5,OUTPUT); //
   pinMode(7,OUTPUT); //反応時にON
   pinMode(TRIG,OUTPUT); //超音波センサ↓
   pinMode(ECHO,INPUT);

mySoftwareSerial.begin(9600); //LCDクリア
  Serial.begin(9600);
 delay(50);
  lcd.setCursor(0, 0);
  lcd.print("Yashago Famima");
  lcd.setCursor(0,1);
  lcd.print("Doorbell V3");
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
 digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite( TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( TRIG, LOW );
  duration = pulseIn( ECHO, HIGH );

  if (duration > 0) {
    duration = duration / 2; 
    distance = duration * speed_of_sound * 100 / 1000000;
   
  }
   if(distance < 75){　//センサーの反応する距離
    digitalWrite(7,HIGH);
    p = p+1;
    lcd.setCursor(0,1);
    lcd.print(p);
   myDFPlayer.play(1);
   delay(10000);
   digitalWrite(7,LOW);

 }else{
  myDFPlayer.stop();
 }
 if( Serial.available() > 0 ) {　//LCD入場者数カウンタ
    Serial.println(Serial.read());
    lcd.setCursor(10,1);
    lcd.print(Serial.read());
    p = p + Serial.read();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Updated");
    delay(1000);
    lcd.home();
    lcd.print("Applying...");
    delay(2000);
    lcd.home();
    lcd.print("\xd4\xbc\xac\xba\xde Base \xcd\xd6\xb3\xba\xbf");
    lcd.setCursor(0,1);
    lcd.print(p);
      
    
    
  }
}
