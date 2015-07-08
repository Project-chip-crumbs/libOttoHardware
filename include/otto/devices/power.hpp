#ifndef STAK_DEVICES_POWER_HPP
#define STAK_DEVICES_POWER_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

STAK_EXPORT float    ottoPowerAverageVoltage();
STAK_EXPORT float    ottoPowerMaximumVoltage();
STAK_EXPORT uint64_t ottoPowerTimeToDepletion();
STAK_EXPORT uint64_t ottoPowerTimeToFullyCharged();

STAK_EXPORT void     ottoPowerInit();
STAK_EXPORT void     ottoPowerTerminate();
STAK_EXPORT uint32_t ottoPowerIsCharging();
STAK_EXPORT uint32_t ottoPowerIsFull();
STAK_EXPORT float    ottoPowerCharge_Percent();
STAK_EXPORT float    ottoPowerCurrent_mA();
STAK_EXPORT float    ottoPowerVoltage_V();
#endif//STAK_DEVICES_POWER_HPP
