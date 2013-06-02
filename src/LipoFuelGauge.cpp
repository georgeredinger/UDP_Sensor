#include "LipoFuelGauge.h"
#include <Wire.h>
#include "Arduino.h"
// Global Variables
#define MAX17043_ADDRESS 0x36  // R/W =~ 0x6D/0x6C

float batVoltage;
float batPercentage;
int alertStatus;
int alertPin = 2;  // This is the alert interrupt pin, connected to pin 2 on the LiPower Shield



/* 
 * i2cRead16(unsigned char address) reads a 16-bit value beginning
 * at the 8-bit address, and continuing to the next address. A 16-bit
 * value is returned.
 * */
unsigned int i2cRead16(unsigned char address)
{
    int data = 0;
		unsigned timeout=0;

    Wire.beginTransmission(MAX17043_ADDRESS);
    Wire.write(address);
    Wire.endTransmission();

    Wire.requestFrom(MAX17043_ADDRESS, 2);
    while (Wire.available() < 2){
			timeout++;
			if(timeout > 65533) 
				 break; //should reset hardware, etc...
		}
    data = ((int) Wire.read()) << 8;
    data |= Wire.read();

    return data;
}

/*
 * i2cWrite16(unsigned int data, unsigned char address) writes 16 bits
 * of data beginning at an 8-bit address, and continuing to the next.
 * */
void i2cWrite16(unsigned int data, unsigned char address)
{
    Wire.beginTransmission(MAX17043_ADDRESS);
    Wire.write(address);
    Wire.write((byte)((data >> 8) & 0x00FF));
    Wire.write((byte)(data & 0x00FF));
    Wire.endTransmission();
}
/*
 * vcellMAX17043() returns a 12-bit ADC reading of the battery voltage,
 * as reported by the MAX17043's VCELL register.
 * This does not return a voltage value. To convert this to a voltage,
 * multiply by 5 and divide by 4096.
 * */


unsigned int vcellMAX17043()
{
    unsigned int vcell;

    vcell = i2cRead16(0x02);
    vcell = vcell >> 4;  // last 4 bits of vcell are nothing

    return vcell;
}

/*
 * percentMAX17043() returns a float value of the battery percentage
 * reported from the SOC register of the MAX17043.
 * */
float percentMAX17043()
{
    unsigned int soc;
    float percent;

    soc = i2cRead16(0x04);  // Read SOC register of MAX17043
    percent = (byte) (soc >> 8);  // High byte of SOC is percentage
    percent += ((float)((byte)soc))/256;  // Low byte is 1/256%

    return percent;
}

/* 
 * configMAX17043(byte percent) configures the config register of
 * the MAX170143, specifically the alert threshold therein. Pass a 
 * value between 1 and 32 to set the alert threshold to a value between
 * 1 and 32%. Any other values will set the threshold to 32%.
 * */
void configMAX17043(byte percent)
{
    if ((percent >= 32)||(percent == 0))  // Anything 32 or greater will set to 32%
        i2cWrite16(0x9700, 0x0C);
    else
    {
        byte percentBits = 32 - percent;
        i2cWrite16((0x9700 | percentBits), 0x0C);
    }
}

/* 
 * qsMAX17043() issues a quick-start command to the MAX17043.
 * A quick start allows the MAX17043 to restart fuel-gauge calculations
 * in the same manner as initial power-up of the IC. If an application's
 * power-up sequence is very noisy, such that excess error is introduced
 * into the IC's first guess of SOC, the Arduino can issue a quick-start
 * to reduce the error.
 * */
void qsMAX17043()
{
    i2cWrite16(0x4000, 0x06);  // Write a 0x4000 to the MODE register
}



void setupLipoFuelGauge(){
     //setup lipo fuel gauge
  pinMode(alertPin, INPUT);
  digitalWrite(alertPin, HIGH);
  Wire.begin();  // Start I2C
  delay(100);
  configMAX17043(32);  // Configure the MAX17043's alert percentage
  qsMAX17043();  // restart fuel-gauge calculations
}
int getLiPoStatus() {
    batPercentage = percentMAX17043();
    batVoltage = (float) vcellMAX17043() * 1/800;  // vcell reports battery in 1.25mV increments
    alertStatus = digitalRead(alertPin);

//    Serial.print(batPercentage, 2);  // Print the battery percentage
//    Serial.println(" %");
//    Serial.print(batVoltage, 2);  // print battery voltage
//    Serial.println(" V");
//    Serial.print("Alert Status = ");
//    Serial.println(alertStatus, DEC);
//    Serial.println();
    return batPercentage;
}


