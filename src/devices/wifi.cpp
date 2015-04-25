#include <otto/devices/wifi.hpp>
#include <string.h>
#include <stdlib.h>

static uint32_t __ottoWifiStatus = 0;
static char* __ottoWifiSsid = 0;

//
STAK_EXPORT void ottoWifiEnable() {
  __ottoWifiStatus = 1;
}

//
STAK_EXPORT void ottoWifiDisable() {
  __ottoWifiStatus = 0;
}

//
STAK_EXPORT uint32_t ottoWifiIsEnabled() {
  return __ottoWifiStatus;
}

//
STAK_EXPORT const char* ottoWifiSsid() {
  if( !__ottoWifiSsid ) {
    return "";
  }
  return __ottoWifiSsid;
}

//
STAK_EXPORT void ottoWifiSetSsid(const char* ssid) {
  if( __ottoWifiSsid ) {
    free( __ottoWifiSsid );
  }
  size_t length = strlen( ssid );
  __ottoWifiSsid = static_cast<char*>( malloc( length + 1 ) );

  // TODO(Wynter): research security concerns regarding memcpy vs strcpy when
  // string length is already known.
  memcpy( __ottoWifiSsid, ssid, length + 1 );
}
