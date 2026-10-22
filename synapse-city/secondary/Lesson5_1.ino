#include <Arduino_APDS9960.h>  // Include APDS-9960 sensor library
 
int r = 0, g = 0, b = 0;              // RGB variables
unsigned long lastUpdate = 0;        // For timing
 
void setup() {
  Serial.begin(115200);              // Start Serial Monitor
  while (!Serial);                   // Wait for Serial Monitor
 
  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS-9960 sensor!");
    while (1);  // Stop program if sensor fails
  }
 
  Serial.println("APDS-9960 sensor initialized.");
}
 
void loop() {
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);         // Read RGB values from sensor
  }
 
  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();           // Update the timer marker
 
    int ambient = r + g + b;         // Estimate ambient light using R + G + B
 
    Serial.print("RGB: ");
    Serial.print(r); Serial.print(", ");
    Serial.print(g); Serial.print(", ");
    Serial.print(b);
 
    Serial.print(" | Estimated Ambient Light: ");
    Serial.println(ambient);         // Print the estimated ambient light level
  }
}
