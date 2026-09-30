#include "sensorInterface.h"
#include "taskGlobals.h"        // gSensorQueue

SensorInterface::SensorInterface(void) {}

SensorInterface::~SensorInterface(void) {}

//========================================================
//=========== Public Functions ===========================
//========================================================

/*********************************************************
 * 
 * Name:  SensorTaskLauncher
 * Notes: See controller.h
 * 
 *********************************************************/
void SensorInterface::SensorTaskLauncher() {
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
// below is working part of A

 // void SensorInterface::init(void) {
//     /* Initialise the sensor */
//     // if(!bno.begin())
//     // {
//     //     /* There was a problem detecting the BNO055 ... check your connections */
//     //     printf("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//     //     while(1);
//     // }

//     // bno.setExtCrystalUse(true);
//     Wire.begin(SDA_PIN_1, SCL_PIN_1);
//     Wire.begin(SDA_PIN_2, SCL_PIN_2);

//     printf("AS5600 Encoder Test");
//     gSensorQueue = xQueueCreate(10, sizeof(uint8_t));
// }

void SensorInterface::init(void)
{
    // Initialize first I2C bus
    I2C_1.begin(SDA_PIN_1, SCL_PIN_1);

    // Initialize second I2C bus
    I2C_2.begin(SDA_PIN_2, SCL_PIN_2);

    printf("AS5600 Encoder Test\n");

    gSensorQueue = xQueueCreate(10, sizeof(uint8_t));
}

// uint16_t SensorInterface::readRawAngle() {
//     Wire.beginTransmission(AS5600_ADDR);
//     Wire.write(0x0C); // RAW ANGLE register
//     Wire.endTransmission();

//     Wire.requestFrom(AS5600_ADDR, 2);

//     if (Wire.available() == 2) {
//         uint16_t high = Wire.read();
//         uint16_t low = Wire.read();
//         return (high << 8) | low;
//     }

//     return 0;
// }

uint16_t SensorInterface::readRawAngle_1()
{
    I2C_1.beginTransmission(AS5600_ADDR);
    I2C_1.write(0x0C); // RAW ANGLE register
    I2C_1.endTransmission();

    I2C_1.requestFrom(AS5600_ADDR, (uint8_t)2);

    if (I2C_1.available() == 2) {
        uint16_t high = I2C_1.read();
        uint16_t low  = I2C_1.read();
        return (high << 8) | low;
    }

    return 0;
}

uint16_t SensorInterface::readRawAngle_2()
{
    I2C_2.beginTransmission(AS5600_ADDR);
    I2C_2.write(0x0C);
    I2C_2.endTransmission();

    I2C_2.requestFrom(AS5600_ADDR, (uint8_t)2);

    if (I2C_2.available() == 2) {
        uint16_t high = I2C_2.read();
        uint16_t low  = I2C_2.read();
        return (high << 8) | low;
    }

    return 0;
}

/*********************************************************
 * 
 * Name:  processInfo
 * Notes: See controller.h
 * 
 *********************************************************/
void SensorInterface::processInfo() {

    init();

    printf("SensorInteface Started\n");
    while(1) {
        // /* Get a new sensor event */ 
        // sensors_event_t event; 
        // bno.getEvent(&event);
        
        // /* Display the floating point data */
        // printf("X: %.4f, Y: %.4f, Z: %.4f\n", event.orientation.x,event.orientation.y, event.orientation.z); 

        // ===== Encoder runs freely =====
        // uint16_t raw = readRawAngle();
        
        // float angle = (raw * 360.0) / 4096.0;

        // printf("Raw: %d | Angle: %.2f\n", raw, angle);

        uint16_t raw1 = readRawAngle_1();
        uint16_t raw2 = readRawAngle_2();

        float angle1 = (raw1 * 360.0f) / 4096.0f;
        float angle2 = (raw2 * 360.0f) / 4096.0f;

        printf("ENC1: %4u | %6.2f°   | ENC2: %4u | %6.2f°\n",
                raw1, angle1,
                raw2, angle2);

        vTaskDelay(TASK_DELAY_8HZ);
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
void SensorInterface::processInfoStatic(void *pvParams) {
    // Retrieve the singleton instance of the SensorInterface class.
    // This ensures that only one instance of SensorInterface exists 
    // and is used throughout the program.

    SensorInterface *sensorInterface = static_cast<SensorInterface *>(pvParams);
    sensorInterface->processInfo();
}