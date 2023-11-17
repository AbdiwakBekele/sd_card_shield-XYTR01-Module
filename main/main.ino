#include <SPI.h>
#include <SD.h>

File dataFile;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing SD..");

  pinMode(10, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    return;
  } else {
    Serial.println("Initilization Done");
    delay(500);
    dataFile = SD.open("sensor.csv", FILE_WRITE);
    if (dataFile) {
      Serial.println("Writing to SD");
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

  // Calculate hours, minutes, and seconds
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  // Extract individual components
  int secondsValue = seconds % 60;
  int minutesValue = minutes % 60;
  int hoursValue = hours % 24;

  String timeString = String(hoursValue) + ":" + String(minutesValue) + ":" + String(secondsValue);

  
    if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n'); // Read until newline character
  
      // Find the positions of commas in the string
      int firstComma = data.indexOf(',');
  
      // Extract substrings based on comma positions
      String temperatureStr = data.substring(0, firstComma);
      String humidityStr = data.substring(firstComma + 1);
  
      // Convert temperature and humidity to float
      float temperature = temperatureStr.toFloat();
      float humidity = humidityStr.toFloat();

      Serial.print(timeString);
      Serial.print(",");
      Serial.print(temperature);
      Serial.print(",");
      Serial.println(humidity);
  
      // Write data to the CSV file
      dataFile.print(timeString);
      dataFile.print(",");
      dataFile.print(temperature, 2); // Adjust the number of decimal places as needed
      dataFile.print(",");
      dataFile.println(humidity, 2);
  
      dataFile.flush();

      // Add a delay to avoid reading too fast and to allow time for other operations
    delay(60000);
    }
  
    
}


