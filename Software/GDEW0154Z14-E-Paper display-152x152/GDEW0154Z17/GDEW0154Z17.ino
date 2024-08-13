#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <DHT.h> 
//including the bitmap file
#include "thermometer.h"

// select the display class and display driver class in the following file (new style):
#include "GxEPD2_display_selection_new_style.h"

// or select the display constructor line in one of the following files (old style):
#include "GxEPD2_display_selection_added.h"

#define DHTPIN 15 // Pin where the DHT11 is connected
#define DHTTYPE DHT22 // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

void setup() {
  Serial.begin(115200);
  Serial.println("SYSSTART!");
  display.init(115200); 
  delay(1000);
  dht.begin(); 
  drawImage();
  printText();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  displayTemperatureAndHumidity(temp, hum);
  delay(3000);
}

void printText() {
  const char Text[] = "Temp & Hum:";
  display.setRotation(3);
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextColor(GxEPD_BLACK);

  // Calculate text bounds to set partial window correctly
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(Text, 0, 0, &tbx, &tby, &tbw, &tbh);

  // Set a partial window for the title
  display.setPartialWindow(0,10, tbw, tbh); // Adjusted X position
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE); 
    display.setCursor(0, 10 + tbh); 
    display.print(Text);
  } while (display.nextPage());
}
//drawing the Thermometer bitmap
void drawImage() {
  display.setRotation(3);
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(5, 50, epd_bitmap_image__2_, 54, 80, GxEPD_BLACK); // Adjusted position and size
  } while (display.nextPage());
}

//Displaying the Temperature and Humidity data
void displayTemperatureAndHumidity(float temp, float hum) {
  
  display.setRotation(3);
  display.setTextColor(GxEPD_BLACK);

  // Coordinates for the temperature and humidity display
  int16_t xTemp = 70; // Adjusted X position
  int16_t yTemp = 80;  // Adjusted Y position
  int16_t xHum = 70;
  int16_t yHum = 110;

  // Use a partial window to refresh only the area where the temperature and humidity are displayed
  display.setPartialWindow(xTemp, yTemp - FreeMonoBold12pt7b.yAdvance, 80, FreeMonoBold12pt7b.yAdvance * 2 + 10);

  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE); 
    display.setCursor(xTemp, yTemp);
    display.print(temp, 1);
    display.print("C");
    display.println(); 


    display.setCursor(xHum, yHum);
    display.print(hum, 1);
    display.println("%");
  } while (display.nextPage());

}
