#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
const int baudRate = 9600;

File dataFile;

void setup() {
  Serial.begin(baudRate);

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  } else {
    Serial.println("Card Present");
  }

  dataFile = SD.open("sensorData.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Failed to create data file");
    return;
  }

  dataFile.println("Date,Time,Temperature,Humidity");
}

void loop() {
  //  if (Serial.available() > 0) {
  //    String data = Serial.readStringUntil('\n'); // Read until newline character
  //
  //    // Find the positions of commas in the string
  //    int firstComma = data.indexOf(',');
  //    int secondComma = data.indexOf(',', firstComma + 1);
  //    int thirdComma = data.indexOf(',', secondComma + 1);
  //
  //    // Extract substrings based on comma positions
  //    String date = data.substring(0, firstComma);
  //    String time = data.substring(firstComma + 1, secondComma);
  //    String temperatureStr = data.substring(secondComma + 1, thirdComma);
  //    String humidityStr = data.substring(thirdComma + 1);
  //
  //    // Convert temperature and humidity to float
  //    float temperature = temperatureStr.toFloat();
  //    float humidity = humidityStr.toFloat();
  //
  //    // Write data to the CSV file
  //    dataFile.print(date);
  //    dataFile.print(",");
  //    dataFile.print(time);
  //    dataFile.print(",");
  //    dataFile.print(temperature, 2); // Adjust the number of decimal places as needed
  //    dataFile.print(",");
  //    dataFile.println(humidity, 2);
  //
  //    dataFile.flush();
  //  }
  //
  //  // Add a delay to avoid reading too fast and to allow time for other operations
  //  delay(100);
}

//void closeFile() {
//  dataFile.close();
//}

