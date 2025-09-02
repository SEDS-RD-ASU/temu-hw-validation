# TEMU Flight Computer HW Validation
<br>

<div align="center">
  <img src="img/temu.png" alt="TEMU Logo" width="200" height="auto">
</div>

<br>

<div align="center">
  <img src="img/image.png" alt="TEMU Flight Computer Setup" style="border: 3px solid black; border-radius: 8px;">
</div>

The TEMU flight computer is a cheap, easy to produce avionics systems designed to each undergraduates the fundamentals of flight computer hardware and software design.

<br>

The flight computer consists of the following:
* Arduino Nano Clone (Old Bootloader)
* GY-91 Breakout Board
    * MPU6500 I2C Accelerometer and Gyroscope
    * BMP280 I2C Barometer
* AT24C256 I2C EEPROM
* Buzzer
* Two MOSFETs (PYR1 and PYR2)
* Terminal Block
* Various pull-up and pull-down resistors
* Capacitor between VIN and GND

<br>

**Ideal console output:**

```
--- BEGINNING TEMU HW VALIDATION ---



--- BUZZER TEST ---

Playing tones...
Tones played!



--- I2C SCAN ---

Nominal I2C Addresses: 0x50, 0x68, 0x76.

Scanning...
I2C device found at address 0x50
I2C device found at address 0x68
I2C device found at address 0x76
I2C Scan Done!!




--- Accelerometer and Gyroscope Data ---
Accel X, Accel Y, Accel Z, Gyro X, Gyro Y, Gyro Z, Temp
0.07    -0.01   1.02    2.08    1.16    -0.73   29.79
0.08    -0.02   1.01    2.08    1.28    -0.79   29.79
0.08    -0.02   1.01    2.20    1.04    -0.85   29.79
0.08    -0.01   1.01    2.32    1.28    -0.92   29.77
0.08    -0.01   1.01    2.14    1.16    -0.85   29.77
0.08    -0.02   1.02    1.89    1.10    -0.79   29.79
0.08    -0.02   1.01    2.20    1.22    -0.92   29.76
0.07    -0.02   1.01    2.32    1.04    -0.85   29.78
0.07    -0.02   1.01    2.01    1.16    -0.85   29.77
0.08    -0.02   1.01    2.01    1.46    -0.85   29.81



--- Barometer Data ---
Pressure, Temperature
Temperature: 27.69°C    Pressure: 96849Pa
Temperature: 27.69°C    Pressure: 96850Pa
Temperature: 27.69°C    Pressure: 96850Pa
Temperature: 27.69°C    Pressure: 96850Pa
Temperature: 27.68°C    Pressure: 96849Pa
Temperature: 27.68°C    Pressure: 96849Pa
Temperature: 27.69°C    Pressure: 96849Pa
Temperature: 27.69°C    Pressure: 96849Pa
Temperature: 27.69°C    Pressure: 96849Pa
Temperature: 27.69°C    Pressure: 96848Pa



--- EEPROM TEST ---

Memory detected!
Mem size in bytes: 32768
I read (should be 200): 200
I read (should be -366): -366
I read (should be -7.35): -7.35
I read: Hi, I am just a simple test string
Next available EEPROM location: 65



End of validation!!!
```