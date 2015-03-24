#ifndef STAK_DEVICES_POWER_HPP
#define STAK_DEVICES_POWER_HPP
#include <stak/stak.hpp>
#include <stak/types.hpp>

STAK_EXPORT void stakPowerInit();
STAK_EXPORT float stakPowerCurrentVoltage();
STAK_EXPORT float stakPowerAverageVoltage();
STAK_EXPORT float stakPowerMaximumVoltage();
STAK_EXPORT uint64_t stakPowerTimeToDepletion();
STAK_EXPORT uint64_t stakPowerTimeToFullyCharged();
STAK_EXPORT float stakPowerPercent();
STAK_EXPORT uint32_t stakPowerIsCharging();
#endif//STAK_DEVICES_POWER_HPP
