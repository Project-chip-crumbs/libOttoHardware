#include <otto/devices/power.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include <string.h>
#include <stdlib.h>

static bool     __ottoPowerInitialized       = false;
static uint32_t __ottoPowerChargingStatus    = 0;
static float    __ottoPowerCharge_Percent    = 0.0f;
static float    __ottoPowerVoltage_V         = 0.0f;
static float    __ottoPowerCurrent_mA        = 0.0f;

static float    __ottoPowerAverageVoltage    = 3.4f;
static float    __ottoPowerMaximumVoltage    = 4.2f;
static int32_t  __ottoPowerGaugeDevice       = 0;

#define NEW_DEVICE_FILE "/sys/class/i2c-dev/i2c-1/device/new_device"
#define DELETE_DEVICE_FILE "/sys/class/i2c-dev/i2c-1/device/delete_device"
#define VOLTAGE_FILE    "/sys/class/power_supply/bq27500-0/voltage_now"
#define STATUS_FILE     "/sys/class/power_supply/bq27500-0/status"
#define CURRENT_FILE    "/sys/class/power_supply/bq27500-0/current_now"

//PRIVATE
void getValue(const char * FILENAME, std::string &r)
{
  if(!__ottoPowerInitialized) {
    ottoPowerInit();
  }

  try {
    if(__ottoPowerInitialized) {
      std::ifstream ifs;
      ifs.open (FILENAME, std::ifstream::in);
      if(ifs.good()) {
        ifs>>r;
      }
      ifs.close();
    }
  }
  catch(...)
  {
    std::cerr<<"libOttoHardware: could not read from: "<<FILENAME<<"\n";
  }
}

//PRIVATE
void getValue(const char *FILENAME, float &f)
{
  std::string s;
  getValue(FILENAME,s);
  try {
    f=std::stof(s);
  } catch(...) {
    f=-1.0;
  }
}


STAK_EXPORT void ottoPowerInit() {
	__ottoPowerInitialized = true;
  /*if(!__ottoPowerInitialized) {
    std::ofstream ofs;
    ofs.open (NEW_DEVICE_FILE, std::ifstream::out);
    if(ofs.good()) {
      ofs<<"bq27510 0x55\n";
      __ottoPowerInitialized = true;
    }
    ofs.close();
  }*/
}

STAK_EXPORT void ottoPowerTerminate() {
  /*if(__ottoPowerInitialized) {
    std::ofstream ofs;
    ofs.open (DELETE_DEVICE_FILE, std::ifstream::out);
    if(ofs.good()) {
      ofs<< "0x55\n";
      __ottoPowerInitialized = true;
    }
    ofs.close();
  }*/
}

//
STAK_EXPORT float ottoPowerVoltage_V() {
  float f;
  static float last_v = 0.0;
  getValue(VOLTAGE_FILE,f);

  f/=1e6;
  if(f < 0.0) {
    f = last_v;
  } else {
    last_v = f;
  }
  if(f > __ottoPowerMaximumVoltage)
     f = __ottoPowerMaximumVoltage;
  __ottoPowerVoltage_V=f;
  return __ottoPowerVoltage_V;
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

STAK_EXPORT float ottoPowerCharge_Percent() {
  float f;
  static float last_p = 0.0;
  getValue(VOLTAGE_FILE,f);
  f/=1e6;
  f-=3.3;
  f/=0.007;
  if(f<0.0) {
     f = last_p;
  } else {
    last_p = f;
  }
  if(f>100.0)
     f=100.0;

  __ottoPowerCharge_Percent = f;
  return __ottoPowerCharge_Percent;
}

STAK_EXPORT uint32_t ottoPowerIsCharging() {
  std::string s;
  
  getValue(STATUS_FILE,s);
  __ottoPowerChargingStatus = (s=="Charging");

  return __ottoPowerChargingStatus;
}

STAK_EXPORT uint32_t ottoPowerIsFull() {
  std::string s;
  
  getValue(STATUS_FILE,s);
  __ottoPowerChargingStatus = (s=="Full");

  return __ottoPowerChargingStatus;
}

STAK_EXPORT float ottoPowerCurrent_mA()
{
  float f;
  getValue(CURRENT_FILE,f);
  f/=1000; 
  __ottoPowerCurrent_mA=f;
  return __ottoPowerCurrent_mA;
}
