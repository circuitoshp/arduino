/////////////////////////
// Arduino Altimeter BMP085
// Designed by naldin
// naldin.net (at) gmail
// 01/13/2014
// v1.00
/////////////////////////

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
int switch1 = 7;
int pot = A0; //for test

Adafruit_BMP085 bmp;

void setup() {                
  bmp.begin();
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(switch1, INPUT);
  val_0 = bmp.readAltitude();
}

void loop() {
  if (digitalRead(switch1) == HIGH){
    currentalt();
  }
  showread(); 
}


//show values from eeprom
void showread() {
  while(digitalRead(switch1) == LOW){
    delay(2000);
    blink1(3,100,50);
    delay(2000);

    delay(1000);
    blink1(EEPROM.read(0),300,200);

    delay(1000);
    blink1(EEPROM.read(1),300,200);

    delay(1000);
    blink1(EEPROM.read(2),300,200);
  }

  //going to getvalue function
  Serial.println("Exited showread");
  blink1(15,100,50);
  delay(2000);
  getvalue();
}


//getting and processing values
void getvalue(){
  while(digitalRead(switch1) == LOW){
//    val = analogRead(pot); //for test
    val = bmp.readAltitude() - val_0;
    Serial.println(val);
    delay(100);
    digitalWrite(led, HIGH);

    if (val > val1){
      val1 = val;
    }
  }
  
  //extracting and burning values to eeprom
  cen1 = val1/100;
  dec1 = (val1 - (cen1*100))/10;
  uni1 = (val1 - (cen1*100) - (dec1*10));

  EEPROM.write(0,cen1);
  EEPROM.write(1,dec1);
  EEPROM.write(2,uni1);

  //going to showread function
  Serial.println("Exited getvalue");
  blink1(15,100,50);
  digitalWrite(led, LOW);
  delay(2000);
//  showread();
}



// show current altitude
void currentalt(){
  int alt1 = val_0;
  blink1(15,100,50);
  delay(2000);
  while(digitalRead(switch1) == LOW){
    Serial.print("Altitude = ");
    Serial.print(alt1);
    Serial.println(" meters");    
    cen1 = alt1/100;
    dec1 = (alt1 - (cen1*100))/10;
    uni1 = (alt1 - (cen1*100) - (dec1*10));

    delay(2000);
    blink1(3,100,50);
    delay(2000);

    delay(1000);
    blink1(cen1,300,200);

    delay(1000);
    blink1(dec1,300,200);

    delay(1000);
    blink1(uni1,300,200);

  }
  blink1(15,100,50);
  delay(2000);  
}



//blink function
void blink1(int j, int bl, int sp){
  int i =0;
  for(i = 0 ; i < j; i ++) { 
    digitalWrite(led, HIGH);
    delay(bl);
    digitalWrite(led, LOW);
    delay(sp);
  }
}


