#include <Wire.h>
 static uint8_t arr[8];

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

uint32_t mountvar(uint16_t pos,uint8_t flag){
  static uint32_t cont;
  if (flag=2){
    cont=(arr[pos]<<8)+arr[pos+1];
  }
  if (flag=3){
    cont=((arr[pos]<<16)+(arr[pos+1]<<8)+arr[pos+2])>>4;
  }
  return cont;
}

void loop() {
  // request the data from the directories
  uint16_t arr_i=0;
  Wire.requestFrom(0x76,8);
  if (Wire.available()<=8){
    while(Wire.available()){
      arr[arr_i++]=Wire.read();
    }
  }
  Serial.printf("Pressure: %u\n",mountvar(1,3));
  Serial.printf("Temperature: %u\n",mountvar(4,3));
  Serial.printf("Humidity: %u\n -----------------\n",mountvar(7,2));
  delay(1000);
}
