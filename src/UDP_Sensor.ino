// memsic 2125 accelerometer x,y UDP blaster
#include "WiFly.h"
#include "Credentials.h"
extern void reset_now();
int woof_count=0;
char udp_message[64];
char count[16]="bogus";

const int xpin = 2;
const int ypin = 3;

void echo() {
    delay(500);
    while(SpiSerial.available() > 0) {
        Serial.print((char)SpiSerial.read());
    }
}

int associate_with_access_point() {
  char ssid_cmd[64] = "set wlan ssid "; 
  char phrase_cmd[64] = "set wlan phrase " ;
  char join_cmd[64] =  "join ";

  strcat(ssid_cmd,ssid);
  strcat(phrase_cmd,passphrase);
  strcat(join_cmd,ssid);
  Serial.begin(9600);
  Serial.println("\n\r\n\rWiFly Shield UDP blaster ");

  reset_now(); // allways start with factory defaults to insure  repeatable setup

  WiFly.begin();

  SpiSerial.print("set wlan auth 4\r");echo();
  SpiSerial.print(ssid_cmd);SpiSerial.print("\r");echo();
  SpiSerial.print(phrase_cmd);SpiSerial.print("\r");echo();
  SpiSerial.print(join_cmd);SpiSerial.print("\r");echo();

  SpiSerial.print("set ip proto 1\r");echo();
  SpiSerial.print("set ip host 255.255.255.255\r");echo();
  SpiSerial.print("set ip remote 55555\r");echo();

  SpiSerial.print("save\r");echo();
  SpiSerial.print("reboot\r");echo();
  delay(2000);
  SpiSerial.print("$$$");echo();
  SpiSerial.print(join_cmd);SpiSerial.print("\r");echo();
  SpiSerial.print("exit\r");echo();
}



int read_2125(int *x, int *y) {
  int debug = 0;
   // x axis (pitch)
  int tHx;      // length of HIGH pulse in microseconds
  int tLx;      // length of LOW pulse in microseconds
  int Tx;       // length of duty cycle in microseconds
  float xRatio; // the ratio of tHx/tLx
  
  // y axis (roll)
  //int pulseY;
  //int accX, accY;
  int tHy;      // length of HIGH pulse in microseconds
  int tLy;      // length of LOW pulse in microseconds
  int Ty;       // length of duty cycle in microseconds
  float yRatio; // the ratio of tHx/tLx

  // read pulse from x axis
  tHx       = pulseIn(xpin, HIGH);
  tLx       = pulseIn(xpin, LOW);
  Tx        = tHx + tLx;
  xRatio    = tHx/tLx;
  
  // read pulse from y axis
  tHy       = pulseIn(ypin, HIGH);
  tLy       = pulseIn(ypin, LOW);
  Ty        = tHy + tLy;
  yRatio    = tHy/tLy;
  
  // read the pulse from y axis
  //pulseY    = pulseIn(ypin, HIGH);
  
  // convert the pulse width into acceleration
  // accX and accY are in milli-gs, earth g is 1000
  // accX = ((pulseX/10)-500)*8;
  // accY = ((pulseY/10)-500)*8;
  
  *x=xRatio;
  *y=yRatio;
}

void setup()
{
  Serial.begin(9600);
  pinMode(xpin,INPUT);
  pinMode(ypin,INPUT);
  int success = associate_with_access_point();


}

void loop()
{
  bool good_measurement=false;
  int x,y;

  good_measurement = read_2125(&x,&y);

  strcat(udp_message,count);
  strcat(udp_message,"\r");
  sprintf(udp_message,"x=%d,y=%d\r",x,y);
  SpiSerial.print(udp_message); // I expect this to be seen by a udp listener on the local network

  delay(1000);

}
