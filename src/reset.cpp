#include <SPI.h>
#include <WiFly.h>

// The GPIO pins on the SPI UART that are connected to WiFly module pins
#define BIT_PIO9  0b00000001 // Hardware factory reset + auto-adhoc
#define BIT_RESET 0b00000010 // Hardware reboot


void setGPIODirection() {
  /*
   */
  SpiSerial.ioSetDirection(BIT_RESET | BIT_PIO9);
}


void hardwareReboot(byte PIO9State = 0) {
  /*
   */
  // NOTE: The WiFly device class implements similar functionality (for reboot
  //       only) but we implement it here slightly differently.
  SpiSerial.ioSetState( (BIT_RESET & ~BIT_RESET) | PIO9State);
  delay(1);
  SpiSerial.ioSetState(BIT_RESET | PIO9State);
}


void readResponse(int timeOut = 0 /* millisecond */) {
  /*
   */

  int target = millis() + timeOut;
  while((millis() < target) || SpiSerial.available() > 0) {
    if (SpiSerial.available()) {
      Serial.write(SpiSerial.read());
    }
  }   
}


#define TOGGLES_REQUIRED 5
#define MS_BETWEEN_TOGGLES 1500

void triggerFactoryReset() {
  /*
   */

  byte state = 0;
  for (int i = 0; i < TOGGLES_REQUIRED; i++) {
    SpiSerial.ioSetState(BIT_RESET | state);  
    state = !state;

    readResponse(MS_BETWEEN_TOGGLES);
  }   
}


void reset_now() {

  Serial.begin(9600);
  Serial.println("WiFly Shield Hardware Factory Reset Tool");
  Serial.println("----------------------------------------");  
  Serial.println();
    
  Serial.println("This sketch will perform the hardware factory reset sequence");
  Serial.println("on the WiFly module on a SparkFun WiFly shield.");
  Serial.println();
  
  Serial.println("Read the sketch documentation for more details.");
  Serial.println();
 
  Serial.println();
  
  // --------------------------
  
  Serial.println("Attempting to connect to SPI UART...");
  SpiSerial.begin();
  Serial.println("Connected to SPI UART.");
  Serial.println();

  Serial.println("Setting GPIO direction.");
  
  setGPIODirection();
  
  Serial.println();
  Serial.println("First reboot to initiate start of factory reset.");
  Serial.println();
  
  hardwareReboot(BIT_PIO9);

  readResponse(1000);

  Serial.println();
  Serial.println("Toggling pin to trigger factory reset.");
  Serial.println();

  triggerFactoryReset();

  Serial.println();  
  Serial.println("Factory reset should now be complete.");  
  Serial.println();
  
  Serial.println("Rebooting for second and final time.");  
  Serial.println();  
  
  hardwareReboot();

  readResponse(1000);

  Serial.println();  
  Serial.println(">> Finished. <<");    

  // --------------------------
  
  Serial.println();
  
  Serial.println(" * Use $$$ (with no line ending) to enter WiFly command mode. (\"CMD\")");
  Serial.println(" * Then send each command followed by a carriage return.");
  Serial.println();
}



