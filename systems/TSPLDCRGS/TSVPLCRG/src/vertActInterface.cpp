#include "vertActInterface.h"

hw_timer_t         *timer           = NULL;
volatile bool       motorEnabled    = false;
volatile uint32_t   stepsRemaining  = 0;
volatile bool       direction       = true;

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

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
    
    printf("VertActInterface::init\n");

    pinMode(PUL_B, OUTPUT);
    pinMode(DIR_B, OUTPUT);
    pinMode(ENA_B, OUTPUT);

    digitalWrite(ENA_B, LOW); // or HIGH depending on your driver
    digitalWrite(PUL_B, LOW);
    digitalWrite(DIR_B, LOW);

    setupTimer(400);

    vTaskDelay(1000);
}

/*********************************************************
 * 
 * Name:  processInfo
 * Notes: See controller.h
 * 
 *********************************************************/
void VertActInterface::processVertActInfo() {

    this->init();

    while(1) {

        moveSteps(6400, true);

        // wait until done
        while (isMoving()) {
            vTaskDelay(1); // 1ms resolution
        }

        moveSteps(6400, false);

        // wait until done
        while (isMoving()) {
            vTaskDelay(1); // 1ms resolution
        }

        printf("VertActInterface Hit!\n");

        vTaskDelay(TASK_DELAY_8HZ);
    }
    
    // EOL for Vert Act task
    vTaskDelete( NULL );
}

bool VertActInterface::isMoving() {
    portENTER_CRITICAL(&timerMux);
    
    bool moving = motorEnabled;
    
    portEXIT_CRITICAL(&timerMux);
    
    return moving;
}

/*********************************************************
 * 
 * Name:  onStepTimer
 * Notes: See controller.h
 * 
 *********************************************************/
void IRAM_ATTR onStepTimer() {
    static bool pulseState = false;

    portENTER_CRITICAL_ISR(&timerMux);

    if (!motorEnabled || stepsRemaining == 0) {
        digitalWrite(PUL_B, LOW);
        portEXIT_CRITICAL_ISR(&timerMux);
        return;
    }

    // Toggle pulse
    pulseState = !pulseState;
    digitalWrite(PUL_B, pulseState);

    // Count steps ONLY on falling edge (1 full pulse)
    if (!pulseState) {
        stepsRemaining--;

        if (stepsRemaining <= 0) {
            motorEnabled = false;
        }
    }

    portEXIT_CRITICAL_ISR(&timerMux);
}

void VertActInterface::setupTimer(uint32_t intervalUs) {
    timer = timerBegin(0, 80, true); // 1 µs tick

    timerAttachInterrupt(timer, &onStepTimer, true);

    timerAlarmWrite(timer, intervalUs, true);
    timerAlarmEnable(timer);
}

void VertActInterface::moveSteps(uint32_t steps, bool dir) {
    portENTER_CRITICAL(&timerMux);

    direction = dir;
    digitalWrite(DIR_B, dir);

    stepsRemaining = steps;
    motorEnabled = true;

    portEXIT_CRITICAL(&timerMux);
}

void VertActInterface::stopMotor() {
    portENTER_CRITICAL(&timerMux);

    motorEnabled = false;
    stepsRemaining = 0;
    
    portEXIT_CRITICAL(&timerMux);
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
    vActInterface->processVertActInfo();
}