// ADXL345 x,y,z accelerometer
// MAX17043 lipo fuel gauge
// Roving Networks WiFly shield WRL-09954 
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_ADXL345.h"
#include "LipoFuelGauge.h"
#include "WiFly_helpers.h"

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345 accel = Adafruit_ADXL345(12345);
 
 
long last_battery_report=0L;

char *ftoa(char *a, double f, int precision)
{
	long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};
	char *ret = a;
	long heiltal = (long)f;
	itoa(heiltal, a, 10);
	while (*a != '\0') a++;
	*a++ = '.';
	long desimal = abs((long)((f - heiltal) * p[precision]));
	itoa(desimal, a, 10);
	return ret;
}


void setup()
{
  Serial.begin(57600); 
  Serial.println(("BEGIN")); 
//  setupLipoFuelGauge();

//  if(!accel.begin())
//  {
//    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
//    while(1);
//  }

 // if(!associate_with_access_point()) {
 //   Serial.println("WiFi association failed");
 // } else {
 // 	Serial.println("WiFi association success");
 // }
// associate_with_access_point();
}
void loop()
{
    bool good_measurement=false;
//    char  xs[16],ys[16],zs[16],volts[16];
    //sensors_event_t event; 
    char udp_message[16];
    int this_minute;
    unsigned long now = millis() / 1000L;
    
    //accel.getEvent(&event);

//    sprintf(udp_message,"{\"t\":\"%lu\",\"x\":\"%s\",\"y\":\"%s\",\"z\":\"%s\"}\r\n"
//            ,now
//            ,ftoa(xs,event.acceleration.x,2)
//            ,ftoa(ys,event.acceleration.y,2)
//            ,ftoa(zs,event.acceleration.z,2)
//           );
// sprintf(udp_message,"{\"t\":\"%lu\",\"x\":\"%s\",\"y\":\"%s\",\"z\":\"%s\"}\r\n"
//            ,now
//            ,"1"
//            ,"2"
//            ,"3"
//           );
//
//sprintf(udp_message,"%lu",now);
//    Send_UDP_Packet(udp_message);
    //Serial.println(udp_message);

//   delay(5000);
//   Serial.println(udp_message);
}


