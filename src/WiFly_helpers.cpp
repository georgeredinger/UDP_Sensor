#include "WiFly.h"
#include "Credentials.h"

extern void reset_now();

void echo() {
    delay(500);
    while(SpiSerial.available() > 0) {
        Serial.print((char)SpiSerial.read());
    }
}

void Send_UDP_Packet(char *udp_message){
  SpiSerial.print(udp_message); 
}

int associate_with_access_point() {
  char ssid_cmd[64] = "set wlan ssid "; 
  char phrase_cmd[64] = "set wlan phrase " ;
  char join_cmd[64] =  "join ";

  strcat(ssid_cmd,ssid);
  strcat(phrase_cmd,passphrase);
  strcat(join_cmd,ssid);
  //reset_now(); // allways start with factory defaults to insure  repeatable setup

  WiFly.begin();

  SpiSerial.print("set wlan auth 4\r");echo();
  SpiSerial.print(ssid_cmd);SpiSerial.print("\r");echo();
  SpiSerial.print(phrase_cmd);SpiSerial.print("\r");echo();
  SpiSerial.print(join_cmd);SpiSerial.print("\r");echo();

  SpiSerial.print("set ip proto 1\r");echo();
  SpiSerial.print("set ip host 192.168.1.100\r");echo();
  SpiSerial.print("set ip remote 12345\r");echo();

  SpiSerial.print("save\r");echo();
  SpiSerial.print("reboot\r");echo();
  delay(2000);
  SpiSerial.print("$$$");echo();
  SpiSerial.print(join_cmd);SpiSerial.print("\r");echo();
  SpiSerial.print("exit\r");echo();
}


