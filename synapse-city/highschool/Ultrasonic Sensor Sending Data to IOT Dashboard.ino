#include "Leanbot.h"
#include "LeanbotIoT.h"
 
 
// using F() macro to lower Arduino SRAM usage
#define  WIFI_SSID      F( "YOUR_WIFI_SSID" ) //change the wifi user ID
#define  WIFI_PASSWORD  F( "YOUR_WIFI_PASSWORD" ) //change the wifi password
 
#define  IOT_ASSET_ID   F( "abcdefghijklmnopqrst" ) //change the asset ID
#define  IOT_REALM      F( "master" )
//  Asset      https://iot-qa.pythaverse.space/manager/#/assets/false/33khwmcNaidrPJ2oZpcgde
//  Dashboard  https://iot-qa.pythaverse.space/manager/#/insight/false/???
 
 
auto IoT_US_value = LbIoT.Asset.attributeInt(F( "Ultrasonic_Sensor" )); //change the Attribute ID
//IOT_US_value is a variable that you can change. Make sure to update the entire program with your new variable name.
 
 
void setup() {
  Leanbot.begin();
}
 
 
void loop() {
  if ( LbIoT.Wifi.status() != WL_CONNECTED ) {
    if ( LbIoT.Wifi.begin( WIFI_SSID, WIFI_PASSWORD ) < 0 ) {
      return;  // retry
    }
  }
 
 
  if ( LbIoT.Asset.status() != ESTABLISHED ) {
    if ( LbIoT.Asset.begin( IOT_ASSET_ID, IOT_REALM ) < 0 ) {
      return;  // retry
    }
 
    auto iotNotes = LbIoT.Asset.attribute(F( "notes" ));
    Serial.print( "Asset: " );
    Serial.println( iotNotes.read() );      // print Asset info
  }
 
 
  // read sensor value
  int sensorValue = Leanbot.pingCm();
  Serial.print( "\n\n\n" "######   Send the \"sensorValue = " );
  Serial.print(sensorValue);
  Serial.print( "\" to server   ######" "\n\n" );
  IoT_US_value.write( sensorValue );
  delay(2500);                           // small delay to wait for response from server
  LbIoT.Asset.flushResponse(NULL);
  checkResponseStatus();
 
 
  Serial.print( "\n\n\n" "######   Read the value from server   ######" "\n\n" );
  int value = IoT_US_value.read();
  checkResponseStatus();
  Serial.print( IoT_US_value.name() );
  Serial.print(" = ");
  Serial.println(value);
  delay(2500);
}
 
 
/*
  https://developer.mozilla.org/en-US/docs/Web/HTTP/Status#client_error_responses
  - Informational responses (100 – 199)
  - Successful responses    (200 – 299)
  - Redirection messages    (300 – 399)
  - Client error responses  (400 – 499)
  - Server error responses  (500 – 599)
 
  Common status:
  - HTTP/1.1 200 OK       : The request succeeded
  - HTTP/1.1 403 Forbidden: Incorrect "attributeId" or "Access public write" is not configured
*/
void checkResponseStatus() {
  int responseStatus = LbIoT.Asset.responseStatus();
  LbIoT.decodeStatus( responseStatus );
}
