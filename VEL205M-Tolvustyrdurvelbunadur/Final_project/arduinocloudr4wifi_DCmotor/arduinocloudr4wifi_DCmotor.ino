/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/618ec156-6f9d-4048-9adc-63dc3e1cb716 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  bool dcMotor;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#define dcmotor1 13 //IN1 of the Driver
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  pinMode(dcmotor1, OUTPUT);
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  
  
}


/*
  Since DcMotor is READ_WRITE variable, onDcMotorChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onDcMotorChange()  {
  // Add your code here to act upon DcMotor change
  if(dcMotor == 1){
    digitalWrite(dcmotor1, HIGH);
  }
  else {digitalWrite(dcmotor1, LOW);}
}