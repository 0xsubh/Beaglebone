#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor1(2, 4);  // trigger=2, echo=3
UltraSonicDistanceSensor distanceSensor2(6, 7);  // trigger=6, echo=7

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.println("A: ");
    Serial.println(distanceSensor1.measureDistanceCm());
    Serial.println("B: ");
    Serial.println(distanceSensor2.measureDistanceCm());
    delay(500);
}
