#include <PWM.h>

/*
 * This program was written by Bill Wade
 * This program is to operate a pneumatic valve
 * This program use an LCD display to aid in debugging
 * This program uses PWM to operate a pneuamtic valve
 * This version of the program simulates input from an encoder with values from 1 to 360
 * The valve opens under the following conditions in V1.0 of the program.  Later versions will adjust for temperature
 * Encoder values
 * 0 to 30 open to compressed air,  input open
 * 30 to 180 pressurize, valve closed
 * 180 to 360 exhaust. exhasut port open
 *  
 *  
 * 
 */

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <PWM.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// add variables for pneuamatic valve
const int valvePositionA = 1;
const int MotorThermistorA = 2;
// const int MotorEncoder = 3;
const int PressureA = 4;
const int RotationD = 5;
const int ForceA = 5;

// end variables for pneumatic valve

int loopCounter = 0;
int encoderValue = 0;
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

const int rs = 13, en = 12, d4 =11, d5 =10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  // lcd.print("hello, Nick!");

    // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  InitTimersSafe();
  // bool success = SetPinFrequency(3,2000);
  
}

void loop() {
  
if (encoderValue >= 360){
    encoderValue = 0;
}

lcd.setCursor(1, 1);
lcd.print("Encoder  = ");//

    lcd.print(encoderValue);   
  
if (encoderValue >= 0 and encoderValue < 31){
      analogWrite(3,1);
       lcd.setCursor(0, 0);
       lcd.print("Valve = Pressurize");
   
}
        
if (encoderValue >30 and encoderValue < 180){
        analogWrite(3,127);
         lcd.setCursor(0, 0);
         lcd.print("Valve = Closed          ");
 
}

if (encoderValue >180){
      analogWrite(3,255); 
       lcd.setCursor(0, 0);
      lcd.print("Valve = Exhaust           ");
 
} 
  
  encoderValue = encoderValue +1;
  loopCounter = loopCounter + 1;
   Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0;
  // T = Temperature in Fairenheight measured by the thermistor

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(1, 1);
//   print the number of seconds since reset:
//  lcd.print("Encoder = ");//
//    lcd.print(encoderValue);   
//    lcd.print("L = ");
//   lcd.print(loopCounter);   
//  lcd.print(T)
//  lcd.print(" F"); 
//  lcd.print(millis() / 1000);
//  lcd.print(" s");

//  pwmWrite(3, );
// delay(30);  
 //pwmWrite(3, .0001);
// analogWrite(3,1);
 // lcd.print("PWM = .0001 ");
// delay(100);
 //pwmWrite(3, .0002);
// analogWrite(3,250);
 // lcd.print("PWM = .0002 ");
// delay(100);
 //pwmWrite(3, .0003);
// analogWrite(3,120);
 // lcd.print("PWM = .0003 ");
// delay(100);
 //pwmWrite(3, .0004);
// analogWrite(3,160);
//  lcd.print("PWM = .0004 ");
//// delay(100);
// pwmWrite(3, .0005);
// analogWrite(3,250);
//  lcd.print("PWM = .0005 ");
 //delay(100);
}
