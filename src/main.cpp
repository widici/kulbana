#include <Arduino.h>
#include <Servo.h>

const int POT_PINS[3] = {0, 1, 2};
const int SERVO_PINS[3] = {9, 10, 11};
Servo servos[3];

const int WIN_PIN = 12;
const int FINISH_PIN = 13;
bool has_won = false;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 3; ++i) {
        servos[i].attach(SERVO_PINS[i]);
    }
    pinMode(WIN_PIN, INPUT);
    pinMode(FINISH_PIN, INPUT);
}

void loop() {
    for (int i = 0; i < 3; i++) {
        int val = analogRead(POT_PINS[i]);
        val = map(val, 0, 1023, 0, 180);
        servos[i].write(val);
    }
    if (digitalRead(WIN_PIN) == HIGH) {
        has_won = true;
    }
    if (digitalRead(FINISH_PIN) == HIGH) {
        if (has_won) {
            Serial.println("WON");
            exit(0);
        }
        Serial.println("RESTART");
    }
    delay(15);
}