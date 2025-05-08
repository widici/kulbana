#include <Arduino.h>
#include <Servo.h>

int pot_pins[3] = {0, 0, 0};
int servo_pins[3] = {9, 9, 9};
Servo servos[3];

void setup() {
    for (int i = 0; i < 3; ++i) {
        servos[i].attach(servo_pins[i]);
    }
}

void loop() {
    for (int i = 0; i < 3; i++) {
        int val = analogRead(pot_pins[i]);
        val = map(val, 0, 1023, 0, 180);
        servos[i].write(val);
        delay(15);
    }
}