#include "DHT.h"

// Define the pin where the DHT11 data pin is connected
#define DHTPIN 14

// Define the type of DHT sensor
#define DHTTYPE DHT11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Number of readings to average
#define NUM_READINGS 10

// Arrays to store temperature and humidity readings
float temperatureReadings[NUM_READINGS];
float humidityReadings[NUM_READINGS];
int readIndex = 0;
float totalTemp = 0;
float totalHumidity = 0; 
float averageTemp = 0; 
float averageHumidity = 0; 
float lastPrintedAverageTemp = 0; 
float lastPrintedAverageHumidity = 0; 

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Start the DHT sensor
  dht.begin();

  // Initialize all readings to 0
  for (int i = 0; i < NUM_READINGS; i++) {
    temperatureReadings[i] = 0;
    humidityReadings[i] = 0;
  }
}

void loop() {
  // Read the temperature and humidity from the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if the readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Update temperature readings
  totalTemp -= temperatureReadings[readIndex];
  temperatureReadings[readIndex] = temperature;
  totalTemp += temperature;

  // Update humidity readings
  totalHumidity -= humidityReadings[readIndex];
  humidityReadings[readIndex] = humidity;
  totalHumidity += humidity;

  // Advance to the next index, wrapping around if necessary
  readIndex = (readIndex + 1) % NUM_READINGS;

  // Calculate the average temperature and humidity
  averageTemp = totalTemp / NUM_READINGS;
  averageHumidity = totalHumidity / NUM_READINGS;

  // Print the average temperature and humidity to the serial monitor if there is a change
  if (averageTemp != lastPrintedAverageTemp || averageHumidity != lastPrintedAverageHumidity) {
    Serial.print("Temperature: ");
    Serial.print(averageTemp);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(averageHumidity);
    Serial.println(" %");

    lastPrintedAverageTemp = averageTemp;
    lastPrintedAverageHumidity = averageHumidity;
  }

  // Wait a few seconds before the next reading
  delay(2000);
}
