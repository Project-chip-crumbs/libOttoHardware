#ifndef STAK_DEVICES_POWER_HPP
#define STAK_DEVICES_POWER_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

STAK_EXPORT void ottoPowerInit();
STAK_EXPORT float ottoPowerCurrentVoltage();
STAK_EXPORT float ottoPowerAverageVoltage();
STAK_EXPORT float ottoPowerMaximumVoltage();
STAK_EXPORT uint64_t ottoPowerTimeToDepletion();
STAK_EXPORT uint64_t ottoPowerTimeToFullyCharged();
STAK_EXPORT float ottoPowerPercent();
STAK_EXPORT uint32_t ottoPowerIsCharging();
#endif//STAK_DEVICES_POWER_HPP
