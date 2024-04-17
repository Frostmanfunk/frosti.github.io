
void setup()
{
  Serial.begin(9600);
  i2c_setup();
  gps_setup();
}

void loop()
{
  gps_loop();
}


