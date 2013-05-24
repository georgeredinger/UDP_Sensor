#include <Arduino.h>

const int xpin = 2;
const int ypin = 3;

void setup_2125() {
  pinMode(xpin,INPUT);
  pinMode(ypin,INPUT);
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


