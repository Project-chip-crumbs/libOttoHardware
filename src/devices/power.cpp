#include <otto/devices/power.hpp>
#include <string.h>
#include <stdlib.h>

static uint32_t __ottoPowerChargingStatus = 0;
static float __ottoPowerCurrentPercent = 38.925f;
static float __ottoPowerCurrentVoltage = 3.3f;
static float __ottoPowerMaximumVoltage = 4.2f;
static float __ottoPowerAverageVoltage = 3.4f;

static int32_t __ottoPowerGaugeDevice = 0;

STAK_EXPORT void ottoPowerInit() {
	//int32_t device = wiringPiI2CSetup( 0x55 );
	//if (device <= -1) return; // TODO(Wynter): throw some error here please

	//__ottoPowerGaugeDevice = device;
}

//
STAK_EXPORT float ottoPowerCurrentVoltage() {
  return __ottoPowerCurrentVoltage;
}

//
STAK_EXPORT float ottoPowerMaximumVoltage() {
  return __ottoPowerMaximumVoltage;
}

//
STAK_EXPORT float ottoPowerAverageVoltage() {
  return __ottoPowerAverageVoltage;
}


//
STAK_EXPORT uint64_t ottoPowerTimeToDepletion() {
  return 2067ULL;
}

//
STAK_EXPORT uint64_t ottoPowerTimeToFullyCharged() {
  return 9312ULL;
}


STAK_EXPORT float ottoPowerPercent() {
  return __ottoPowerCurrentPercent;
}

STAK_EXPORT uint32_t ottoPowerIsCharging() {
  return __ottoPowerChargingStatus;
}
