#include <Arduino.h>
#include <Wire.h>
#include <FastIMU.h>
#include <AT24C256.h>
#include <BMP280.h>

// IMU Setup ------------------------------------------------------------

#define IMU_ADDRESS 0x68    
MPU6500 IMU;

calData calib = { 0 };  // calibration data

AccelData accelData; // accel data storage
GyroData gyroData; // gyro data storage

// BMP Setup ------------------------------------------------------------

BMP280 bmp280(0x76);

void setup() {

    // INITIALIZE SERIAL

    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    
    // INITIALIZE I2C ------------------------------------------------------------

    Wire.begin();
    Wire.setClock(400000); //400khz clock

    

    // INITIALIZE IMU ------------------------------------------------------------
  
    int err = IMU.init(calib, IMU_ADDRESS);
    if (err != 0) {
      Serial.print("Error initializing IMU: ");
      Serial.println(err);
      while (true) {
        ;
      }
    }

    if (err != 0) {
        Serial.print("Error Setting range: ");
        Serial.println(err);
        while (true) {
          ;
        }
    }

    // INITIALIZE BMP280 ------------------------------------------------------------

    bmp280.begin();

    // INITIALIZE BUZZER ------------------------------------------------------------

    pinMode(12, OUTPUT);

    // SETUP IS DONE!!!! NOW FOR THE VALIDATION!!!

    Serial.print("\n\n\n");
    Serial.print("\n\n\n");

    Serial.println("--- BEGINNING TEMU HW VALIDATION ---");

    delay(1000);
    Serial.print("\n\n\n");

    // BUZZER TEST ------------------------------------------------------------

    Serial.println("--- BUZZER TEST ---");
    Serial.println();

    Serial.println("Playing tones...");
    tone(12, 500, 200); // 500 Hz tone for 200ms
    delay(250);
    tone(12, 1000, 200); // 1 kHz tone for 200ms
    delay(250);
    tone(12, 1500, 200); // 1.5 kHz tone for 200ms
    delay(250);
    noTone(12);
    delay(500);
    Serial.println("Tones played!");

    delay(1000);
    Serial.print("\n\n\n");

    // I2C SCAN ------------------------------------------------------------

    Serial.println("--- I2C SCAN ---");
    Serial.println();

    byte error, address;
    int nDevices;
  
    Serial.println("Scanning...");
  
    nDevices = 0;
    for(address = 1; address < 127; address++ )
    {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
  
      if (error == 0)
      {
        Serial.print("I2C device found at address 0x");
        if (address<16)
          Serial.print("0");
        Serial.print(address,HEX);
        Serial.println("  !");
  
        nDevices++;
      }
      else if (error==4)
      {
        Serial.print("Unknown error at address 0x");
        if (address<16)
          Serial.print("0");
        Serial.println(address,HEX);
      }
    }
    if (nDevices == 0)
      Serial.println("No I2C devices found\n");
    else
      Serial.println("done\n");
    
    delay(1000);
    Serial.print("\n\n\n");

    // IMU Data ------------------------------------------------------------
    
    Serial.println("--- Accelerometer and Gyroscope Data ---");
    Serial.println("Accel X, Accel Y, Accel Z, Gyro X, Gyro Y, Gyro Z, Temp");

    for (int i = 0; i < 10; i++) {
        IMU.update();
        IMU.getAccel(&accelData);
        Serial.print(accelData.accelX);
        Serial.print("\t");
        Serial.print(accelData.accelY);
        Serial.print("\t");
        Serial.print(accelData.accelZ);
        Serial.print("\t");
        IMU.getGyro(&gyroData);
        Serial.print(gyroData.gyroX);
        Serial.print("\t");
        Serial.print(gyroData.gyroY);
        Serial.print("\t");
        Serial.print(gyroData.gyroZ);
        if (IMU.hasTemperature()) {
            Serial.print("\t");
            Serial.println(IMU.getTemp());
        }
        else {
        Serial.println();
        }
        delay(50);
    }

    delay(1000);
    Serial.print("\n\n\n");

    // BAROMETER DATA ------------------------------------------------------------

    Serial.println("--- Barometer Data ---");
    Serial.println("Pressure, Temperature");

    for (int i = 0; i < 10; i++) {
        uint32_t pressure = bmp280.getPressure();
        float temperature = bmp280.getTemperature();

        //Print the results
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print("°C \t");
        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println("Pa");
        delay(50);
    }

    delay(1000);
    Serial.print("\n\n\n");

    // END OF VALIDATION ------------------------------------------------------------
    Serial.println("End of validation!!!");
}

void loop() {

}