#include <otto/otto.hpp>
#include <bcm2835.h>
#include <thread>
#include <chrono>
#include <cstdio>
#include <string>
#include <iostream>

static std::thread update_thread;
extern volatile unsigned long long __ottoDiskUsage_total;
extern volatile unsigned long long __ottoDiskUsage_used;
volatile bool terminate;

STAK_EXPORT void ottoHardwareInit() {
  bcm2835_init();

  terminate = false;
  auto t = std::thread([] {
    while(!terminate) {
      char buffer[ 2048 ];

      // call df with a blocksize of 512 bytes and return just the last line of the
      // output so we can easily scan it for disk usage statistics
      FILE *fp = popen( "df -k /dev/mmcblk0p4 | tail -n 1", "r" );
      fgets( buffer, 2048, fp );
      pclose( fp );
      buffer[ 2047 ] = '\0';
      sscanf( buffer, "%*s %llu %llu %*i %*i%%", &__ottoDiskUsage_total, &__ottoDiskUsage_used );
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  });
  update_thread = std::move(t);
}

STAK_EXPORT void ottoHardwareTerminate() {
  terminate = true;
  update_thread.join();
  bcm2835_close();
}