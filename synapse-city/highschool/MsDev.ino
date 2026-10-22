#include <Leanbot.h>
 
void setup() {
  Leanbot.begin();                           // initialize Leanbot
}
 
void loop() {
  LbMission.beginDigitalTwin(F( "msDev" ));    // start mission
  
  LbRGB.clear();
  LbRGB[ledO] = 0xFFFFFF;
  LbRGB[ledA] = 0xFF0000;
  LbRGB[ledB] = 0xFFFF00;
  LbRGB[ledC] = 0x00FF00;
  LbRGB[ledD] = 0x00FFFF;
  LbRGB[ledE] = 0x0000FF;
  LbRGB[ledF] = 0xFF00FF;
  LbRGB.show();
  
  LbDelay(500);
  LbGripper.moveToLR(90, 0, 1000);
  LbDelay(1000);
  LbGripper.moveToLR(0, 90, 1000);
  LbDelay(1000);
  LbGripper.moveToLR(-30, 120, 500);
  LbDelay(1000);
  LbGripper.moveToLR(0, 0, 1500);
  LbDelay(1000);
 
  LbMotion.runLR(+800, +1200);               // go straight forward 
  LbMotion.waitDistanceMm(+100);             //   for 100 mm distance
 
  LbMotion.runLR(-800, -1200);               // go straight backward 
  LbMotion.waitDistanceMm(-100);             //   for 100 mm distance
 
  LbMission.end();                           // stop, finish mission
}
