#include <Arduino.h>

RTC_DATA_ATTR int rtcPersist = 0; // Prototype for storing information in persistant RTC mem

// put function declarations here:
int myFunction(int, int);

// Setup runs on every wake!!
void setup() {
  // Set target rainfall amount (server will handle the logic and pass a number)
  // Create irrEvent object Object needs to return an array of irrigation OR have runZone function that handles 
  // pinmode based on int passed to function. Protoype: runZone(zone=1,gpio=1) 

  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  // What time does irrigation start? // TODO: Logic to handle multiple irrigation events each day
  // After irrigation runs, calculate next irrigation time (Maybe the server delivers this?)
  // Sleep until nextWake
}

void loop() {
  // Do we even need a loop? What goes here?  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}