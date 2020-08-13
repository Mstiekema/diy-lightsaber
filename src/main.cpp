#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

bool swinging;
unsigned long lastGoodAccel;

void setup() {
  Serial.begin(9600);
  Wire.begin(D5, D6);

  // Initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  
  // Verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  lastGoodAccel = millis();
}

void checkSwing(int16_t x, int16_t y, int16_t z) {
  bool goodAccel = false;

  // Once we have enough acceleration, we can make the saber 
  //  && lastGoodAccel > 1000
  if ((x > 20000 || x < -20000 || y > 20000 || y < -20000 || z > 20000 || z < -20000)) {
    goodAccel = true;
    lastGoodAccel = millis();
    Serial.println("Swing");
  }
  
  if (!swinging) {

  } else {
    
  }
}

void loop() {
  // Read accel data from MPU-6050
  accelgyro.getAcceleration(&ax, &ay, &az);

  checkSwing(ax, ay, az);

  // Print data to graph
  Serial.print("{\"topic\": \"AccelX\", \"payload\": ");
  Serial.print(ax);
  Serial.println("}");

  Serial.print("{\"topic\": \"AccelY\", \"payload\": ");
  Serial.print(ay);
  Serial.println("}");
      
  Serial.print("{\"topic\": \"AccelZ\", \"payload\": ");
  Serial.print(az);
  Serial.println("}");
}