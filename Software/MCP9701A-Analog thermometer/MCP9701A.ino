/*=========================Header=========================*/
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
/*=========================Variables=========================*/
const int numReadings = 10;

int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total 

int averageValue = 0;           // the average
int oldValue = 0;
int storedValue = 0; 
int delta = 1;            // 0.2C per 1 - difference 

float voltage = 0;

int state = 0; 
float tempvalue = 0;

 // Read the temp from the sensor.
float ATStemp = 0;
/*=========================A and D Pins=========================*/

int AIN0 = 0; //17.07.2023

/*=========================SetUP=========================*/
void setup() {

  Serial.begin(9600);
  delay(1000);       //Serial display start up
  Serial.println("SYSSTART!"); 

  for (int thisReading = 0; thisReading < numReadings; thisReading++) { 
    readings[thisReading] = 0;
  }
/*=========================Pin Modes=========================*/
  //10.07.2023
  pinMode(LED_BUILTIN,OUTPUT);

/*=======================Start up phase========================*/

  }

void loop() {

  /*===================BuiltIn blink indicator=================*/
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);                   
  digitalWrite(LED_BUILTIN,LOW);//10.07.2023
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);


//13.07.202
  if(ATStemp >=10 && ATStemp <= 25){ 
    Serial.println("Acceptable!");

  }
  if(ATStemp >= 0 && ATStemp < 10){
    Serial.println("COLD!!");
  }
  if(ATStemp > 25){
    Serial.println("HOT!!");
  }
  textTempnHum();
  ATSaverage();
}

/*=========================Void Functions=========================*/
//18/19.07.2023
void textTempnHum(void) {

  Serial.print("ATemp: ");
  Serial.print(ATStemp);
  Serial.print(" C");
  Serial.println();
  delay(1000);
}
//17.07.2023
void ATSaverage (void){
  oldValue = averageValue; 

  // subtract the last reading:
  total = total - readings[readIndex];
  
  // read from the sensor:
  readings[readIndex] = analogRead(AIN0);

  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  
  // calculate the average:
  averageValue = total / numReadings;

  if (oldValue != averageValue){
    if((averageValue - storedValue) != delta){
         // print the new value

          voltage = averageValue*3.270/1024;


          ATStemp = (voltage-0.4)/0.0195;
          Serial.print("ATemp = ");
          Serial.print(ATStemp);
          Serial.print(" C");
          Serial.println();
          
          storedValue = averageValue;
      }
}

  delay(100);

}
