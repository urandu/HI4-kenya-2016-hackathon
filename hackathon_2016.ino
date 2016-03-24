#include <Wire.h>
#include "rgb_lcd.h"
#include <fix_fft.h>
/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin =  8;      // the number of the LED pin
rgb_lcd lcd;



unsigned long int starttime;
unsigned long int endtime;



const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
const int sampleRate=600;
int samples[sampleRate];

bool asthma=false;
bool bronchitis=false;
bool pneumonia=false;
bool epiglotis=false;



char im[sampleRate];
char data[sampleRate];

// Define the pins to which the sound sensor and LED are connected.
const int pinSound = A3;
//const int pinLed   = 7;
const int pinSpeaker = 6;

// Define the sound level above which to turn on the LED.
// Change this to a larger value to require a louder noise level.
int thresholdValue = 500;


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("Booting.....");

    delay(1000);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}






   

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    lcd.clear();
    
    lcd.print("blow after beep");
    delay(2000);
    digitalWrite(pinSpeaker, HIGH);
    delay(500);
    digitalWrite(pinSpeaker, LOW);

    lcd.clear();
    lcd.print("Please blow..");


starttime = millis();
endtime = starttime;
//while ((endtime - starttime) <=3000) // do this loop for up to 1000mS
//{
// code here
//loopcount = loopcount+1;
//endtime = millis();
//}
  for(int i=0;i<=sampleRate;i++)
  {
    samples[i]=analogRead(pinSound);
    data[i]=samples[i] - 128;
    im[i]=0;
    
    
    
   // Serial.print(analogRead(pinSound));
    //Serial.print(" ");
    delay(5);
  }
    fix_fft(data,im,7,0);
    for (int ii=0; ii< 256;ii++){
                 data[ii] = sqrt(data[ii] * data[ii] + im[ii] * im[ii]);
         // Serial.write(data[i]);
         //Serial.print(" new");  
          }
    
    show_big_bars(data);
    
    //lcd.clear();
    //lcd.print(analogRead(pinSound));
    //delay(3000);

    //lcd.clear();
    //lcd.print("waiting...");
    
  

  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  
  
  
  
}
 void show_big_bars(char *spektrum) {
        int spek_for_draw;
      //  nokia.drawline(10, 15, 10, 39, BLACK);
        for (byte i = 1; i < 64; i++){ // Skip 0 Channel
          // Serial.print(spektrum[i],BYTE);
          spek_for_draw = ((1.5*(spektrum[i])*100*2.5)); // 0/2.5 ~ 255/2.5
          //if (spek_for_draw > 39) spek_for_draw = 39;
               Serial.print(spek_for_draw);
               Serial.print(" ");
               if(i>5)
             {
               //asthma test
               if( ( (((1.5*(spektrum[i])*100*2.5))>100)&&(((1.5*(spektrum[i-1])*100*2.5))>100)&&(((1.5*(spektrum[i-2])*100*2.5))>100)&&(((1.5*(spektrum[i-3])*100*2.5))>100)  ) && (  (((1.5*(spektrum[i])*100*2.5))<=1000)&&(((1.5*(spektrum[i-1])*100*2.5))<=1000)&&(((1.5*(spektrum[i-2])*100*2.5))<=1000)&&(((1.5*(spektrum[i-3])*100*2.5))<=1000)  )   )
               {
                 asthma=true;
               }
               
               //pneumonia test
               if( ( (((1.5*(spektrum[i])*100*2.5))>100)&&(((1.5*(spektrum[i-1])*100*2.5))>100)&&(((1.5*(spektrum[i-2])*100*2.5))>100)&&(((1.5*(spektrum[i-3])*100*2.5))>100)  ) && (  (((1.5*(spektrum[i])*100*2.5))<=200)&&(((1.5*(spektrum[i-1])*100*2.5))<=200)&&(((1.5*(spektrum[i-2])*100*2.5))<=200)&&(((1.5*(spektrum[i-3])*100*2.5))<=200)  )   )
               {
                 pneumonia=true;
               }
               
             }
             if( i>25)
           {
             
              //bronchitis test
               if( (  (((1.5*(spektrum[i])*100*2.5))<=300)&&(((1.5*(spektrum[i-1])*100*2.5))<=300)&&(((1.5*(spektrum[i-2])*100*2.5))<=300)&&(((1.5*(spektrum[i-3])*100*2.5))<=300)&&(((1.5*(spektrum[i-4])*100*2.5))<=300)&&(((1.5*(spektrum[i-5])*100*2.5))<=300)&&(((1.5*(spektrum[i-6])*100*2.5))<=300)&&(((1.5*(spektrum[i-7])*100*2.5))<=300)&&(((1.5*(spektrum[i-8])*100*2.5))<=300)&&(((1.5*(spektrum[i-9])*100*2.5))<=300)&&(((1.5*(spektrum[i-10])*100*2.5))<=300)&&(((1.5*(spektrum[i-11])*100*2.5))<=300)&&(((1.5*(spektrum[i-12])*100*2.5))<=300)&&(((1.5*(spektrum[i-13])*100*2.5))<=300)&&(((1.5*(spektrum[i-14])*100*2.5))<=300)&&(((1.5*(spektrum[i-15])*100*2.5))<=300)&&(((1.5*(spektrum[i-16])*100*2.5))<=300)&&(((1.5*(spektrum[i-17])*100*2.5))<=300)&&(((1.5*(spektrum[i-18])*100*2.5))<=300)&&(((1.5*(spektrum[i-19])*100*2.5))<=300)  )   )
               {
                 bronchitis=true;
               }
             
           }
            



        //  nokia.drawline(i+10, 39 - spek_for_draw, i+10, 39, BLACK);
        }
        if(asthma || bronchitis || pneumonia)
          {
            if(asthma)
          {
            lcd.clear();
            lcd.print("WHEEZING PRESENT.");
            digitalWrite(ledPin, HIGH);
            digitalWrite(pinSpeaker, HIGH);
            delay(5000);
            digitalWrite(pinSpeaker, LOW);
            digitalWrite(ledPin, LOW);
          }
          if(bronchitis )
          {
            lcd.clear();
            lcd.print("RHONCHI PRESENT.");
            digitalWrite(ledPin, HIGH);
            digitalWrite(pinSpeaker, HIGH);
            delay(5000);
            digitalWrite(pinSpeaker, LOW);
            digitalWrite(ledPin, LOW);
          }
          if( pneumonia)
          {
            lcd.clear();
            lcd.print("CRACKLES PRESENT.");
            digitalWrite(ledPin, HIGH);
            digitalWrite(pinSpeaker, HIGH);
            delay(5000);
            digitalWrite(pinSpeaker, LOW);
            digitalWrite(ledPin, LOW);
          }
          }
          else
        {
          lcd.clear();
        lcd.print("CONDITION: NORMAL.");
        digitalWrite(ledPin, HIGH);
            digitalWrite(pinSpeaker, HIGH);
            delay(200);
            digitalWrite(pinSpeaker, LOW);
            digitalWrite(ledPin, LOW);
            delay(200);
            digitalWrite(ledPin, HIGH);
            digitalWrite(pinSpeaker, HIGH);
            delay(200);
            digitalWrite(pinSpeaker, LOW);
            digitalWrite(ledPin, LOW);
        } 
      
    
    
  }

