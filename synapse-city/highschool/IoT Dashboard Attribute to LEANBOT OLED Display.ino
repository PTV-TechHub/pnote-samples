#include "Leanbot.h"
#include "LeanbotIoT.h"
 
 
// using F() macro to lower Arduino SRAM usage
#define  WIFI_SSID      F( "YOUR_WIFI_SSID" )
#define  WIFI_PASSWORD  F( "YOUR_WIFI_PASSWORD" )
 
#define  IOT_ASSET_ID   F( "3TkLOyHb5FzWJtN1QEnNGo" )
#define  IOT_REALM      F( "master" )
//  Asset      https://iot.pythaverse.space/manager/#/assets/false/33khwmcNaidrPJ2oZpcgde
//  Dashboard  https://iot.pythaverse.space/manager/#/insight/false/???
 
 
auto IoT_Text_OLED = LbIoT.Asset.attribute(F( "MarcoText" ));
 
 
//  OLED display library
 
#include <U8g2lib.h>
#include <Wire.h>
 
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);   // SH1106 for 1.3" OLED module
 
 
 
void setup() {
  Leanbot.begin();
 
  // begin OLED
  u8g2.setBusClock( 400000 );                // max I2C speed
  u8g2.begin();
  u8g2.setFont( u8g2_font_luBS08_tr );        // OLED: choose a suitable font
 
}
 
 
void OLED_Display(String text) {
  for ( u8g2.firstPage() ; u8g2.nextPage() ; ) {      // OLED buffer drawing loop
    u8g2.setCursor(35, 16);
    u8g2.print(text);
 
    u8g2.setCursor(35, 24);
    u8g2.print("");
    
  }
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
 
 
  Serial.print( "\n\n\n" "######   Read the text from IoT Dashboard to OLED Display   ######" "\n\n" );
  String text = IoT_Text_OLED.read();
  checkResponseStatus();
  Serial.print( IoT_Text_OLED.name() );
  Serial.print(" = ");
  Serial.println(text);
 
  OLED_Display(text);
 
  delay(2500);
}
 
 
/*
  https://developer.mozilla.org/en-US/docs/Web/HTTP/Status#client_error_responses
+  - Informational responses (100 – 199)
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
