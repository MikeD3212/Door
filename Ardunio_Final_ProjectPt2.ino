#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Keypad.h>
#include <Servo.h>

//________________________________________________
Servo myservo;
int pos = 0;
//________________________________________________

const byte ROWS = 4;
const byte COLS = 3;
String password = "1234";

char keypressed;
String pad = "";

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {41, 43, 45};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
    Serial.begin(9600);
    myservo.attach(9);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
}

void loop() {
    readKeypad();
    if (keypressed == '#') {
        if (pad == password) {
            Serial.println("Access Granted");
            digitalWrite(11, HIGH);

            // Move the servo from 0 to 90 degrees
            for (pos = 0; pos <= 90; pos++) {
                myservo.write(pos);
                delay(15);
            }
            delay(10000); // You can adjust the delay here if needed.

            digitalWrite(11, LOW); // Turn off the LED
            // Move the servo back to 0 degrees
            for (pos = 90; pos >= 0; pos--) {
                myservo.write(pos);
                delay(15);
            }
            delay(1000); // You can adjust the delay here if needed.
        } else {
            Serial.println("Access Denied");
            tone(10, 370);
            delay(1000);
            digitalWrite(11, LOW);
            digitalWrite(12, HIGH);
            delay(500);
            digitalWrite(12, LOW);
            delay(500);
            digitalWrite(12, HIGH);
            delay(500);
            digitalWrite(12, LOW);
            delay(500);
            digitalWrite(12, HIGH);
            delay(500);
            digitalWrite(12, LOW);
            delay(500);
            digitalWrite(12, HIGH);
        }
    }
    if (keypressed == '*') {
        pad = "";
        Serial.println("________________________________________");
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        noTone(10);
        digitalWrite(10, LOW);
    }
}

void readKeypad() {
    keypressed = customKeypad.getKey();
    if (keypressed != '\0' && keypressed != '#' && keypressed != '*') {
        pad += keypressed;
    }
}
