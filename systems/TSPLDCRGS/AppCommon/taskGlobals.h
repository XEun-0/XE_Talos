#ifndef TASKGLOBALS_H
#define TASKGLOBALS_H

#pragma once
#include <Arduino.h>

//========================================================
//=========== Delays =====================================
//========================================================
#define TASK_DELAY_8HZ                      pdMS_TO_TICKS(125)
#define MAIN_CONTROLLER_TASK_DELAY_10HZ     pdMS_TO_TICKS(100)

#define TEN_SECONDS_DELAY                   pdMS_TO_TICKS(10000) 
#define FIVE_SECONDS_DELAY                  pdMS_TO_TICKS(5000) 
#define SYS_BAUD_RATE                       115200

//========================================================
//=========== Misc =======================================
//========================================================
#define SDA_PIN_1 8
#define SCL_PIN_1 9
#define SDA_PIN_2 17
#define SCL_PIN_2 16
// #define AS5600_ADDR 0x36

// Actuators
#define PUL_A 5 // subject to change
#define DIR_A 6
#define ENA_A 7

#define PUL_B 5
#define DIR_B 6
#define ENA_B 7

extern hw_timer_t          *timer;
extern volatile bool        motorEnabled;
extern volatile uint32_t    stepsRemaining;
extern volatile bool        direction;

extern portMUX_TYPE         timerMux;

//========================================================
//=========== Queues =====================================
//========================================================
extern QueueHandle_t gSensorQueue;

#endif // TASKGLOBALS_H