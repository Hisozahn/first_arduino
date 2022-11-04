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

const byte columns[] = {
        COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

const byte rows[] = {
        ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};

#define MATRIX_ROWS_SIZE (sizeof(rows) / sizeof(rows[0]))
#define MATRIX_COLUMN_SIZE (sizeof(columns) / sizeof(columns[0]))
#define DRAW_FRAME_TIME_BUDGET 50
#define DRAW_ROW_TIME_WINDOW_MS 2

// The display buffer
// It shows a walking steps (1 = ON, 0 = OFF)
byte draw_buffer[] = {B01100110, B10111101, B10011001, B10000001, B01000010, B01100110, B00111100, B00011000};


void setColumns(byte b) {
    for (size_t i = 0; i < MATRIX_COLUMN_SIZE; ++i) {
        digitalWrite(columns[i], (~b >> i) & 0x01); // Get all bits from byte
    }
}

void drawScreen(size_t begin, size_t end) {
    size_t budget = 0;
    while (budget < DRAW_FRAME_TIME_BUDGET) {
        // Turn on each row in series
        for (size_t i = 0; i < MATRIX_ROWS_SIZE; i++) {
            if (i != begin && i < (MATRIX_ROWS_SIZE - end)) {
                continue;
            }
            budget++;
            setColumns(draw_buffer[i]); // Set columns for this specific row

            digitalWrite(rows[i], HIGH);
            delay(DRAW_ROW_TIME_WINDOW_MS);
            digitalWrite(rows[i], LOW);
        }
    }
}

void setup() {
    // Open serial port
    Serial.begin(9600);

    // Set all used pins to OUTPUT
    for (byte pin : rows) {
        pinMode(pin, OUTPUT);
    }
    for (byte pin : columns) {
        pinMode(pin, OUTPUT);
    }
}

void loop() {
    for (size_t loop_index = 0; loop_index < MATRIX_ROWS_SIZE; ++loop_index) {
        for (size_t i = 0; i < MATRIX_ROWS_SIZE - loop_index; ++i) {
            drawScreen(i, loop_index);
        }
    }
    for (size_t i = 0; i < 4; ++i) {
        drawScreen(0, 8);
    }
}