#include <SPI.h>
#include <SD.h>
#include <DHT.h>

#define DHTPIN 2 // Digital pin connected to the DHT11 sensor
#define DHTTYPE DHT22 // DHT11 sensor type

// Initialize the DHT sensor library
DHT dht(DHTPIN, DHTTYPE);

File dataFile;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing SD Card..");
  delay(1000);
  dht.begin();
  Serial.println("Initializing Humidity & Temprature Sensor...");

  pinMode(10, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    return;
  } else {
    Serial.println("Initilization Done");
    delay(500);
    dataFile = SD.open("sensor.csv", FILE_WRITE);
    if (dataFile) {
      Serial.println("Saving data to SD");
      dataFile.print("Date Time");
      dataFile.print(",");
      dataFile.print("Temprature"); // Adjust the number of decimal places as needed
      dataFile.print(",");
      dataFile.println("Humidity");
  
      dataFile.flush();
    } else {
      Serial.println("Failed to write to SdCrar");
    }
  }
}


void loop() {

  unsigned long currentMillis = millis();

  // Read the temperature and humidity from the sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();


    // Check if any reads failed and exit early
if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read sensor!");
    return;
  }

 
  // Calculate hours, minutes, and seconds
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  // Extract individual components
  int secondsValue = seconds % 60;
  int minutesValue = minutes % 60;
  int hoursValue = hours % 24;

  String timeString = String(hoursValue) + ":" + String(minutesValue) + ":" + String(secondsValue);

      Serial.print("Date-Time: ");
      Serial.print(timeString);
      Serial.print("\t");
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println("°C\t");
  
  
      // Write data to the CSV file
      dataFile.print(timeString);
      dataFile.print(",");
      dataFile.print(temperature, 2); // Adjust the number of decimal places as needed
      dataFile.print(",");
      dataFile.println(humidity, 2);
  
      dataFile.flush();

      // Add a 10 min delay to avoid reading too fast and to allow time for other operations
    delay(600000);
   
  
    
}
