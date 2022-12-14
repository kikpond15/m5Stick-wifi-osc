import netP5.*;
import oscP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;
String SEND_IP = "your send ssid";
int send_port = 12000;

int r, g, b;


void setup() {
  size(300,300);
  oscP5 = new OscP5(this, 12000);
  textSize(50);
  myRemoteLocation = new NetAddress(SEND_IP,send_port);
}

void draw() {
  r = int(map(mouseX, 0, width, 0, 255));
  g = int(map(mouseY, 0, height, 0, 255));
  b = int(map(mouseX+mouseY, 0, width+height, 0, 255));
  background(r, g, b);
  fill(255-r, 255-g, 255-b);
  text(str(r)+","+str(g)+","+str(b) , 10, height/2);
}

void mouseMoved(){
  OscMessage myMessage = new OscMessage("/color");
  myMessage.add(r);
  myMessage.add(g);
  myMessage.add(b); 
  oscP5.send(myMessage, myRemoteLocation); 
}
