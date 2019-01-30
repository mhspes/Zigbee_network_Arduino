#include <XBee.h>

#define LIGHTSENSOR A0

XBee xbee = XBee();
uint8_t data[5];

XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x414EA6F0);
ZBExplicitTxRequest zbTx = ZBExplicitTxRequest(addr64, data, sizeof(data));

void setup() {
  pinMode(LIGHTSENSOR,INPUT);  
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
  float reading = analogRead(LIGHTSENSOR); //Read light level
  int value = 100*(double)reading;
  
  // Insert value into uint8_t array
  for(int i = 4; i >=0; i--){
    data[i]=  value/ (int)pow(10,i) % 10;   
    }
  Serial.println("Sending a datapacket..");
  xbee.send(zbTx);
  Serial.print("\n");
  delay(1000);
}

