#ifndef IMUINTERFACE_H
#define IMUINTERFACE_H

#include <Adafruit_BNO055.h>            // Adafruit_BNO055
#include <Wire.h>

#include "taskGlobals.h"                // TASK_DELAY_8HZ


// Telemetry and Thruster Control Interface
class SensorInterface {

public:

    SensorInterface(void);
    ~SensorInterface(void);

    /*********************************************************
     * 
     * Name:  TTCTaskLauncher
     * Notes: n/a
     * 
     *********************************************************/
    void SensorTaskLauncher(void);

private:
    SemaphoreHandle_t   sohMutex;
    SemaphoreHandle_t   thruserBinarySemaphore;

    Adafruit_BNO055     bno;
    QueueHandle_t       gSensorQueue;
    
    TwoWire I2C_1 = TwoWire(0);
    TwoWire I2C_2 = TwoWire(1);

    static constexpr uint8_t AS5600_ADDR = 0x36;

    /*********************************************************
     * 
     * Name:  init
     * Notes: initialize parameters
     * 
     *********************************************************/
    void init(void);

    /*********************************************************
     * 
     * Name:  processInfo
     * Notes: process information, main loop
     * 
     *********************************************************/
    void processInfo();

    /*********************************************************
     * 
     * Name:  readRawAngle
     * Notes: -
     * 
     *********************************************************/
    uint16_t readRawAngle_1();
    uint16_t readRawAngle_2();
    
    /*********************************************************
     * 
     * Name:  processInfoStatic
     * Notes: create static instance if it doesn't exist
     * 
     *********************************************************/
    static void processInfoStatic(void *pvParams);    
};

#endif // IMUINTERFACE_H