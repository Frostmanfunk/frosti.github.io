/*!
 * @file  DRI0043.ino
 * @brief TB6600 arduino Stepper Motor Driver is an easy-to-use professional stepper motor driver, which could control a two-phase stepping motor.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  DFRobot
 * @version  V1.0
 * @date  2023-08-03
 */

int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
//int ENA=5; //define Enable Pin
void setup() {
  delay(5000);
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  // pinMode (ENA, OUTPUT);

}

void loop() {
  for (int j = 0; j<2;j++)
  {
    for (int i=0; i< 6400; i++)    //Forward 5000 steps
    {
      digitalWrite(DIR,HIGH);
    // digitalWrite(ENA,HIGH);
      digitalWrite(PUL,HIGH);
      delayMicroseconds(100);
      digitalWrite(PUL,LOW);
      delayMicroseconds(100);
    }
  }
  delay(1000);
  for (int i=0; i<6400; i++)   //Backward 5000 steps
  {
    digitalWrite(DIR,LOW);
    //digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);
  }
  delay(5000);
}