#include <Wire.h>
#include <LiquidCrystal.h> //Header file for LCD
//const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2; //pins of LCD connected to Arduino
LiquidCrystal lcd(12,11,5,4,3,2); //lcd function from LiquidCrystal
int buz = 8; //buzzer connected to pin 8
int led = 9; //led connected to pin 9
int fan = 10; //fan connected to pin 13
const int aqsensor = A0; //output of mq135 connected to A0 pin of Arduino
int threshold = 100; //Threshold level for Air Quality
void setup() {
    pinMode (buz,OUTPUT); // buzzer is connected as Output from Arduino
    pinMode (led,OUTPUT); // led is connected as output from Arduino
    pinMode (aqsensor,INPUT); // MQ135 is connected as INPUT to Arduino
    Serial.begin (9600); //begin serial communication with baud rate of 9600
    digitalWrite(led,LOW);
    lcd.clear(); // clear lcd
    lcd.begin (16,2); // consider 16,2 lcd
}
void loop() {
    lcd.display();
    lcd.clear();
    int ppm = analogRead(aqsensor); //read MQ135 analog outputs at A0 and store it in ppm
    Serial.print("Air Quality: "); //print message in serail monitor
    Serial.println(ppm); //print value of ppm in serial monitor
    lcd.setCursor(0,0); // set cursor of lcd to 1st row and 1st column
    lcd.print("Air Quality: "); // print message on lcd
    lcd.print(ppm); // print value of MQ135
    if (ppm > 150 && ppm <=300) // check is ppm is greater than threshold or not
    {
        lcd.setCursor(1,1); //jump here if ppm is greater than threshold
        lcd.print("AQ Level BAD");
        Serial.println("AQ Level BAD"); 
        tone(led,1000,200); //blink led with turn on time 1000mS, turn off time 200mS
        digitalWrite(buz,HIGH); //Turn ON Buzzer
        digitalWrite(fan,HIGH); //Turn ON fan
    }
    else if (ppm > 300)
    {
        lcd.setCursor(1,1); //jump here if ppm is greater than threshold
        lcd.print("AQ Level TOXIC");
        Serial.println("AQ Level TOXIC"); 
        tone(led,1000,200); //blink led with turn on time 1000mS, turn off time 200mS
        digitalWrite(buz,HIGH); //Turn ON Buzzer
        digitalWrite(fan,HIGH); //Turn ON fan
    }
    else
    {
        digitalWrite(led,LOW); //jump here if ppm is not greater than threshold and turn off LED
        digitalWrite(buz,LOW); //Turn off Buzzer
        digitalWrite(fan,LOW); //Turn off fan
        lcd.setCursor(1,1);
        lcd.print("AQ Level GOOD");
        Serial.println("AQ Level GOOD");
    } 
    delay(500);
}
