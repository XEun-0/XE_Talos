#include "controller.h"
#include "taskGlobals.h"

#include <cstddef>
#include <Arduino.h>
// #include <Adafruit_BNO055.h>

//====== Initialize Variables ============================

Controller *Controller::instance = nullptr;
// Adafruit_BNO055 bno = Adafruit_BNO055(55);

//========================================================

/*********************************************************
 * 
 * Name:  Controller
 * Notes: See controller.h
 * 
 *********************************************************/
Controller::Controller(void) {

}

/*********************************************************
 * 
 * Name:  ~Controller
 * Notes: See controller.h
 * 
 *********************************************************/
Controller::~Controller(void) {

}

/*********************************************************
 * 
 * Name:  getInstance
 * Notes: See controller.h
 * 
 *********************************************************/
Controller *Controller::getInstance (void) {
    if (Controller::instance == nullptr) {
        Controller::instance = new Controller();
        Controller::instance->init(); // may not be needed
    }

    return Controller::instance;
}

/*********************************************************
 * 
 * Name:  init
 * Notes: See controller.h
 * 
 *********************************************************/
void Controller::init(void) {

}

/*********************************************************
 * 
 * Name:  mainLoop
 * Notes: See controller.h
 * 
 *********************************************************/
void Controller::mainLoop(void) {

    while(1) {
        
        TickType_t startTick = xTaskGetTickCount();
        TickType_t currTick = xTaskGetTickCount();

        vTaskDelay(MAIN_CONTROLLER_TASK_DELAY_10HZ);
    }

    // Send error code serial msg if needed.
    vTaskDelete( NULL );
}

// Not in class

/*********************************************************
 * 
 * Name:  controllerTaskLauncher
 * Notes: See controller.h
 * 
 *********************************************************/
void controllerTaskLauncher( void *pvParams ) {
    // Retrieve the singleton instance of the Controller class.
    // This ensures that only one instance of Controller exists 
    // and is used throughout the program.

    Controller *pController = Controller::getInstance();
    pController->mainLoop();
}

