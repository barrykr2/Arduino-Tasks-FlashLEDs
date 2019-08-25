/*
 * Example of using Petr Stehlik's Tasker for Arduino (petr @ pstehlik.cz).
 * This example is written by Barry Kruyssen (barry @ redfoxcottage.net) using 
 * Visual Studio Code with PlatformIO for an esp32 board.
 */

#include <Arduino.h>
#include "Tasker.h"
#include "FlashLEDs.h"

#pragma region "Constants for pin allocations"
const int pinBuiltInLED = 2;
const int pinGreenLED = 18;
const int pinRedLED = 19;
#pragma endregion //"Constants for pin allocations"

#pragma region "Sketch constants"
const int statusLEDonMills = 100;       // 1/10th of a second
const int statusLEDoffMills = 100;      // 1/10th of a second
const int statusLEDnumberOfFlashes = 2; // number of flashes in loop
const int statusLEDloopMills = 3000;    // loop every 3 seconds

const int greenLEDonMills = 200;        // 1/5th of a second
const int greenLEDoffMills = 100;       // 1/10th of a second
const int greenLEDnumberOfFlashes = 5;  // number of flashes in loop
const int greenLEDloopMills = 4000;     // loop every 4 seconds

const int redLEDonMills = 5000;         // 5 seconds
const int redLEDoffMills = 0;           // no seconds
const int redLEDnumberOfFlashes = 1;    // number of flashes in loop
const int redLEDloopMills = 10000;      // loop every 10 seconds
#pragma endregion //Sketch constants"

#pragma region "Library definitions"
Tasker tasker;
arfcFlashLEDs flashLEDs;
#pragma endregion //"Library definitions"

#pragma region "Define structures and types"
/*typedef struct {
  int setInterval;
  int flashCount;
} rtnFlashLED;
*/
#pragma endregion //"Define structures and types"

#pragma region "Logic functions"
/*
// function to flash LED X times in every Y milliseconds for Z milliseconds.
rtnFlashLED flashLED(int LEDpin, int LEDonMills, int LEDoffMills, int LEDnumberOfFlashes, int LEDloopMills, int flashCount){
  int isHigh = digitalRead(LEDpin);
  int setHighLow;
  int setInterval;
  rtnFlashLED returnData;

  if (isHigh != HIGH) {
    setHighLow = HIGH;
    setInterval = LEDonMills;
    flashCount++;
  } else {
    setHighLow = LOW;
    if (flashCount < LEDnumberOfFlashes) {
      setInterval = LEDoffMills;
    } else {
      setInterval = LEDloopMills - (LEDnumberOfFlashes * LEDonMills) - ((LEDnumberOfFlashes - 1) * LEDoffMills);
      flashCount = 0;  // reset flash count
    }
  }

  digitalWrite(LEDpin, setHighLow);
  
  returnData.flashCount = flashCount;
  returnData.setInterval = setInterval;
  return returnData;
}
*/
#pragma endregion // "Logic functions"

#pragma region "Task scheduled functions"
// function to flash status LED
void taskStatusLED(){
  static int flashCount;
  rtnFlashLED returnedData = flashLEDs.flashLED(pinBuiltInLED, statusLEDonMills, statusLEDoffMills, statusLEDnumberOfFlashes, statusLEDloopMills, flashCount);
  flashCount = returnedData.flashCount;
  tasker.setInterval(taskStatusLED, returnedData.setInterval);  
}

// function to flash Greeen LED
void taskGreenLED(){
  static int flashCount;
  rtnFlashLED returnedData = flashLEDs.flashLED(pinGreenLED, greenLEDonMills, greenLEDoffMills, greenLEDnumberOfFlashes, greenLEDloopMills, flashCount);
  flashCount = returnedData.flashCount;
  tasker.setInterval(taskGreenLED, returnedData.setInterval);  
}

// function to flash Red LED
void taskRedLED(){
  static int flashCount;
  rtnFlashLED returnedData = flashLEDs.flashLED(pinRedLED, redLEDonMills, redLEDoffMills, redLEDnumberOfFlashes, redLEDloopMills, flashCount);
  flashCount = returnedData.flashCount;
  tasker.setInterval(taskRedLED, returnedData.setInterval);  
}
#pragma endregion //"Task scheduled functions"

#pragma region "Initialisation functions"
// Initialise all tasks, there can be multiple tasks scheduled.
void Init_Tasks() {
  tasker.setInterval(taskStatusLED, statusLEDonMills);
  tasker.setInterval(taskGreenLED, greenLEDonMills);
  tasker.setInterval(taskRedLED, redLEDonMills);
}

void Init_Pins() {
  // Initialise pin modes
  pinMode(pinBuiltInLED, OUTPUT);
  pinMode(pinGreenLED, OUTPUT);
  pinMode(pinRedLED, OUTPUT);
}
#pragma endregion // "Initialisation functions"

void setup() {
  Init_Pins();      // Initialise pins
  Init_Tasks();     // Initialise all tasks
}

void loop() {
  // put your main code here, to run repeatedly:

  tasker.loop();        // run any tasks that are scheduled to run
}