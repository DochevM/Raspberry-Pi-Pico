/*=========================Header=========================*/
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>//13.07.2023
#include "DHT.h"//19.07.2023
/*=========================Defining=========================*/
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels  //14.07.2023
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define LOGO_HEIGHT   32
#define LOGO_WIDTH    64
/*=========================================================*/
/*=========================Bit Map=========================*/
static const unsigned char PROGMEM logo_bmp[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x45, 0x3c, 0x79, 0x3c, 0x00, 0x00, 
	0x00, 0x01, 0x45, 0x02, 0x61, 0x32, 0x00, 0x00, 0x00, 0x01, 0x29, 0x1e, 0x41, 0x22, 0x00, 0x00,  
	0x00, 0x01, 0x29, 0x22, 0x41, 0x22, 0x00, 0x00, 0x00, 0x01, 0x39, 0x26, 0x41, 0x22, 0x00, 0x00, 
	0x00, 0x01, 0x11, 0x3e, 0x41, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
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

int buttonState = 0;
int state = 0; 
float tempvalue = 0;

 // Read the humidity from the sensor.
float DHTtemp = 0;
float DHThum = 0;
float ATStemp = 0;
/*=========================A and D Pins=========================*/
int AIN0 = 0; //17.07.2023
int BUTTON = 15;
int LED_GREEN = 17;
int LED_RED = 18;
int LED_BLUE = 16;
#define DHTPIN 22
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
/*=========================SetUP=========================*/
void setup() {

  Serial.begin(9600);
  delay(1000);       //Serial display start up
  Serial.println("SYSSTART!");

  dht.begin(); //dht sensor startup 

  for (int thisReading = 0; thisReading < numReadings; thisReading++) { 
    readings[thisReading] = 0;
  }
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {  //Erron mesage
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  testdrawbitmap();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.display();
  delay(1000);
/*=========================Pin Modes=========================*/
  //10.07.2023
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(BUTTON,INPUT);//11.07.2023
  pinMode(LED_GREEN,OUTPUT); 
  pinMode(LED_BLUE,OUTPUT);
  pinMode(LED_RED,OUTPUT);
/*=======================Start up phase========================*/
  digitalWrite(LED_GREEN,HIGH);
  digitalWrite(LED_BLUE,HIGH); //startup phase
  digitalWrite(LED_RED,HIGH);
  }

void loop() {

  /*===================BuiltIn blink indicator=================*/
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);                   
  digitalWrite(LED_BUILTIN,LOW);//10.07.2023
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);

  // Read the humidity from the sensor.
  DHThum = dht.readHumidity();
  delay(50);
  // Read the temperature from the sensor.
  DHTtemp = dht.readTemperature();
  delay(50);
/*=========================Conditions=========================*/
  if (DHTtemp != -1 && DHThum != -1)
   {
        Serial.print("Temperature: ");
        Serial.print(DHTtemp);
        Serial.println(" C");

        Serial.print("Humidity: ");
        Serial.print(DHThum);
        Serial.println(" %");

    }
    else
    {
        // If the temperature or humidity reading failed, print an error message.
        Serial.println("Error reading data");
    }
  
//11.07.2023
  buttonState = digitalRead(BUTTON); //Checking if the button is opressed
  if (buttonState == LOW){ //If its pressed => 
  state = 1; 
  do {
    Serial.println("button pressed");
    
    textTempnHum();
    buttonState = digitalRead(BUTTON);
    if (buttonState == HIGH)
    { 
      state = 0;
      break; 
    }
  } while (state);
} else {      //if its not pressed do:
  display.clearDisplay();
  display.display();
  delay(100);
  }
//13.07.202
  if(DHTtemp && ATStemp >=10 && DHTtemp && ATStemp <= 25){ 
    digitalWrite(LED_GREEN,LOW);

  }else{

    digitalWrite(LED_GREEN,HIGH);
  }
  if(DHTtemp && ATStemp >= 0 && DHTtemp && ATStemp < 10){
    digitalWrite(LED_BLUE,LOW);
  }else{

    digitalWrite(LED_BLUE,HIGH);
  }
  if(DHTtemp && ATStemp > 25){
    digitalWrite(LED_RED,LOW);
  }else{

    digitalWrite(LED_RED,HIGH);
  }
 
  ATSaverage();
  buttonFunctions();
}

/*=========================Void Functions=========================*/
//18/19.07.2023
void textTempnHum(void) {

  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 0);
  display.print("DTemp: ");
  display.setCursor(45, 0);
  display.print(DHTtemp);
  display.print(" C");
  display.println();
  display.setCursor(5, 10);
  display.print("DHum: ");
  display.setCursor(45, 10);
  display.print(DHThum);
  display.print(" %");
  display.println();
  display.setCursor(5, 20);
  display.print("ATemp: ");
  display.setCursor(45, 20);
  display.print(ATStemp);
  display.print(" C");
  display.println();
  display.display();      // Show initial text
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
//19.07.2023
void buttonFunctions(void){  
  buttonState = digitalRead(BUTTON); //Checking if the button is opressed
  if (buttonState == LOW){ //If its pressed => 
  state = 1; 
  do {
    Serial.println("Button Pessed!");
    delay(500);
    buttonState = digitalRead(BUTTON);
    if (buttonState == HIGH)
    { 
      state = 0;
      break; 
    }
  } while (state);
} else {      //if its not pressed do:
  Serial.println("Button not pressed!"); 
  delay(500);
  }
  
  if(DHTtemp && ATStemp >=10 && DHTtemp && ATStemp <= 25){
    Serial.println("Green");

  }
  if(DHTtemp && ATStemp >= 0 && DHTtemp && ATStemp < 10){
    Serial.println("Blue");
  }
  if(DHTtemp && ATStemp > 25){
    Serial.println("Red");
  }

}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2, //Bitmap
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}
