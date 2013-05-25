// memsic 2125 accelerometer x,y UDP blaster
#include "WiFly_helpers.h"
#include "memsic_2125.h"
extern void reset_now();
int woof_count=0;
char udp_message[64];
char count[16]="bogus";


void setup()
{
  Serial.begin(9600);
  setup_2125();
  int success = associate_with_access_point();
}

void loop()
{
  bool good_measurement=false;
  int x,y;

  good_measurement = read_2125(&x,&y);

  sprintf(udp_message,"{\"x\":\"%d\",\"y\":\"%d\"}",x,y);
  Send_UDP_Packet(udp_message);
	Serial.println(udp_message);

  delay(100);

}
