// Leanbot verify, contain Blue pollution at E2 and neutralize with block from S3
// Start
// - Leanbot at CRL
// - Pollution: Blue at E2
// - Neutralize at S3
// Leanbot steps
// - Follow line to E2
// - Read and display color LED RGB of block at E2
// - If color != BLUE then STOP (Mission end)
// - Push Pollution into Containment E
// - Follow line to S3
// - Pick up Neutralize at S3
// - Follow line to E2
// - Drop Neutralize into Containment E
// - Mission end (Leanbot stops at Containment E)
 
#include <Leanbot.h>
#include <Arduino_APDS9960.h>
 
 
//==============================================================================
//  Object Color
//==============================================================================
int speed = 2000;
 
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
//  Basic Colored-Object Detection (only Red, Green, Blue)
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
 
String Obj_detectColor() {
  Obj_readRGB();
 
  if (BasicObj_isRed()) {
    LbRGB.fillColor(CRGB::Red);
    LbRGB.show();
    return "Red";
  }
 
  if (BasicObj_isGreen()) {
    LbRGB.fillColor(CRGB::Green);
    LbRGB.show();
    return "Green";
  }
 
  if (BasicObj_isBlue()) {
    LbRGB.fillColor(CRGB::Blue);
    LbRGB.show();
    return "Blue";
  }
 
  LbRGB.fillColor(CRGB(50, 50, 50));   // Dark Gray indicating Unknown color
  LbRGB.show();
  return "Unknown";
}
 
//==============================================================================
 
void setup() {
  Leanbot.begin();                      // initialize Leanbot
  LbIRLine.doManualCalibration(TB1A);
  // LbIRLine.setThreshold( 69,   78,  106,   70 );    // or measure first and then edit the threshold in the code
  APDS.begin();
  LbDelay(500);
}
 
String Color;
 
void loop() {
  LbMission.begin(TB1A + TB1B);                  // Start mission when TB1A + TB1B are pressed
  
  FromCRLtoE2();
  Color = Obj_detectColor();			// Read and display color LED RGB
  if (Color!= "Blue") {
    LbMission.end(); 
  }
  PushPollutionE2();
  FromE2toS3();
  PickupNeutralizeS3();
  FromS3toE2();
  DropNeutralizeE2();
  LbMission.end();  
}
 
void FromCRLtoE2(){
  Forward(speed, 110);                          // Go  to the line.
  Rotate(-speed, 23);                           // Turn Left
  followLineMultipleJunctions(1);               // Move 1 Junctions
  goToJunction();
  Rotate(speed, 33);                            // Turn right
  Forward(speed, 25);                             
}
 
void PushPollutionE2() {
  Rotate(speed/4, 50);                           // Move the blue block into area 
  Backward(speed, 25);                           // Move backward to the line
}
 
void FromE2toS3() {
  Rotate(speed, 30);                            // Turn right
  followLineMultipleJunctions(1);               // Move 1 Junctions
  goToJunction();
  Rotate(speed, 60);                            // Turn right
  followLineMultipleJunctions(2);               // Move 2 Junctions
  goToJunction();
 
  
}
void PickupNeutralizeS3() {
  LbGripper.close(50);
}
void FromS3toE2() {
  Rotate(speed, 150);                           // Turn around
  followLineMultipleJunctions(2);               // Move 2 Junctions
  goToJunction();
  Rotate(-speed, 23);                           // Turn Left                          
  Forward(speed, 110);
}
void DropNeutralizeE2() {
  LbGripper.open();
}
 
void Forward(int speed, int distanceMm) {
  LbMotion.runLR(speed, speed);                  // Move forward with given speed
  LbMotion.waitDistanceMm(distanceMm);           // Wait until distance is reached
  LbMotion.stopAndWait();                        // Stop and wait
}
 
void Backward(int speed, int distanceMm) {
  LbMotion.runLR(-speed, -speed);                // Move backward with given speed
  LbMotion.waitDistanceMm(distanceMm);           // Wait until distance is reached
  LbMotion.stopAndWait();                        // Stop and wait
}
 
void Rotate(int speed, int deg) {
  LbMotion.runLR(speed, -speed);                 // Rotate robot in place
  LbMotion.waitRotationDeg(deg);                 // Wait until rotation angle is reached
  LbMotion.stopAndWait();                        // Stop and wait
}
 
void followLineDistance(int distanceMm) {
  int targetMm = distanceMm + LbMotion.getDistanceMm(); // Calculate targ et distance
 
  while (LbMotion.getDistanceMm() < targetMm) { 				// Continue until target distance is reached
    runFollowLine();                             				// Run line following logic
  }
}
 
void runFollowLine() {
  //LbRGB.fillColor(CRGB::Black); // Off RGB
  int lineValue = LbIRLine.read();                // Read IR line sensor value
  LbIRLine.displayOnRGB(CRGB::DarkCyan);          // Display sensor status on RGB LED
 
  switch (lineValue) {
 
    case 0b0100:                                 // .o..
      LbMotion.runLR(+speed/2, +speed);          // Adjust slightly to the left
      break;
 
    case 0b0010:                                 // ..o.
      LbMotion.runLR(+speed, +speed/2);          // Adjust slightly to the right
      break;
 
    case 0b1100:                                 // oo..
      LbMotion.runLR(     0, +speed);            // Strong left correction
      break;
 
    case 0b0011:                                 // ..oo
      LbMotion.runLR(+speed, 0);                 // Strong right correction
      break;
 
    case 0b1000:                                 // o...
      LbMotion.runLR(-speed/2, +speed/2);        // Sharp left turn
      break;
 
    case 0b0001:                                 // ...o
      LbMotion.runLR(+speed/2, -speed/2);        // Sharp right turn
      break;
 
    default:
      LbMotion.runLR(+speed, +speed);            // Go straight
      break;
  }
}
 
void followLineUntilJunction() {
  while (LbIRLine.read() != 0b1111) {            // Continue until full junction is detected
    runFollowLine();                             // Run line following logic
  }
}  
 
void goToJunction() {
  followLineUntilJunction();                     // Continue until junction is detected
  followLineDistance(20);                        // Move forward to the purple block
  LbMotion.stopAndWait();                        // Stop and wait
}
 
void followLineMultipleJunctions(int junctionCount) {
  for (int i = 0; i < junctionCount; i++) {
    followLineDistance(30);
    followLineUntilJunction();
  }
}
