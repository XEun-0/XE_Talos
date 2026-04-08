#include "controller.h"
#include "taskGlobals.h"        // TEN_SECONDS_DELAY
// #include "pPrintf.h"
#include <cstddef>
#include <Arduino.h>
#include <Adafruit_BNO055.h>

//====== Initialize Variables ============================

Controller *Controller::instance = nullptr;
Adafruit_BNO055 bno = Adafruit_BNO055(55);

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
    
    /* Initialise the sensor */
    if(!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    
    vTaskDelay(1000);
        
    bno.setExtCrystalUse(true);

    while(1) {
        TickType_t startTick = xTaskGetTickCount();
        TickType_t currTick = xTaskGetTickCount();

        /* Get a new sensor event */ 
        sensors_event_t event; 
        bno.getEvent(&event);
        
        /* Display the floating point data */
        printf("X: %.4f, Y: %.4f, Z: %.4f\n", event.orientation.x,event.orientation.y, event.orientation.z);

        vTaskDelay(MAIN_CONTROLLER_TASK_DELAY_10HZ);
    }

    // Send error code serial msg if needed.
    vTaskDelete( NULL );
}

/*********************************************************
 * 
 * Name:  getSendSOHSerial
 * Notes: See controller.h
 * 
 *********************************************************/
// void Controller::getSendSOHSerial(void) {
//     TTCSohRespType ttcSoh;
//     memset(&ttcSoh, 0, sizeof(TTCSohRespType));

//     // What is SOH - State of Health
//     // Stats and information about the specific component 
//     // in question. i.e. Sensors, Thrusters
//     gTTCInterface.gatherSensorSOH(&ttcSoh);

//     gTTCInterface.gatherThrusterSOH(&ttcSoh);
    
//     #if !defined(SERIAL_OUT)
//     Serial.write((uint8_t *)&ttcSoh, sizeof(TTCSohRespType));
//     #else
//     // char avr_buffer[100];

//     // char floatX[10], floatY[10], floatZ[10];
//     // dtostrf(ttcSoh.sensorInfo.imuOrientX, 6, 2, floatX); // Width 6, 2 decimal places
//     // dtostrf(ttcSoh.sensorInfo.imuOrientY, 6, 2, floatY);
//     // dtostrf(ttcSoh.sensorInfo.imuOrientZ, 6, 2, floatZ);

//     // sprintf(avr_buffer, "X: %s, Y: %s, Z: %s", floatX, floatY, floatZ);
//     // Serial.println(avr_buffer);
//     #endif

//     // process msg before sending out

//     #if SERIAL_OUT
//     hexDump((uint8_t *)&ttcSoh, sizeof(TTCSohRespType));
//     checkStructSizes();
//     #endif

//     // Serial.println(ttcSoh.sensorInfo.imuOrientX);
// }

/*********************************************************
 * 
 * Name:  rxSerialCommands
 * Notes: See controller.h
 * 
 *********************************************************/
// void Controller::rxSerialCommands(void) {
//     // From Serial comms recieve commands and 
//     // populate command struct for TTCInterface
//     // tasking

//     ThrusterCommandsType rxThrusterCmds;
    
//     // Serial.read something and store in buffer
//     gTTCInterface.doThrusterCommands(rxThrusterCmds);
// }

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

