#include <stak/devices/power.hpp>
#include <string.h>
#include <stdlib.h>

static uint32_t __stakPowerChargingStatus = 0;
static float __stakPowerCurrentPercent = 38.925f;
static float __stakPowerCurrentVoltage = 3.3f;
static float __stakPowerMaximumVoltage = 4.2f;
static float __stakPowerAverageVoltage = 3.4f;

static int32_t __stakPowerGaugeDevice = 0;

STAK_EXPORT void stakPowerInit() {
	//int32_t device = wiringPiI2CSetup( 0x55 );
	//if (device <= -1) return; // TODO(Wynter): throw some error here please

	//__stakPowerGaugeDevice = device;
}

//
STAK_EXPORT float stakPowerCurrentVoltage() {
  return __stakPowerCurrentVoltage;
}

//
STAK_EXPORT float stakPowerMaximumVoltage() {
  return __stakPowerMaximumVoltage;
}

//
STAK_EXPORT float stakPowerAverageVoltage() {
  return __stakPowerAverageVoltage;
}


//
STAK_EXPORT uint64_t stakPowerTimeToDepletion() {
  return 2067ULL;
}

//
STAK_EXPORT uint64_t stakPowerTimeToFullyCharged() {
  return 9312ULL;
}


STAK_EXPORT float stakPowerPercent() {
  return __stakPowerCurrentPercent;
}

STAK_EXPORT uint32_t stakPowerIsCharging() {
  return __stakPowerChargingStatus;
}
