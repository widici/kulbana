#include <Arduino.h>
#include <Servo.h>

const int N_SERVOS = 3;
const int POT_PINS[N_SERVOS] = {A0, A1, A2};
const int SERVO_PINS[N_SERVOS] = {6, 5, 3};
Servo servos[N_SERVOS];

const int LIGHT_THRESHOLD = 150;
const int WIN_PIN = A3;
const int FINISH_PIN = A4;
bool has_won = false;

const int IN_PIN = 12;
const int OUT_PIN = 13;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < N_SERVOS; ++i) {
        servos[i].attach(SERVO_PINS[i]);
    }
    reset();
    pinMode(WIN_PIN, INPUT);
    pinMode(FINISH_PIN, INPUT);
}

void loop() {
    while (digitalRead(12) == LOW) {
        delay(10);
    }
    for (int i = 0; i < N_SERVOS; i++) {
        int val = analogRead(POT_PINS[i]);
        val = map(val, 0, 1023, 0, 180);
        servos[i].write(val);
    }
    if (analogRead(WIN_PIN) <= LIGHT_THRESHOLD) {
        has_won = true;
    }
    if (analogRead(FINISH_PIN) <= LIGHT_THRESHOLD) {
        if (has_won) {
            Serial.println("WON");
            digitalWrite(OUT_PIN, HIGH);
            delay(3000);  // Sleeps for 3 secs
            digitalWrite(OUT_PIN, LOW);
            has_won = false;
        }
        Serial.println("RESET");
        reset();
    }
    delay(15);
}

void reset() {
    for (int i = 0; i < N_SERVOS; i++) {
        servos[i].write(90);
    }
}