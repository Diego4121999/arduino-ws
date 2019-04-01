#include <Wire.h>

void setup() {
  // join i2c bus (address optional for master)
  Wire.begin(0, 2);
  
  // start serial for output
  Serial.begin(115200);
}

void loop() {
  // write the direction in the pointer
  Wire.beginTransmission(0x76);
  Wire.write(0xD0);
  Wire.endTransmission(0);
  // request 1 bytes from slave device #111011X0
  Wire.requestFrom(0x76,1);

  // slave may send less than requested
  while (Wire.available())
  {
    // receive a byte as character
    char c = Wire.read();

    // print the character
    Serial.printf("Received: %02X\n", c);
  }
  delay(500);
}
