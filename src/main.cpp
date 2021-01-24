/*
Car Crash Avoidance System

Author: Mukhtar Zotder | 2021
URL: https://github.com/mukhtarzotder/auto-crash-avoiding-system
License: MIT
*/

#include <Arduino.h>

#define triger D1
#define echo D0
#define buzzer D5
#define ENA D2
#define IN1 D8
#define IN2 D7

#define redLED D4
#define greenLED D6

int isStopped = 0;

void ledSelect(int led) {
    if (led == 0) {
        digitalWrite(redLED, 1);
        digitalWrite(greenLED, 0);
    } else if (led == 1) {
        digitalWrite(redLED, 0);
        digitalWrite(greenLED, 1);
    }
}

int getDistance() {
    int distance;
    long duration;

    digitalWrite(triger, 0);
    delayMicroseconds(2);
    digitalWrite(triger, 1);
    delayMicroseconds(10);
    digitalWrite(triger, 0);

    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}

int getDistanceAvg() {
    int totalDist = 0;

    for (int i = 0; i < 10; i++) {
        int dist = getDistance();
        totalDist += dist;

        delayMicroseconds(100);
    }

    return (int)(totalDist / 10);
}

void Buzzer() {
    tone(buzzer, 3000, 1000);
}

void backCar() {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    analogWrite(ENA, 300);

    // delay(200);

    // isStopped = 1;
}

void runCar(int value) {
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    if (value == 1) {
        analogWrite(ENA, 360);
        isStopped = 0;
    } else if (value == 0) {
        if (isStopped == 0) {
            backCar();
            Buzzer();
        }
        delay(200);

        isStopped = 1;

        analogWrite(ENA, 0);
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(triger, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);

    delay(3500);      // for starting the car
}

void loop() {
    int dist = getDistanceAvg();
    Serial.print("Distance: ");
    Serial.print(dist);
    Serial.println(" cm");

    if (dist >= 8 && dist <= 100) {
        ledSelect(1);
        runCar(1);
    } else {
        ledSelect(0);
        runCar(0);
        // Buzzer();
    }

    delay(100);
}