#include <stak/stak.hpp>
#include <wiringPi.h>

STAK_EXPORT void stakHardwareInit() {
  wiringPiSetupSys();
}