#ifndef VERTACTINTERFACE_H
#define VERTACTINTERFACE_H

#include <Adafruit_BNO055.h>            // Adafruit_BNO055

#include "taskGlobals.h"                // I_VERT_ACT_DELAY_8HZ

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
    SemaphoreHandle_t   sohMutex;
    SemaphoreHandle_t   thruserBinarySemaphore;

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
    void processInfo();

    /*********************************************************
     * 
     * Name:  processInfoStatic
     * Notes: create static instance if it doesn't exist
     * 
     *********************************************************/
    static void processInfoStatic(void *pvParams);    
};

#endif // VERTACTINTERFACE_H