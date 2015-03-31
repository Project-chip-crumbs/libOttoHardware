#include <otto/otto.hpp>
#include <bcm2835.h>

STAK_EXPORT void ottoHardwareInit() {
  bcm2835_init();
}

STAK_EXPORT void ottoHardwareTerminate() {
  bcm2835_close();
}