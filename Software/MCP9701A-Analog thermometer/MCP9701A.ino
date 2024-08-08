//Variables
const int numReadings = 10;

int readings[numReadings];  
int readIndex = 0;          // the index of the current reading
int total = 0;              

int averageValue = 0;           // the average
int oldValue = 0;
int storedValue = 0; 
int delta = 1;            // 0.2C per 1 - difference 

float voltage = 0;

int state = 0; 
float tempvalue = 0;

float ATStemp = 0;

//Pin definition
int AIN0 = 0; 


void setup() {

  Serial.begin(9600);
  delay(1000);       //Serial display start up
  Serial.println("SYSSTART!"); 

  for (int thisReading = 0; thisReading < numReadings; thisReading++) { 
    readings[thisReading] = 0;
  }

  pinMode(LED_BUILTIN,OUTPUT);

  }

void loop() {

 //Indicator that the Raspberry Pi Pico is working
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);                   
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);

  //Function calling
  ATSaverage();
}




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

  delay(500);

}
