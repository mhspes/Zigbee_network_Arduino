#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse(); 

uint8_t data[5]; // 5 byte frame for 5 digits (sensed value)

XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x414EA6F0); // 64-byte address of the coordinator
ZBExplicitTxRequest zbTx = ZBExplicitTxRequest(addr64, data, sizeof(data)); // Frame


void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
  xbee.setSerial(Serial);
}

void loop() {
  
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
      // got some packet
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE){ 
        // Got packet with 64-bit address (API frame 0x90)
      
      xbee.getResponse().getZBRxResponse(rx); 
      // Assign the rx packet for the xbee-object
            
      uint8_t received_packet[rx.getDataLength()]; // Fetch data

      // Set the data into payload
      for (int i =rx.getDataLength()-1; i >= 0;i--){
         data[i] = rx.getData(i);
          }

      // Here could be data aggregation etc.
      
      // Forward data
      xbee.send(zbTx);
      Serial.print("\n");
      
      } else {
        Serial.println("Received an unexpected frame."); // Faulty frame format
      }
  } else {
    Serial.println("Nothing received");
  } 
     
  delay(1000);
}
