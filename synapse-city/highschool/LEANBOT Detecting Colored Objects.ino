#include <Leanbot.h>
#include <Arduino_APDS9960.h>
 
 
//==============================================================================
//  Object Color
//==============================================================================
 
int ObjRed, ObjGreen, ObjBlue;                 // measured object RGB color
 
void _coreRead(int& r, int& g, int& b, CRGB ledColor) {  // measure RGB values under ledColor + ambient light condition
  LbRGB.fillColor(ledColor);
  LbRGB.show();
  while ( ! APDS.colorAvailable());
  APDS.readColor(r, g, b);
}
 
void Obj_readRGB() {
  int rRed, gGreen, bBlue;
  int rr, gg, bb;
 
  int originalBrightness = LbRGB.getBrightness();        // remember LED brightness
  LbRGB.setBrightness(255);                              // change to maximum LED brightness
 
  _coreRead( rRed, gg,   bb,  CRGB::Red   );   // rRed:     red value  under   Red LED + ambient light
  _coreRead( rr, gGreen, bb,  CRGB::Lime  );   // gGreen: green value  under Green LED + ambient light - CRGB::Lime is #00FF00 from https://github.com/FastLED/FastLED/wiki/Pixel-reference#predefined-colors-list
  _coreRead( rr,   gg, bBlue, CRGB::Blue  );   // bBlue:   blue value  under  Blue LED + ambient light
  _coreRead( rr,   gg,   bb,  CRGB::Black );   // (ambient) RGB values under    no LED + ambient light
 
  LbRGB.setBrightness(originalBrightness);               // restore LED brightness
 
  ObjRed   = rRed   - rr;    // remove (varying) ambient light
  ObjGreen = gGreen - gg;
  ObjBlue  = bBlue  - bb;
}
 
 
//==============================================================================
//  Basic Colored-Object Detection (only Reg, Green, Blue)
//==============================================================================
 
boolean BasicObj_isRed() {
  if ( ObjRed <= ObjGreen )  return false;
  if ( ObjRed <= ObjBlue  )  return false;
  if ( ObjRed <= 3        )  return false;
  return true;
}
 
boolean BasicObj_isGreen() {
  if ( ObjGreen <= ObjRed  )  return false;
  if ( ObjGreen <= ObjBlue )  return false;
  if ( ObjGreen <= 3       )  return false;
  return true;
}
 
boolean BasicObj_isBlue() {
  if ( ObjBlue <= ObjRed   )  return false;
  if ( ObjBlue <= ObjGreen )  return false;
  if ( ObjBlue <= 3        )  return false;
  return true;
}
 
 
//==============================================================================
//  Advanced Colored-Object Detection (more colored-objects)
//    Some template example only
//    Student to program their own detection methods
//==============================================================================
 
boolean LegoBrick_isRed() {
  return false;
}
 
boolean LegoBrick_isLightGreen() {
  return false;
}
 
 
boolean JengaBlock_isRed() {
  return false;
}
 
boolean JengaBlock_isPurple() {
  return false;
}
 
 
//==============================================================================
 
 
void setup() {
  Leanbot.begin();                      // initialize Leanbot
  APDS.begin();
}
 
 
void loop() {
  ObjectColorDemo();
  LbDelay(3000);    // delay 3 seconds between each Demo
}
 
 
void ObjectColorDemo() {
  Obj_readRGB();        // activate Led light and APDS color sensor to read object RGB values
 
  // Print out object RGB values for observation
  Serial.println();
  Serial.print(  "ObjRed   = " );
  Serial.println( ObjRed );
  Serial.print(  "ObjGreen = " );
  Serial.println( ObjGreen );
  Serial.print(  "ObjBlue  = " );
  Serial.println( ObjBlue );
 
  if (BasicObj_isRed()) {
    Serial.println( "Detect Basic object: Red" );
  }
 
  if (BasicObj_isGreen()) {
    Serial.println( "Detect Basic object: Green" );
  }
 
  if (BasicObj_isBlue()) {
    Serial.println( "Detect Basic object: Blue" );
  }
 
  if (LegoBrick_isLightGreen()) {
    Serial.println( "Detect Lego brick: Light Green" );
  }
 
  if (JengaBlock_isPurple()) {
    Serial.println( "Detect Jenga block: Purple" );
  }
}
