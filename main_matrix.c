#include <DFRobot_RGBMatrix.h> // Hardware-specific library
#include <Wire.h>
#include <TimeLib.h>
#define OE 9
#define LAT 10
#define CLK 11
#define A A0
#define B A1
#define C A2
#define D A3
#define E A4
#define LOGO16_GLCD_HEIGHT 64
#define LOGO16_GLCD_WIDTH  64

DFRobot_RGBMatrix matrix(A, B, C, D, E, CLK, LAT, OE, false, LOGO16_GLCD_WIDTH, LOGO16_GLCD_HEIGHT);
int targetDay = 15;
int targetMonth = 3;
int targetYear = 2025;
// unsigned long previousMillis = 0; // Stores the last time the task ran
// const unsigned long interval = 15000; // 1 minute in milliseconds
// int i = 0;

void setup() 

{
  Serial.begin(9600);
  matrix.begin();
  matrix.fillScreen(0);//clear the screen
  matrix.setCursor(0,0);
  // setTime(0,0,0,5, 1, 2025);
  // calculateDaysUntil(15,3,2025);

}


// void loop() {
    

//     // Check if 1 minute has passed
//     if (currentMillis - previousMillis >= interval) {
//         previousMillis = currentMillis; // Update the last run time
//         matrix.fillScreen(0);//clear the screen
//         matrix.setCursor(0,0);
//         matrix.setTextColor(matrix.Color333(7,0,4));
//         matrix.print("Wednesday\n1/3/2024\n");
//         matrix.print(currentMillis);
//         matrix.print("\nSnowing");
//         i++;
//     }
// }
void loop() {
  float tempF = 0.0;
  String condition = "N/A";
  if (Serial.available() > 0) {
    // Read the temperature data sent from ESP8266
    String tempData = Serial.readStringUntil('\n');
    Serial.print("Received Data: ");
    Serial.println(tempData);  // Print the received data for debugging

    // Extract temperature (assuming the format is something like "Temperature (C): 22.5")
    // if (tempData.indexOf("Fahrenheit") >= 0) {
    //   condition = tempData.substring(tempData.indexOf(":::"));  // Extract condition
    //   // condition.trim();
    //   // matrix.print("test\n");  // Display condition on the matrix
    // }
    // if (tempData.indexOf("Fahrenheit") >= 0) {
    //   tempF = tempData.substring(tempData.indexOf("::")+2).toFloat();  // Extract temperature in Fahrenheit
    // }
    // displayTemperature(tempF, condition);
    int day = 0;
    int month = 0;
    if(tempData.indexOf(";") >= 0){
      matrix.fillScreen(0);//clear the screen
      matrix.setCursor(0,0);
      matrix.print(tempData.substring(tempData.indexOf(";")+1,tempData.indexOf("Date")));
      matrix.print("\n");
    }      
    if(tempData.indexOf("'") >= 0){
      matrix.print(tempData.substring(tempData.indexOf("2025")+5, tempData.indexOf(" ")));
      day = tempData.substring(tempData.indexOf("2025")+8, tempData.indexOf("2025")+10).toInt();
      month = tempData.substring(tempData.indexOf("2025")+5, tempData.indexOf("2025")+7).toInt();
      setTime(0,0,0,day, month, 2025);
      matrix.print("\n");
    }      
    if(tempData.indexOf(":::") >= 0){
      matrix.print(tempData.substring(tempData.indexOf(":::")+3,tempData.indexOf("Temperature")));
      matrix.print("\n");
    }  
    if (tempData.indexOf("Fahrenheit") >= 0) {
      matrix.print("Temp:" + tempData.substring(tempData.indexOf("::")+2, tempData.indexOf(".")));  // Extract temperature in Fahrenheit
      matrix.print("\n");
    }  
    if (tempData.indexOf("Fahrenheit") >= 0) {
      int daysUntil = calculateDaysUntil(targetDay, targetMonth, targetYear);
      matrix.print("\n\n");
      matrix.print("SB:");
      matrix.print(daysUntil);
      matrix.print("days");
    }

    

  }
  // displayTemperature(20);
  // if (Serial.available() > 0) {
  //   String message = Serial.readString();
  //   Serial.println(message);  // Print the received message
  //   displayTemperature(40);
  // }
}

int calculateDaysUntil(int day, int month, int year) {
    // Convert current and target dates to timestamps
    time_t now1 = now();  // Current timestamp
    time_t target = makeTime(tmElements_t{0, 0, 0, 7, day, month, year - 1970});  // Target timestamp
    // Calculate the difference in seconds and convert to days
    return (target - now1) / 86400;  // 86400 seconds in a day
}
