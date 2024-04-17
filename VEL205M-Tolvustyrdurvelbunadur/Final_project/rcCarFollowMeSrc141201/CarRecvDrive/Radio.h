
const uint64_t pipeIn =  0xE8E8F0F0E1LL;

struct MyData {
  byte axis1;
  byte axis2;
  byte axis3;
  byte axis4;
  byte switches;
  float lat;
  float lon;
};

MyData data;

void resetDataAxes() {
  data.axis1 = 127;
  data.axis2 = 127;
  data.axis3 = 127;
  data.axis4 = 127;
  data.switches = 0;
  data.lat = 0;
  data.lon = 0;
  tagLoc.lat = 0;
  tagLoc.lon = 0;
}

RF24 radio(2, 5);

void radio_setup() {
  Serial.println("Radio...");
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);

  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

void radio_loop() {
  static bool haveRadio = false;
  static unsigned long lastRecvTime = 0;

  unsigned long now = millis();
  bool hadRadio = haveRadio;

  while ( radio.available() ) {        
    radio.read(&data, sizeof(MyData));
    lastRecvTime = now;
    haveRadio = true;
    tagLoc.lat = data.lat;
    tagLoc.lon = data.lon;
  }

  if ( now - lastRecvTime > 1000 ) {
    haveRadio = false;
    resetDataAxes();
  }
  
  if ( !hadRadio && haveRadio ) 
    Serial.println("\n***** Gained radio contact *****\n");
  else if ( hadRadio && !haveRadio )
    Serial.println("\n***** Lost radio contact *****\n");
}
