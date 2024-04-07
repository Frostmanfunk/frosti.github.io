#include <Stepper.h>
////////////////////////////// Define Pins ///////////////////////////////

// Big stepper motor (g.r. )
int PUL_B=7; //define Pulse pin
int DIR_B=6; //define Direction pin

// Medium stepper motor (g.r. 56.7 approx)
int PUL_M = 5;
int DIR_M = 4;

// Small stepper motor (g.r. 1)
int PUL_S = 3;
int DIR_S = 2;

///// Color detector
#define S0 8
#define S1 9
#define S2 10       //Useless
#define S3 11       // Useless
#define sensorOut 12
// Calibration Values
// *Get these from Calibration Sketch
int redMin = 20; // Red minimum value
int redMax = 230; // Red maximum value
// Variables for Color Pulse Width Measurements
int redPW = 0;
// Variables for final Color values
int redValue;


// Heat detector
// Pin code here

///////////////////////////////// Set up //////////////////////////////////
void setup() {
  // Big stepper
  pinMode (PUL_B, OUTPUT);
  pinMode (DIR_B, OUTPUT);
  int gr_1 = 9.1;

  // Medium stepper
  pinMode (PUL_M, OUTPUT);
  pinMode (DIR_M, OUTPUT);
  int gr_2 = 56.7;

  // Small stepper
  pinMode (PUL_S, OUTPUT);
  pinMode (DIR_S, OUTPUT);

  // Color code
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // Setup Serial Monitor
  Serial.begin(9600);
}


///////////////////////////// Loop main code //////////////////////////////////
void loop() {
  int gr_1 = 9.1;
  int gr_2 = 56.7;
  int first_motor = 3/4;
  delay(5000);
  ////////////// Get hold of glas
  Big_motor_down();
  for(int i = 0; i < 6; i++) {
    Small_motor_down();
  }  
  delay(1000);
  Serial.println("Vínglasið er komið í hendurnar.");
  ////////////////// Color code wine
  redPW = getRedPW();   // Read Red value  
  redValue = map(redPW, redMin,redMax,255,0); // Map to value from 0-255 
  delay(200);   // Delay to stabilize sensor

  /////////////////7 Take temperature of wine

  // Print output to Serial Monitor
  Serial.print("Red = ");
  Serial.println(redValue);
  Serial.print("Þú ert að gæða þér á ");
  if (redValue < 0) {
    Serial.println("rauðvíni !!!!!!!!!!!!!!!");
  }
  else {
    Serial.println("hvítvíni.");
  }
  delay(5000);

  ////////////// Lift glas up
  for (int i = 0; i < 3; i++) {
    Medium_motor_up();
  }
  Big_motor_up();
  Serial.println("Vínglasi hefur verið lift up.");
  ///////////// Give a sip
  delay(500);
  for (int i = 0; i < 7; i++) {
    Small_motor_up();
  }
  delay(500);
  for (int i = 0; i < 7; i++) {
    Small_motor_down();
  }
  Serial.println("Búið er að gefa sopa, mmmmm hvað þetta er gott.");
  ///////////// Put glas down
  Big_motor_down();
  delay(1000);
  for (int i = 0; i < 3; i++) {
    Medium_motor_down();
  }
  delay(500);
  for (int i = 0; i < 6; i++) {
    Small_motor_up();
  }
  Serial.println("Glasið er komið aftur á borðið.");
  ////////////// Go back to starting position
  Big_motor_up();
  delay(500);
  //Big_motor_down();
  
  Serial.println("Róbot búinn með sína vinnu. Litgreining í gangi í smá tíma");
  ////////////////// Color code wine
  for (int i = 0; i < 6; i++){
    redPW = getRedPW();   // Read Red value  
    redValue = map(redPW, redMin,redMax,255,0); // Map to value from 0-255 
    delay(200);   // Delay to stabilize sensor

    // Print output to Serial Monitor
    Serial.print("Red = ");
    Serial.println(redValue);
    Serial.print("Þú ert að gæða þér á ");
    if (redValue < 0) {
      Serial.println("rauðvíni !!!!!!!!!!!!!!!");
    }
    else {
      Serial.println("hvítvíni.");
    }
    delay(2000);
  }
  
}
//////////////////////////// Functions ///////////////////////////////////////////////


//////// Motors /////////

// Big motor
int Big_motor_up() {
  int N = floor(6400 * 3/4);
  for (int i=0; i<N; i++) {  //up 5000 steps
    digitalWrite(DIR_B,HIGH);
    digitalWrite(PUL_B,HIGH);
    delayMicroseconds(200);
    digitalWrite(PUL_B,LOW);
    delayMicroseconds(200);
  }
}

void Big_motor_down() {
  int N = floor(6400 * 3/4);
  for (int i=0; i< N ; i++) {  //up 5000 steps
    digitalWrite(DIR_B,LOW);
    digitalWrite(PUL_B,HIGH);
    delayMicroseconds(200);
    digitalWrite(PUL_B,LOW);
    delayMicroseconds(200);
  }
}

// Medium motor
int Medium_motor_up() {
  for (int i=0; i<6400; i++)   //up 5000 steps
  {
    digitalWrite(DIR_M,HIGH);
    digitalWrite(PUL_M,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL_M,LOW);
    delayMicroseconds(100);
  }
}

int Medium_motor_down() {
  for (int i=0; i<6400; i++)   //up 5000 steps
  {
    digitalWrite(DIR_M,LOW);
    digitalWrite(PUL_M,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL_M,LOW);
    delayMicroseconds(100);
  }
}

// Small motor
int Small_motor_up() {
  for (int i=0; i<6400; i++)   //up 5000 steps
  {
    digitalWrite(DIR_S,LOW);
    digitalWrite(PUL_S,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL_S,LOW);
    delayMicroseconds(100);
  }
}

int Small_motor_down() {
  for (int i=0; i<6400; i++)   //up 5000 steps
  {
    digitalWrite(DIR_S,HIGH);
    digitalWrite(PUL_S,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL_S,LOW);
    delayMicroseconds(100);
  }
}

///////// Motors End /////////

///////// Color functions //////////////
// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

/////////// Coloe function ends ////////////
