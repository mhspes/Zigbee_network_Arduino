#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBExplicitRxResponse rx = ZBExplicitRxResponse(); 

uint8_t data[5];
// Address and packet
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x414EA6F0);
ZBExplicitTxRequest zbTx = ZBExplicitTxRequest(addr64, data, sizeof(data));


void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
  xbee.setSerial(Serial);
}
void loop() {
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
      // got some packet
      if (xbee.getResponse().getApiId() == ZB_EXPLICIT_RX_RESPONSE){
      // Got packet with 64-bit address
      
      xbee.getResponse().getZBRxResponse(rx);
      uint8_t received_packet[rx.getDataLength()];  
      Serial.println("Received data.");
      for (int i =rx.getDataLength()-1; i >= 0;i--){
         data[i] = rx.getData(i);
          Serial.print(data[i]);
          }

      // Here could be data aggregation etc.

      //Forward data
      xbee.send(zbTx);
      Serial.print("\n");
      
      } else {
        Serial.println("Not a 64-bit addressed packet.");
      }
  } else {
    Serial.println("Nothing received");
  } 
     
  delay(1000);
}
