#ifndef GLOBALS_H
#define GLOBALS_H

#include "vertActInterface.h"
#include "imuInterface.h"

// Forward Declaration
class VertActInterface;
class IMUInterface;

#ifdef DECLARE_GLOBALS

extern VertActInterface gVActInterface;
extern IMUInterface gIMUInterface;

#else

VertActInterface gVActInterface;
IMUInterface gIMUInterface;

#endif

#endif // GLOBALS_H