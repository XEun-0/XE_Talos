#ifndef GLOBALS_H
#define GLOBALS_H

#include "vertActInterface.h"
#include "sensorInterface.h"

// Forward Declaration
class VertActInterface;
class SensorInterface;

#ifdef DECLARE_GLOBALS

extern VertActInterface gVActInterface;
extern SensorInterface gSensorInterface;

#else

VertActInterface gVActInterface;
SensorInterface gSensorInterface;

#endif

#endif // GLOBALS_H