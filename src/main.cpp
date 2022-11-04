#include "Arduino.h"

// Pins connect as per define
// Fill in the pins you used on your own setup.
#define ROW_1 2
#define ROW_2 3
#define ROW_3 7
#define ROW_4 A2
#define ROW_5 8
#define ROW_6 13
#define ROW_7 12
#define ROW_8 5
#define COL_1 A3
#define COL_2 11
#define COL_3 A1
#define COL_4 10
#define COL_5 6
#define COL_6 A0
#define COL_7 4
#define COL_8 9

const byte rows[] = {
        ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};

// The display buffer
// It shows a walking steps (1 = ON, 0 = OFF)
byte heart[] = {B01100110, B10111101, B10011001, B10000001, B01000010, B01100110, B00111100, B00011000};

void setColumns(byte b) {
    digitalWrite(COL_1, (~b >> 0) & 0x01); // Get the 1st bit: 10000000
    digitalWrite(COL_2, (~b >> 1) & 0x01); // Get the 2nd bit: 01000000
    digitalWrite(COL_3, (~b >> 2) & 0x01); // Get the 3rd bit: 00100000
    digitalWrite(COL_4, (~b >> 3) & 0x01); // Get the 4th bit: 00010000
    digitalWrite(COL_5, (~b >> 4) & 0x01); // Get the 5th bit: 00001000
    digitalWrite(COL_6, (~b >> 5) & 0x01); // Get the 6th bit: 00000100
    digitalWrite(COL_7, (~b >> 6) & 0x01); // Get the 7th bit: 00000010
    digitalWrite(COL_8, (~b >> 7) & 0x01); // Get the 8th bit: 00000001

    // If the polarity of your matrix is the opposite of mine
    // remove all the '~' above.
}

void drawScreen(byte buffer2[], byte begin, byte end) {
    size_t budget = 0;
    while (budget < 50) {
        // Turn on each row in series
        for (byte i = 0; i < 8; i++) {
            if (i != begin && i < (8 - end)) {
                continue;
            }
            budget++;
            setColumns(buffer2[i]); // Set columns for this specific row

            digitalWrite(rows[i], HIGH);
            delay(2); // Set this to 50 or 100 if you want to see the multiplexing effect!
            digitalWrite(rows[i], LOW);
        }
    }
}

void setup() {
    // Open serial port
    Serial.begin(9600);

    // Set all used pins to OUTPUT
    for (byte i = 2; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
}

void loop() {
    for (size_t loop_index = 0; loop_index < 8; ++loop_index) {
        for (size_t i = 0; i < 8 - loop_index; ++i) {
            drawScreen(heart, i, loop_index);
        }
    }
    drawScreen(heart, 0, 8);
    drawScreen(heart, 0, 8);
    drawScreen(heart, 0, 8);
    drawScreen(heart, 0, 8);
}