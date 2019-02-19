#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse(); // Define object for the received packet

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
}

void loop() {
  
    xbee.readPacket();
    if (xbee.getResponse().isAvailable()) {
      // got some packet
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE){ 
        // Got packet with 64-bit address (API frame 0x90)
        
        xbee.getResponse().getZBRxResponse(rx);
        uint8_t sensor_data[rx.getDataLength()];

        Serial.print("Received reading: ");
        
        // Print out the received data in correct format
        // xx.xxx
        for (int i =rx.getDataLength()-1; i >= 0;i--){
          sensor_data[i] = rx.getData(i);
          Serial.print(sensor_data[i]);
          if (i==2){
            Serial.print(".");
            }
          }
          Serial.print("\n");
      } else {
        Serial.println("Received an unexpected frame.");
      }
          
    } else {
      Serial.println("Nothing received.");
    }
  delay(1000);
    
}
