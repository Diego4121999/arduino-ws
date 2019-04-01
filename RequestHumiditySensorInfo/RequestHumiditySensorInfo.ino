#include <Wire.h>

void setup() {
  // join i2c bus (address optional for master)
  Wire.begin(0, 2);
  
  // start serial for output
  Serial.begin(115200);
}

void loop() {
  // start the samplers
  Wire.beginTransmission(0x76);
  Wire.write(0xF2);
  Wire.write(1);
  Wire.endTransmission(1);
  Wire.beginTransmission(0x76);
  Wire.write(0xF4);
  Wire.write(0x27);
  Wire.endTransmission(1);
  // --Temperature Sampling--
  // write the direction in the pointer
  Wire.beginTransmission(0x76);
  Wire.write(0xFA);
  Wire.endTransmission(0);
  // request 1 bytes from slave device #111011X0
  Wire.requestFrom(0x76,3);
  // slave may send less than requested
  while (Wire.available())
  {
    uint8_t tsampMSB = Wire.read();
    uint8_t tsampLSB = Wire.read();
    uint8_t tsampXLSB = Wire.read();
    //join to make the temperature sample
    int32_t temp = (tsampMSB<<12)+(tsampLSB<<4)+(tsampXLSB>>4);
    // print the temperature sampling results
    Serial.printf("Received (temperature sampling): %u\n", temp);
  }
  // --Pressure Sampling--
  Wire.beginTransmission(0x76);
  Wire.write(0xF7);
  Wire.endTransmission(0);
  // request 1 bytes from slave device #111011X0
  Wire.requestFrom(0x76,3);
  // slave may send less than requested
  while (Wire.available())
  {
    uint8_t psampMSB = Wire.read();
    uint8_t psampLSB = Wire.read();
    uint8_t psampXLSB = Wire.read();
    //join to make the temperature sample
    int32_t pressure = (psampMSB<<12)+(psampLSB<<4)+(psampXLSB>>4);
    // print the temperature sampling results
    Serial.printf("Received (pressure sampling): %u\n", pressure);
  }
  // --Humidity Sampling--
  Wire.beginTransmission(0x76);
  Wire.write(0xFD);
  Wire.endTransmission(0);
  // request 1 bytes from slave device #111011X0
  Wire.requestFrom(0x76,2);

  // slave may send less than requested
  while (Wire.available())
  {
    // receive a byte as character
    uint8_t hsampMSB = Wire.read();
    uint8_t hsampLSB = Wire.read();
    // join the 2 bytes together
    uint16_t humid = (hsampMSB<<8)+hsampLSB;
    // print the humidity results
    Serial.printf("Received (humidity sampling): %u\n", humid);
  }
  delay(500);
}
