#include <Wire.h>

unsigned char requestedInfo = GPS_NONE;

// This gets called when the master does a write.
void i2c_slave_write_handler(int numBytes)
{
  requestedInfo = Wire.read();
}

// This gets called when the master does a read.
void i2c_slave_read_handler()
{
  switch (requestedInfo) {
  case GPS_COUNT:
    Wire.write((uint8_t*)&gpsInfo.readCount, 8);
    break; 
  case GPS_DATE: 
    Wire.write((uint8_t*)&gpsInfo.year, 4); 
    break;
  case GPS_TIME: 
    Wire.write((uint8_t*)&gpsInfo.hour, 3); 
    break;
  case GPS_LOCATION: 
    Wire.write((uint8_t*)&gpsInfo.lat, 8);
    break;
  }

}

void i2c_setup()
{
  Wire.begin(GPS_I2C_ADDRESS);
  Wire.onReceive(i2c_slave_write_handler);
  Wire.onRequest(i2c_slave_read_handler);
}


