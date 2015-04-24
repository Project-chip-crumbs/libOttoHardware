#ifndef STAK_DEVICES_WIFI_HPP
#define STAK_DEVICES_WIFI_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

STAK_EXPORT void ottoWifiEnable();
STAK_EXPORT void ottoWifiDisable();
STAK_EXPORT uint32_t ottoWifiIsEnabled();
STAK_EXPORT const char* ottoWifiSsid();
STAK_EXPORT void ottoWifiSetSsid(const char* ssid);
#endif//STAK_DEVICES_WIFI_HPP
