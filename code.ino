/*
Auto Crash Avoiding System
An Automatic arduino (microcontroller) based system for automobile

Author: Mukhtar Zotder | 2020
URL: https://github.com/mukhtarzotder/auto-crash-avoiding-system/
License: MIT
*/

// declaring pins
const int triggerPin = A3;
const int echoPin = A2;
const int relayPin = 5;
const int buzzerPin = 11;
const int gLED = 6;
const int rLED = 7;
// const int led2 = 6;

// variables for ultrasonic sensor
long time = 0;
int distance = 0;
int dist = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("Auto Crash Avoiding System - 2020");
    Serial.println("Author: Mukhtar Zotder");

    pinMode(rLED, OUTPUT);
    pinMode(gLED, OUTPUT);
    pinMode(relayPin, OUTPUT);
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzerPin, OUTPUT);
}

int getDistance() {
    dist = 0;
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    time = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = time * 0.034 / 2;
    dist = time * 0.034 / 2;      // speed of sound = 0.034 cm/us (microsecond)

    return dist;
}

int getDistAvg() {
    int totalDist = 0;

    for (int i = 0; i < 10; i++) {
        int dist2 = getDistance();
        totalDist += dist2;
        delay(1);
    }
    int avgDist = totalDist / 10;

    return avgDist;
}

void loop() {
    // distance = getDistAvg();
    distance = 100;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("cm ");

    if (distance < 12) {
        digitalWrite(rLED, 1);
        digitalWrite(gLED, 0);
        tone(buzzerPin, 1000);

        digitalWrite(relayPin, 0);
    } else if (distance >= 12) {
        digitalWrite(rLED, 0);
        digitalWrite(gLED, 1);
        noTone(buzzerPin);

        digitalWrite(relayPin, 1);
    }

    delay(100);
}