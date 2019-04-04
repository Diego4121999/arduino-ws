/*load libraries*/
#include "SparkFunBME280.h"
#include "Wire.h"

#define SLAVE_ADDRESS 0x76
/*define the chip as an object*/
BME280 BME280_chip;

void setup() {
  /*start the serial*/
  Serial.begin(115200);
  /*join the I2C port and set to 400kHz*/
  Wire.begin(0,2);
  Wire.setClock(400000);
  /*Change the sensor to I2C mode and address it*/
  BME280_chip.settings.commInterface = I2C_MODE;
  BME280_chip.settings.I2CAddress = SLAVE_ADDRESS;
  /*Make the sensor run in normal mode*/
  BME280_chip.settings.runMode = 3;
  /*Set the standby time to minimum to maximize sampling frequency*/
  BME280_chip.settings.tStandby = 0;
  /*Set the noise filter to be stopped*/
  BME280_chip.settings.filter = 0;
  /*Set the oversampling of the sensors to 1*/
  BME280_chip.settings.tempOverSample = 1;
  BME280_chip.settings.pressOverSample = 1;
  BME280_chip.settings.humidOverSample = 1;
  /*Make sure the sensors have time to setup properly*/
  delay(10);
  /*Start the sensor*/
  BME280_chip.begin();
  /* Check communication before continue */
  if (BME280_chip.beginI2C(Wire) == false)
  {
    Serial.printf("The sensor did not respond. Please check wiring.\n");
    /* Stop here (WDT will reset at some point) */
    while(1);
  }
}

void loop() {
  float Temp=BME280_chip.readTempC();
  float Press=BME280_chip.readFloatPressure();
  Serial.printf("----------\n"
  "Temperature: %f\n"
  "Pressure: %f\n",Temp,Press);
  delay(1000);
}
