char command;


void setup() {
  pinMode(2, OUTPUT);    // in1 (left motors forward)
  pinMode(3, OUTPUT);    // in2 (left motors reverse)
  pinMode(4, OUTPUT);    // in3 (right motors forward)
  pinMode(5, OUTPUT);    // in4 (right motors reverse)
  pinMode(9, OUTPUT);    // ENA (PWM pin for left motors)
  pinMode(10, OUTPUT);   // ENB (PWM pin for right motors)

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();
    Serial.println(command);
    
    // Perform actions based on received command
    if (command == 'F') {    // move forward (all motors rotate in forward direction)
      forward();
    } else if (command == 'B') {    // move backward (all motors rotate in reverse direction)
      backward();
    } else if (command == 'L') {    // turn left
      left();
      delay(400);  // Delay to complete the turn
      stop();
    } else if (command == 'R') {    // turn right
      right();
      delay(400);  // Delay to complete the turn
      stop();
    } else if (command == 'S') {    // STOP (all motors stop)
      stop();
    }
  }
  delay(100);
}

void right() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(9, 255);    // Set maximum speed for left motors
  analogWrite(10, 255);   // Set maximum speed for right motors
}

void left() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  analogWrite(9, 255);    // Set maximum speed for left motors
  analogWrite(10, 255);   // Set maximum speed for right motors
}

void backward() {
  digitalWrite(2, HIGH);    // Left motors forward
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);     // Right motors reverse
  digitalWrite(5, HIGH);
  analogWrite(9, 255);    // Set maximum speed for left motors
  analogWrite(10, 255);   // Set maximum speed for right motors
}

void forward() {
  digitalWrite(2, LOW);     // Left motors reverse
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);    // Right motors forward
  digitalWrite(5, LOW);
  analogWrite(9, 255);    // Set maximum speed for left motors
  analogWrite(10, 255);   // Set maximum speed for right motors
}

void stop() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  analogWrite(9, 0);    // Disable left motors
  analogWrite(10, 0);   // Disable right motors
}