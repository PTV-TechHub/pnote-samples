#include <Arduino_APDS9960.h>  // Sensor library
#include "Leanbot.h"           // Leanbot library
 
int r = 0, g = 0, b = 0;
unsigned long lastUpdate = 0;
 
void setup() {
  Leanbot.begin();             // Initialize Leanbot
  Serial.begin(115200);
  while (!Serial);
 
  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS-9960 sensor!");
    while (1);
  }
 
  Serial.println("APDS-9960 sensor initialized.");
}
 
void loop() {
  // Read color values if available
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);
  }
 
  // Every 100 ms, check light and control LEDs
  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();
 
    int ambient = r + g + b;  // Estimate ambient light
 
    Serial.print("RGB: ");
    Serial.print(r); Serial.print(", ");
    Serial.print(g); Serial.print(", ");
    Serial.print(b);
 
    Serial.print(" | Estimated Ambient Light: ");
    Serial.println(ambient);
 
    // Adaptive LED Control Logic
    if (ambient < 1000) {
      // It's dark → turn ON LED (green)
      LbRGB.clear();
      LbRGB.fillColor(0x33cc00, BITMAP(ledO, ledA, ledB, ledC, ledD, ledE, ledF));
      LbRGB.show();
    } else {
      // It's bright → turn OFF LED
      LbRGB.clear();
      LbRGB.fillColor(0x000000, BITMAP(ledO, ledA, ledB, ledC, ledD, ledE, ledF));
      LbRGB.show();
    }
  }
}
