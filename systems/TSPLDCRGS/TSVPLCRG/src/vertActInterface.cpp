#include "vertActInterface.h"

VertActInterface::VertActInterface(void) {}

VertActInterface::~VertActInterface(void) {}

//========================================================
//=========== Public Functions ===========================
//========================================================

/*********************************************************
 * 
 * Name:  VActInterfaceTaskLauncher
 * Notes: See controller.h
 * 
 *********************************************************/
void VertActInterface::VActInterfaceTaskLauncher() {
    xTaskCreate(
        processInfoStatic,              // Function to be called
        "processInfoStatic",            // Name of the task
        6000,                           // Stack size
        this,                           // Parameters passed to task
        2,                              // Task priority (higher number = higher priority)
        NULL                            // Task handle for reference
    );
}

//========================================================
//=========== Private Functions ==========================
//========================================================

/*********************************************************
 * 
 * Name:  init
 * Notes: See controller.h
 * 
 *********************************************************/
void VertActInterface::init(void) {
    // /* Initialise the sensor */
    // if(!bno.begin())
    // {
    //     /* There was a problem detecting the BNO055 ... check your connections */
    //     printf("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    //     while(1);
    // }
    
    vTaskDelay(1000);
}

/*********************************************************
 * 
 * Name:  processInfo
 * Notes: See controller.h
 * 
 *********************************************************/
void VertActInterface::processInfo() {

    init();

    while(1) {
        // /* Get a new sensor event */ 
        // sensors_event_t event; 
        // bno.getEvent(&event);
        
        // /* Display the floating point data */
        // printf("X: %.4f, Y: %.4f, Z: %.4f\n", event.orientation.x,event.orientation.y, event.orientation.z);
        
        // printf("VertActInterface Hit!\n");

        vTaskDelay(I_VERT_ACT_DELAY_8HZ);
    }
    
    // EOL for Vert Act task
    vTaskDelete( NULL );
}

/*********************************************************
 * 
 * Name:  processInfoStatic
 * Notes: See controller.h
 * 
 *********************************************************/
void VertActInterface::processInfoStatic(void *pvParams) {
    // Retrieve the singleton instance of the VertActInterface class.
    // This ensures that only one instance of VertActInterface exists 
    // and is used throughout the program.

    VertActInterface *vActInterface = static_cast<VertActInterface *>(pvParams);
    vActInterface->processInfo();
}