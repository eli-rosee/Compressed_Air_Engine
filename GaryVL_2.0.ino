// include the library code:
#include <LiquidCrystal.h>
#include <PWM.h>

/*
This program was written by Eli Rose, adapted from program by Bill Wade (V1.0)
This program is to operate a pneumatic valve
This program use an LCD display to aid in debugging
This program uses PWM to operate a pneuamtic valve

This version of the program simulates input from an encoder with values from 0 to 500 (extended from 360 for timing purposes, will be adjusted in V3.0)
The valve opens under the following conditions in V2.0 of the program.  Later versions will adjust for temperature

Encoder values
0 to 126 left piston cycles once; pressurizes (open to compressed air), then retracts (exhaust port opens)
127 neither pitson moves, valve in neutral position
128 to 255 right piston cycles once; pressurizes (open to compressed air), then retracts (exhaust port opens)
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

// Initialize the library by associating any needed LCD interface pin with the arduino pin number it is connected to
// Add variables for pneuamatic valve

const int valvePositionA = 1;
const int MotorThermistorA = 2;
// const int MotorEncoder = 3;
const int PressureA = 4;
const int RotationD = 5;
const int ForceA = 5;


// Initializes variables utilized in the loop and calculations afterword (unimplemented)
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

// Set initial valve position to neutral
int initialVal = 127;
analogWrite(3, initialVal);

// Initialize Encoder Values
int leftPiston = 0;
int rightPiston = 255;

encoderValue = 3000;
lcd.clear();

// Loop that gives a 3000 tick timer countdown for pressurization setup
while(encoderValue >= 0)
{
  // Gets rid of extra 0 once it switches to 3 digit
  if(encoderValue == 999)
  {
    lcd.clear();
  }

  lcd.setCursor(0, 0);
  lcd.print("Countdown: ");//
  lcd.print(encoderValue);
  lcd.setCursor(0, 1);
  lcd.print("EncoderVal: ");
  lcd.print(initialVal);
  encoderValue = encoderValue - 1;
}

// Starts the pistons off with initial vals while increasing / decreasing by 5 to test value range using analogWrite
// Displays to lcd screen all actions taken, as well as the timer (encoderValue)
while(i < 127 && j > 127)
{
  lcd.clear();
  encoderValue = 0;
  leftPiston = leftPiston + 5;
  leftPiston = leftPiston - 5;

  while(encoderValue <= 500)
  {

    lcd.setCursor(0, 1);
    lcd.print("Loop: ");
    lcd.print(encoderValue); 

    if (encoderValue > 0 and encoderValue < 250)
    {
      analogWrite(3, leftPiston);
      lcd.setCursor(0, 0);
      lcd.print("Encoder: ");
      lcd.print(leftPiston)
      lcd.print("/500")
    }

    if (encoderValue > 250 and encoderValue < 500)
    {
      analogWrite(3, rightPiston);
      lcd.setCursor(0, 0);
      lcd.print("Encoder: ");
      lcd.print(rightPiston)
      lcd.print("/500")
    }

      encoderValue = encoderValue + 1;
  }
}

// Unused calculations (implemented later)

  //  Vo = analogRead(ThermistorPin);
  // R2 = R1 * (1023.0 / (float)Vo - 1.0);
  // logR2 = log(R2);
  // T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  // T = T - 273.15;
  // T = (T * 9.0)/ 5.0 + 32.0;
  // T = Temperature in Fairenheight measured by the thermistor

}