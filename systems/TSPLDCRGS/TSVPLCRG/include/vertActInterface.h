#ifndef VERTACTINTERFACE_H
#define VERTACTINTERFACE_H

#include <Adafruit_BNO055.h>            // Adafruit_BNO055

#include "taskGlobals.h"                // TASK_DELAY_8HZ

// Telemetry and Thruster Control Interface
class VertActInterface {

public:

    VertActInterface(void);
    ~VertActInterface(void);

    /*********************************************************
     * 
     * Name:  TTCTaskLauncher
     * Notes: n/a
     * 
     *********************************************************/
    void VActInterfaceTaskLauncher(void);

private:
    // SemaphoreHandle_t   sohMutex;
    // SemaphoreHandle_t   thruserBinarySemaphore;

    Adafruit_BNO055     bno;

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
    void processVertActInfo();

    /*********************************************************
     * 
     * Name:  onStepTimer
     * Notes: See controller.h
     * 
     *********************************************************/
    bool isMoving();
    void stopMotor();
    void moveSteps(uint32_t steps, bool dir);
    void setupTimer(uint32_t intervalUs);

    /*********************************************************
     * 
     * Name:  processInfoStatic
     * Notes: create static instance if it doesn't exist
     * 
     *********************************************************/
    static void processInfoStatic(void *pvParams);    
};

// Not in class
void IRAM_ATTR onStepTimer();

#endif // VERTACTINTERFACE_H