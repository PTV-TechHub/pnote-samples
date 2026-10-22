#include <Leanbot.h>                    // use Leanbot library
#include "LeanbotIoT.h"
 
#define  WIFI_SSID      F("YOUR_WIFI_SSID")
#define  WIFI_PASSWORD  F("YOUR_WIFI_PASSWORD")
 
// Asset - https://iot.pythaverse.space/manager/?realm=pythaverse#/assets/false/67qJjyT5BkSTM0GeynB4Ma
#define  IOT_ASSET_ID   F( "67qJjyT5BkSTM0GeynB4Ma" )
#define  IOT_REALM      F( "master" )
 
auto IoTColorA = LbIoT.Asset.attribute(F( "ColorA" ));
auto IoTColorB = LbIoT.Asset.attribute(F( "ColorB" ));
 
void setup() {
  Leanbot.begin();                      // initialize Leanbot
 
  LbIoT.Wifi.begin(WIFI_SSID, WIFI_PASSWORD);
  LbIoT.Asset.begin(IOT_ASSET_ID, IOT_REALM);
 
  IoTColorB.write("DETECTING"); 
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
  unsigned long startTime = millis();
  
  LbRGB_showColor(CRGB::Black);
  String targetColor = getTargetColor();
 
  unsigned long endTime = millis();
  beep();                    // indicate finish getTargetColor
 
  Serial.print( ">>>  getTargetColor() took (ms): " );
  Serial.println( endTime - startTime );
 
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
  LbMotion_runDistanceMm(2000, 2000, 170);       //  move from grid 14 to grid 7
}
 
void simulateColorDetection() {
  Serial.println( "Please touch one of TB1A, TB1B, TB2A, TB2B to simulate color detection ..." );
  
  while (true) {
    BlinkLed();
 
    if (LbTouch.read(TB1A)) {
      Serial.println("TB1A touched - RED");
      LbRGB_showColor(CRGB::Red);
      IoTColorB.write("RED");
      return;
    } 
    if (LbTouch.read(TB1B)) {
      Serial.println("TB1B touched - YELLOW");
      LbRGB_showColor(CRGB::Yellow);
      IoTColorB.write("YELLOW");
      return;
    } 
    if (LbTouch.read(TB2A)) {
      Serial.println("TB2A touched - GREEN");
      LbRGB_showColor(CRGB::Green);
      IoTColorB.write("GREEN");
      return;
    } 
    if (LbTouch.read(TB2B)) {
      Serial.println("TB2B touched - NONE");
      LbRGB_showColor(CRGB::Black);
 
      unsigned long startTime = millis();
      IoTColorB.write("NONE");
      unsigned long endTime = millis();
      Serial.print(">>>  IoTColorB.write() took (ms): ");
      Serial.println(endTime - startTime);
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
  LbMotion_runDistanceMm(-2000, -2000, 170);    //  move from grid 7 to grid 14
  LbMotion_runRotationDeg(-1000, 1000, 81);     //  facing grid 9
}
 
String getTargetColor() {  
  String targetColor = IoTColorA.read();
  while (targetColor == "DETECTING") {          //  targetColor not ready yet
    targetColor = IoTColorA.read();             //  keep reading (until ready)
  }
  return targetColor;
}
 
void handleGreenBlock() {
  Serial.println("Handling Green block...");
  LbRGB_showColor(CRGB::Green);
  LbMotion_runRotationDeg(1000, -1000, 16);     //  facing grid 19
  LbMotion_runDistanceMm(2000, 2000, 380);      //  move from grid 14 to grid 19
  LbGripper.close();
  LbMotion_runDistanceMm(-2000, -2000, 380);    //  move from grid 19 to grid 14
  LbGripper.open();
}
 
void handleYellowBlock() {
  Serial.println("Handling Yellow block...");
  LbRGB_showColor(CRGB::Yellow);
  LbMotion_runDistanceMm(2000, 2000, 320);      //  move from grid 14 to grid 12
  LbGripper.close();
  LbMotion_runDistanceMm(-2000, -2000, 320);    //  move from grid 12 to grid 14
  LbGripper.open();
}
 
void handleRedBlock() {
  Serial.println("Handling Red block...");
  LbRGB_showColor(CRGB::Red);
  LbMotion_runRotationDeg(-1000, 1000, 16);     //  facing grid 5
  LbMotion_runDistanceMm(2000, 2000, 380);      //  move from grid 14 to grid 5
  LbGripper.close();
  LbMotion_runDistanceMm(-2000, -2000, 380);    //  move from grid 5 to grid 14
  LbGripper.open();
}
 
void handleNone() {
  Serial.println("No block detected, staying in place.");
  LbRGB_showColor(CRGB::Black);
}
 
void beep() {
  for (int count = 0; count < 5; count++) {
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
