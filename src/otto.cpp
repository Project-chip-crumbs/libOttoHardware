#include <otto/otto.hpp>
#include <wiringPi.h>

STAK_EXPORT void ottoHardwareInit() {
  wiringPiSetupGpio();
}