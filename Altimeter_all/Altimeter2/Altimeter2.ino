#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <EEPROM.h>

//Variables
int val_0 = 0;
int val = 0;
int val1 = 0;
int cen1 = 0;
int dec1 = 0;
int uni1 = 0;
int led = 13;
int bl = 300;
int sp = 200;
int for_blink = 6;
int pot = A0;

Adafruit_BMP085 bmp;

void setup() {                
  bmp.begin();
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(for_blink, INPUT);
  pinMode(7, INPUT);
  val_0 = bmp.readAltitude();
}

void loop() {
  if (digitalRead(7) == HIGH){
    delay(1000);
    for(int blink1 = 0 ; blink1 < 8; blink1 ++) { 
      digitalWrite(led, HIGH);
      delay(80);
      digitalWrite(led, LOW);
      delay(30);
    }
    starting();
  }
  showread(); 
}


//starting blink sequence
void showread() {
  delay(2000);
  for(int blink1 = 0 ; blink1 < 3; blink1 ++) { 
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(50);
  }
  delay(2000);

  for(int blink1 = 0 ; blink1 < EEPROM.read(0); blink1 ++) { 
    digitalWrite(led, HIGH);
    delay(bl);
    digitalWrite(led, LOW);
    delay(sp);
  }

  delay(1000);
  for(int blink1 = 0 ; blink1 < EEPROM.read(1); blink1 ++) { 
    digitalWrite(led, HIGH);
    delay(bl);
    digitalWrite(led, LOW);
    delay(sp);
  }

  delay(1000);
  for(int blink1 = 0 ; blink1 < EEPROM.read(2); blink1 ++) { 
    digitalWrite(led, HIGH);
    delay(bl);
    digitalWrite(led, LOW);
    delay(sp);
  }

}


void starting(){
  val = analogRead(pot);
//  val = bmp.readAltitude() - val_0;
  Serial.println(val);
  delay(300);
  digitalWrite(led, HIGH);
  
  // extracting the values
  if (val > val1){
    val1 = val;
    cen1 = val1/100;
    dec1 = (val1 - (cen1*100))/10;
    uni1 = (val1 - (cen1*100) - (dec1*10));
    EEPROM.write(0,cen1);
    EEPROM.write(1,dec1);
    EEPROM.write(2,uni1);
  }

  //call function for blink led
  if (digitalRead(for_blink) == HIGH){
    digitalWrite(led, LOW);
    showread();
    showread();
    showread();    
    delay(2000);
  }
  starting();
}


