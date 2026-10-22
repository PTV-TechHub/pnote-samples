#include <Leanbot.h>                    // use Leanbot library
#include "LeanbotIoT.h"
 
#define  WIFI_SSID      F("YOUR_WIFI_SSID")
#define  WIFI_PASSWORD  F("YOUR_WIFI_PASSWORD")
 
// Asset - https://iot.pythaverse.space/manager/?realm=pythaverse#/assets/false/67qJjyT5BkSTM0GeynB4Ma
#define  IOT_ASSET_ID   F( "67qJjyT5BkSTM0GeynB4Ma" )
 
auto IoTColorA = LbIoT.Asset.attribute(F( "ColorA" ));
auto IoTColorB = LbIoT.Asset.attribute(F( "ColorB" ));
 
void setup() {
  Leanbot.begin();                      // initialize Leanbot
 
  LbIoT.Wifi.begin( WIFI_SSID, WIFI_PASSWORD );
  LbIoT.Asset.begin( IOT_ASSET_ID );
 
  IoTColorA.write("DETECTING"); 
}
 
void loop() {
  LbMission.begin();
 
  goToColorDetectionPoint();
  delay(1000);               // delay 1 second for demo observation
  simulateColorDetection();
  beep();                    // indicate finish detectColor
  delay(1000);               // delay 1 second for demo observation
  goToCollectionArea();
  delay(1000);               // delay 1 second for demo observation
 
  beep();                    // indicate begin getTargetColor
 
  LbRGB_showColor(CRGB::Black);
  String targetColor = getTargetColor();
 
  beep();                    // indicate finish getTargetColor
 
  Serial.print( "Target color: " );
  Serial.println( targetColor );
 
  if (targetColor == "RED") {
    handleRedBlock();
  } else if (targetColor == "YELLOW") {
    handleYellowBlock();
  } else if (targetColor == "GREEN") {
    handleGreenBlock();
  } else if (targetColor == "NONE") {
    handleNone();
  } else {
    Serial.println("No valid color received");
  }
 
  LbMission.end();
}
 
void goToColorDetectionPoint() {
  Serial.println("Navigating to color detection point...");
  LbMotion_runDistanceMm(2000, 2000, 170);       //  move from grid 8 to grid 15
}
 
void simulateColorDetection() {
  Serial.println( "Please touch one of TB1A, TB1B, TB2A, TB2B to simulate color detection ..." );
  
  while (true) {
    BlinkLed();
 
    if (LbTouch.read(TB1A)) {
      Serial.println("TB1A touched - RED");
      LbRGB_showColor(CRGB::Red);
      IoTColorA.write("RED");
      return;
    } 
    if (LbTouch.read(TB1B)) {
      Serial.println("TB1B touched - YELLOW");
      LbRGB_showColor(CRGB::Yellow);
      IoTColorA.write("YELLOW");
      return;
    } 
    if (LbTouch.read(TB2A)) {
      Serial.println("TB2A touched - GREEN");
      LbRGB_showColor(CRGB::Green);
      IoTColorA.write("GREEN");
      return;
    } 
    if (LbTouch.read(TB2B)) {
      Serial.println("TB2B touched - NONE");
      LbRGB_showColor(CRGB::Black);
      IoTColorA.write("NONE");
      return;
    }
  }
}
 
void BlinkLed(){
  LbRGB_showColor(CRGB::White);
  delay(100);
  LbRGB_showColor(CRGB::Black);
  delay(100);
}
 
void goToCollectionArea() {
  LbMotion_runDistanceMm(-2000, -2000, 170);    //  move from grid 15 to grid 8
  LbMotion_runRotationDeg(-1000, 1000, 81);     //  facing grid 9
}
 
String getTargetColor() {  
  String targetColor = IoTColorB.read();
  while (targetColor == "DETECTING") {          //  targetColor not ready yet
    targetColor = IoTColorB.read();             //  keep reading (until ready)
  }
  return targetColor;
}
 
void handleGreenBlock() {
  Serial.println("Handling Green block...");
  LbRGB_showColor(CRGB::Green);
  LbMotion_runRotationDeg(1000, -1000, 16);     //  facing grid 17
  LbMotion_runDistanceMm(2000, 2000, 380);      //  move from grid 8 to grid 17
  LbGripper.close();
  LbMotion_runDistanceMm(-2000, -2000, 380);    //  move from grid 17 to grid 8
  LbGripper.open();
}
 
void handleYellowBlock() {
  Serial.println("Handling Yellow block...");
  LbRGB_showColor(CRGB::Yellow);
  LbMotion_runDistanceMm(2000, 2000, 320);      //  move from grid 8 to grid 10
  LbGripper.close();
  LbMotion_runDistanceMm(-2000, -2000, 320);    //  move from grid 10 to grid 8
  LbGripper.open();
}
 
void handleRedBlock() {
  Serial.println("Handling Red block...");
  LbRGB_showColor(CRGB::Red);
  LbMotion_runRotationDeg(-1000, 1000, 16);     //  facing grid 3
  LbMotion_runDistanceMm(2000, 2000, 380);      //  move from grid 8 to grid 3
  LbGripper.close();
  LbMotion_runDistanceMm(-2000, -2000, 380);    //  move from grid 3 to grid 8
  LbGripper.open();
}
 
void handleNone() {
  Serial.println("No block detected, staying in place.");
  LbRGB_showColor(CRGB::Black);
}
 
void beep() {
  for (int count = 0; count < 3; count++) {
    Leanbot.tone(440 * 2, 50);
    delay(50);
  }
}
 
void LbRGB_showColor(const uint32_t rgb_led_code){
  LbRGB.fillColor(rgb_led_code);
  LbRGB.show();
}
 
void LbMotion_runDistanceMm(int vL, int vR, int distanceMm) {
  LbMotion.runLR(vL, vR);
  LbMotion.waitDistanceMm(distanceMm);
  LbMotion.stopAndWait();
}
 
void LbMotion_runRotationDeg(int vL, int vR, int rotationDeg) {
  LbMotion.runLR(vL, vR);
  LbMotion.waitRotationDeg(rotationDeg);
  LbMotion.stopAndWait();
}
