#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBExplicitRxResponse rx = ZBExplicitRxResponse(); // Define object for the packet

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
}

void loop() {
    xbee.readPacket();
    if (xbee.getResponse().isAvailable()) {
      // got some packet
      if (xbee.getResponse().getApiId() == ZB_EXPLICIT_RX_RESPONSE){ 
        // Got packet with 64-bit address
        xbee.getResponse().getZBRxResponse(rx);
        uint8_t sensor_data[rx.getDataLength()];

        Serial.print("Received reading: ");

        // Print out the received data
        for (int i =rx.getDataLength()-1; i >= 0;i--){
          sensor_data[i] = rx.getData(i);
          Serial.print(sensor_data[i]);
          if (i==2){
            Serial.print(".");
            }
          }
          Serial.print("\n");
      } else {
        Serial.println("Not a 64-bit addressed packet.");
      }
          
    } else {
      Serial.println("Nothing received.");
    }
  delay(1000);
    
}
