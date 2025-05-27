#include <Arduino.h>
#include <Servo.h>

const int N_SERVOS = 3;
const int POT_PINS[N_SERVOS] = {A0, A1, A2};
const int SERVO_PINS[N_SERVOS] = {6, 5, 3};
Servo servos[N_SERVOS];

const int LIGHT_THRESHOLD = 150;
const int WIN_PIN = A3;

const int IN_PIN = 12;
const int OUT_PIN = 13;
const int DELAY = 5;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < N_SERVOS; ++i) {
        servos[i].attach(SERVO_PINS[i]);
    }
    reset();
    pinMode(WIN_PIN, INPUT);
    pinMode(IN_PIN, INPUT);
    pinMode(OUT_PIN, OUTPUT);
}

void loop() {
    while (digitalRead(IN_PIN) == LOW) {
        delay(DELAY);
    }
    for (int i = 0; i < N_SERVOS; i++) {
        int val = analogRead(POT_PINS[i]);
        val = map(val, 0, 1023, 0, 180);
        servos[i].write(val);
    }
    if (analogRead(WIN_PIN) <= LIGHT_THRESHOLD) {
        Serial.println("WON");
        digitalWrite(OUT_PIN, HIGH);
        delay(3000);  // Sleeps for 3 secs
        digitalWrite(OUT_PIN, LOW);
        reset();
    }
    delay(DELAY);
}

void reset() {
    for (int i = 0; i < N_SERVOS; i++) {
        servos[i].write(90);
    }
}