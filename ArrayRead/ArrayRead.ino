#include <Wire.h>

void setup() {
  // join i2c bus (address optional for master)
  Wire.begin(0, 2);
  // start serial for output
  Serial.begin(115200);
  // start the samplers
  Wire.beginTransmission(0x76);
  Wire.write(0xF2);
  Wire.write(1);
  Wire.write(0xF4);
  Wire.write(0x27);
  // write the starting directory on the pointer
  Wire.write(0xF7);
  Wire.endTransmission(0);
}

void loop() {
  // request the data from the directories
  static uint8_t arr[128];
  uint16_t arr_i=0;
  Wire.requestFrom(0x76,8);
  if (Wire.available()<=8){
    while(Wire.available()){
      arr[arr_i++]=Wire.read();
    }
  }
  delay(1000);
}
