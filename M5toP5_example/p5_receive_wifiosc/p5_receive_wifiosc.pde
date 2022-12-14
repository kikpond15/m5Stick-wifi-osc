import netP5.*;
import oscP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;

int data = 0;
int count = 0;

void setup() {
  size(640, 480);
  oscP5 = new OscP5(this, 12000);
  textSize(50);
}

void draw() {
  background(100);
  fill(255);
  text(str(data), width/2-100, height/2);
  text(str(count), width/2+100, height/2);
}

void oscEvent(OscMessage theOscMessage) {
  //println(theOscMessage.addrPattern());
  if (theOscMessage.checkAddrPattern("/button/push")==true) {
    data = theOscMessage.get(0).intValue();
  }
  if (theOscMessage.checkAddrPattern("/button/count")==true) {
    count = theOscMessage.get(0).intValue();
  }
}
