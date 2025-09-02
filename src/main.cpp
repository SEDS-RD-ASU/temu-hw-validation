#include <Arduino.h>
#include <Wire.h>
#include <FastIMU.h>
#include <BMP280.h>
#include <Sparkfun_External_EEPROM.h>

// IMU Setup ------------------------------------------------------------

#define IMU_ADDRESS 0x68    
MPU6500 IMU;

calData calib = { 0 };  // calibration data

AccelData accelData; // accel data storage
GyroData gyroData; // gyro data storage

// BMP Setup ------------------------------------------------------------

BMP280 bmp280(0x76);

// EEPROM Setup ------------------------------------------------------------

ExternalEEPROM eepromChip;




// Entry Point ------------------------------------------------------------

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

    // INITIALIZE EEPROM ------------------------------------------------------------

    eepromChip.setMemoryType(256);

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
    Serial.println("Nominal I2C Addresses: 0x50, 0x68, 0x76.");
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
        Serial.println();
  
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
      Serial.println("I2C Scan Done!!\n");
    
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

    // EEPROM TEST ------------------------------------------------------------

    Serial.println("--- EEPROM TEST ---");
    Serial.println();

    if (eepromChip.begin() == false)
    {
      Serial.println("No memory detected. Freezing.");
      while (true)
        ;
    }

    Serial.println("Memory detected!");

    Serial.print("Mem size in bytes: ");
    Serial.println(eepromChip.length());

    //Yes you can read and write bytes, but you shouldn't!
    byte myValue1 = 200;
    eepromChip.write(0, myValue1); //(location, data)

    byte myRead1 = eepromChip.read(0);
    Serial.print("I read (should be 200): ");
    Serial.println(myRead1);

    //You should use gets and puts. This will automatically and correctly arrange
    //the bytes for larger variable types.
    int myValue2 = -366;
    eepromChip.put(10, myValue2); //(location, data)
    int myRead2;
    eepromChip.get(10, myRead2); //location to read, thing to put data into
    Serial.print("I read (should be -366): ");
    Serial.println(myRead2);

    float myValue3 = -7.35;
    eepromChip.put(20, myValue3); //(location, data)
    float myRead3;
    eepromChip.get(20, myRead3); //location to read, thing to put data into
    Serial.print("I read (should be -7.35): ");
    Serial.println(myRead3);

    String myString = "Hi, I am just a simple test string";
    unsigned long nextEEPROMLocation = eepromChip.putString(30, myString);
    String myRead4 = "";
    eepromChip.getString(30, myRead4);
    Serial.print("I read: ");
    Serial.println(myRead4);
    Serial.print("Next available EEPROM location: ");
    Serial.println(nextEEPROMLocation);
    
    delay(1000);
    Serial.print("\n\n\n");

    // END OF VALIDATION ------------------------------------------------------------
    Serial.println("End of validation!!!");
}

void loop() {
  // do nothing here lol
}