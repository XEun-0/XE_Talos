#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// below is for stepper motor
// #define PUL 5
// #define DIR 6
// #define ENA_2 7

// const long pulsePerRev = 6400;
// int pDelay = 200;

// void setup() {
//     pinMode(PUL, OUTPUT);
//     pinMode(DIR, OUTPUT);

//     digitalWrite(DIR, LOW);
//     digitalWrite(ENA_2, HIGH);
// }

// void loop() {
//     digitalWrite(DIR, LOW);
//     digitalWrite(ENA_2, HIGH);

//     for (long i = 0; i < pulsePerRev; i++) {
//         digitalWrite(PUL, HIGH);
//         delayMicroseconds(pDelay);
//         digitalWrite(PUL, LOW);
//         delayMicroseconds(pDelay);
//     }



//     delay(5000);

//     digitalWrite(ENA_2, LOW);
//     delay(5000);
// }
#define DECLARE_GLOBALS
#include "globals.h"
#include "taskGlobals.h"

#define ENA_2 4
#define IN_3 5
#define IN_4 18

#define ENA_1 15
#define IN_1 17
#define IN_2 16

// PWM config
const int pwmFreq = 10000;
const int pwmResolution = 8;

// Separate channels
const int pwmChannel_1 = 0;
const int pwmChannel_2 = 1;

Adafruit_BNO055 bno = Adafruit_BNO055(55);

// Motor 2 (your original)
void setMotor2(int speed, uint8_t dirBits) {
    digitalWrite(IN_3, dirBits & 0x01);
    digitalWrite(IN_4, (dirBits >> 1) & 0x01);
    ledcWrite(pwmChannel_2, speed);
}

// Motor 1 (new)
void setMotor1(int speed, uint8_t dirBits) {
    digitalWrite(IN_1, dirBits & 0x01);
    digitalWrite(IN_2, (dirBits >> 1) & 0x01);
    ledcWrite(pwmChannel_1, speed);
}

void setup() {
    // Direction pins
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);

    // PWM setup
    ledcSetup(pwmChannel_1, pwmFreq, pwmResolution);
    ledcAttachPin(ENA_1, pwmChannel_1);

    ledcSetup(pwmChannel_2, pwmFreq, pwmResolution);
    ledcAttachPin(ENA_2, pwmChannel_2);

    // Start stopped
    setMotor1(0, 0b00);
    setMotor2(0, 0b00);

    Serial.begin(115200);
    Serial.println("Orientation Sensor Test"); Serial.println("");
  
    /* Initialise the sensor */
    if(!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    
    delay(1000);
        
    bno.setExtCrystalUse(true);
}

void loop() {

    /* Get a new sensor event */ 
    sensors_event_t event; 
    bno.getEvent(&event);
    
    /* Display the floating point data */
    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.print(event.orientation.z, 4);
    Serial.println("");
    
    delay(100);

    // // This is downward
    // setMotor1(55, 0b01);
    // setMotor2(60, 0b01);
    // delay(500);

    // // Both reverse
    // setMotor1(65, 0b10);
    // setMotor2(70, 0b10);
    // delay(600);

    // // Brake
    // setMotor1(0, 0b00);
    // setMotor2(0, 0b00);
    // delay(2000);

    // // Coast
    // setMotor1(0, 0b11);
    // setMotor2(0, 0b11);
    // delay(2000);
}