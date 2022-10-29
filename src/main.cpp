#include "Arduino.h"

// Pins connect as per define
// Fill in the pins you used on your own setup.
#if 0
ORIGINAL
#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3
#endif

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
byte star1[] = {B00000110,B11000010,B10100100,B00011000,B00011000,B00100101,B01000011,B01100000};
byte star2[] = {B00110000,B00100000,B00100111,B00011001,B10011000,B11100100,B00000100,B00001100};
byte star3[] = {B00000110,B10001000,B10010000,B01011100,B00111010,B00001001,B00010001,B01100000};
byte heart[] = {B01100110, B10111101, B10011001, B10000001, B01000010, B01100110, B00111100, B00011000};

size_t timeCount = 0;
size_t loop_index = 0;


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

void setRows(byte b) {
    digitalWrite(ROW_1, (b >> 0) & 0x01); // Get the 1st bit: 10000000
    digitalWrite(ROW_2, (b >> 1) & 0x01); // Get the 2nd bit: 01000000
    digitalWrite(ROW_3, (b >> 2) & 0x01); // Get the 3rd bit: 00100000
    digitalWrite(ROW_4, (b >> 3) & 0x01); // Get the 4th bit: 00010000
    digitalWrite(ROW_5, (b >> 4) & 0x01); // Get the 5th bit: 00001000
    digitalWrite(ROW_6, (b >> 5) & 0x01); // Get the 6th bit: 00000100
    digitalWrite(ROW_7, (b >> 6) & 0x01); // Get the 7th bit: 00000010
    digitalWrite(ROW_8, (b >> 7) & 0x01); // Get the 8th bit: 00000001

    // If the polarity of your matrix is the opposite of mine
    // remove all the '~' above.
}

void  drawScreen(byte buffer2[], byte begin, byte end){
    // Turn on each row in series
    for (byte i = 0; i < 8; i++) {
        if (i != begin && i < (8 - end)) {
            continue;
        }
        setColumns(buffer2[i]); // Set columns for this specific row

        digitalWrite(rows[i], HIGH);
        delay(2); // Set this to 50 or 100 if you want to see the multiplexing effect!
        digitalWrite(rows[i], LOW);
    }
}

void setup() {
    // Open serial port
    Serial.begin(9600);

    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    for (byte i = 2; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    //for (byte i = 2; i <= 13; i++)
    //    digitalWrite(i, LOW);
    //digitalWrite(A0, LOW);
    //digitalWrite(A1, LOW);
    //digitalWrite(A2, LOW);
    //digitalWrite(A3, LOW);

    //digitalWrite(COL_1, LOW);
    //digitalWrite(COL_2, LOW);
    //digitalWrite(COL_3, LOW);
    //digitalWrite(COL_4, LOW);
    //digitalWrite(COL_5, LOW);
    //digitalWrite(COL_6, LOW);
    //digitalWrite(COL_7, LOW);
    //digitalWrite(COL_8, LOW);

    //digitalWrite(ROW_1, HIGH);
    //digitalWrite(ROW_2, HIGH);
    //digitalWrite(ROW_3, HIGH);
    //digitalWrite(ROW_4, HIGH);
    //digitalWrite(ROW_5, HIGH);
    //digitalWrite(ROW_6, HIGH);
    //digitalWrite(ROW_7, HIGH);
    //digitalWrite(ROW_8, HIGH);
    //setColumns(0xff);
    //digitalWrite(2, HIGH);
    //setRows(B00000000);
}

void loop() {
    delay(5);

    timeCount += 1;

    if(timeCount <  20 - loop_index * 1) {
        drawScreen(heart, 0, loop_index);
    } else if (timeCount <  39 - loop_index * 2  && loop_index < 7) {
        drawScreen(heart, 1, loop_index);
    } else if (timeCount <  57 - loop_index * 3  && loop_index < 6) {
        drawScreen(heart, 2, loop_index);
    } else if (timeCount <  74- loop_index * 6  && loop_index < 5) {
        drawScreen(heart, 3, loop_index);
    } else if (timeCount <  90 - loop_index * 8  && loop_index < 4) {
        drawScreen(heart, 4, loop_index);
    } else if (timeCount <  105 - loop_index * 10  && loop_index < 3) {
        drawScreen(heart, 5, loop_index);
    } else if (timeCount <  119 - loop_index * 12  && loop_index < 2) {
        drawScreen(heart, 6, loop_index);
    } else if (timeCount <  132 - loop_index * 16 && loop_index < 1) {
        drawScreen(heart, 7, loop_index);
    } else {
        // back to the start
        timeCount = 0;
        loop_index = (loop_index + 1) % 8;
    }
}



#if 0

int DHpin = 8; // input/output pin
byte dat[5];
byte read_data()
{
    byte i = 0;
    byte result = 0;
    for (i = 0; i < 8; i++) {
        while (digitalRead(DHpin) == LOW); // wait 50us
        delayMicroseconds(30); //The duration of the high level is judged to determine whether the data is '0' or '1'
        if (digitalRead(DHpin) == HIGH)
            result |= (1 << (8 - i)); //High in the former, low in the post
        while (digitalRead(DHpin) == HIGH); //Data '1', waiting for the next bit of reception
    }
    return result;
}
void start_test()
{
    digitalWrite(DHpin, LOW); //Pull down the bus to send the start signal
    delay(30); //The delay is greater than 18 ms so that DHT 11 can detect the start signal
    digitalWrite(DHpin, HIGH);
    delayMicroseconds(40); //Wait for DHT11 to respond
    pinMode(DHpin, INPUT);
    while(digitalRead(DHpin) == HIGH);
    delayMicroseconds(80); //The DHT11 responds by pulling the bus low for 80us;

    if(digitalRead(DHpin) == LOW)
        delayMicroseconds(80); //DHT11 pulled up after the bus 80us to start sending data;
    for(int i = 0; i < 5; i++) //Receiving temperature and humidity data, check bits are not considered;
        dat[i] = read_data();
    pinMode(DHpin, OUTPUT);
    digitalWrite(DHpin, HIGH); //After the completion of a release of data bus, waiting for the host to start the next signal
}
void setup()
{
    Serial.begin(9600);
    pinMode(DHpin, OUTPUT);
}
void loop()
{
    start_test();
    Serial.print("Humdity = ");
    Serial.print(dat[0], DEC); //Displays the integer bits of humidity;
    Serial.print('.');
    Serial.print(dat[1], DEC); //Displays the decimal places of the humidity;
    Serial.println('%');
    Serial.print("Temperature = ");
    Serial.print(dat[2], DEC); //Displays the integer bits of temperature;
    Serial.print('.');
    Serial.print(dat[3], DEC); //Displays the decimal places of the temperature;
    Serial.println('C');
    byte checksum = dat[0] + dat[1] + dat[2] + dat[3];
    if (dat[4] != checksum)
        Serial.println("-- Checksum Error!");
    else
        Serial.println("-- OK");

    delay(1000);
}

#endif
#if 0
#include "../.pio/libdeps/uno/Servo/src/Servo.h"
#include "Arduino.h"

Servo servo;

int servoAngle;
const int leftButtonPin = 2;
const int rightButtonPin = 4;
const int servoAngleMax = 180;
const int servoAngleMin = 0;
const int servoAngleIncrement = 5;

void setup() {
    pinMode(leftButtonPin, INPUT);
    servo.attach(9);
    servoAngle = 90;
}

int next()
{
    if (servoAngle + servoAngleIncrement >= servoAngleMax) {
        servoAngle = servoAngleMax;
    } else {
        servoAngle += servoAngleIncrement;
    }
    return servoAngle;
}

int prev()
{
    if (servoAngle <= servoAngleIncrement) {
        servoAngle = 0;
    } else {
        servoAngle -= servoAngleIncrement;
    }
    return servoAngle;
}

void loop() {
    if (digitalRead(leftButtonPin) == HIGH) {
        servo.write(prev());
    } else {
        if (digitalRead(rightButtonPin) == HIGH) {
            servo.write(next());
        }
    }
    delay(50);
}
#endif
#if 0
int next()
{
    servoAngle = (servoAngle + 20) % 360;
    return servoAngle < 180 ? servoAngle : 360 - servoAngle;
}

int prev()
{
    servoAngle = (servoAngle + 340) % 360;
    return servoAngle < 180 ? servoAngle : 360 - servoAngle;
}
#endif

#if 0
servo.write(next());
    delay(200);
    servo.write(next());
    delay(200);
    servo.write(prev());
    delay(200);
    servo.write(prev());
    delay(200);
    servo.write(next());
    delay(300);
    servo.write(next());
    delay(600);
#endif

#if 0
Serial.println("kek");
    delay(1000);
    static int kek = 0;
    static int a = 0;

    kek += ((++a % 10) == 0);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(kek % 2);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(15);                       // wait for a second
#endif

#if 0
int address;
    for (address = 64; address < 0x7f; address++) {
        rc = Wire.requestFrom(address, 1);
        if (rc != 0)
            break;
    }
    if (address == 0x7f)
        Serial.println("Not found");
    else {
        Serial.print("Found: ");
        Serial.println(address);
        Serial.print("rc: ");
        Serial.println(rc);
    }
#endif

#if 0
command: pio run -t upload && pio device monitor -b 9600 -p COM7
#endif