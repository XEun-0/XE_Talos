#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>

// Declare globals as extern in this file
// while declaring actually for other files
// global header without macro is called in
// controller.h
#define DECLARE_GLOBALS
#include "globals.h"            // gVActInterface

#include "taskGlobals.h"        // SYS_BAUD_RATE
#include "controller.h"         // controllerTaskLauncher

/*********************************************************
 * 
 * Name:  setup
 * Notes: Arduino way of starting application task
 * 
 *********************************************************/
void setup() {
    Serial.begin(SYS_BAUD_RATE);

    // Create main controller task
    xTaskCreate(
        controllerTaskLauncher,             // Function to be called
        "controllerTaskLauncher",           // Name of the task
        5000,                               // Stack size
        NULL,                               // Parameters passed to task
        1,                                  // Task priority (higher number = higher priority)
        NULL                                // Task handle for reference
    );

    gVActInterface.VActInterfaceTaskLauncher();
    gIMUInterface.ImuTaskLauncher();
    // No need to start scheduler
}

/*********************************************************
 * 
 * Name:  loop
 * Notes: RTOS removes loop functionality
 * 
 *********************************************************/
void loop() {}