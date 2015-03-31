#include <iostream>
extern "C" {
  #include <otto/otto.hpp>
  #include <otto/system.hpp>
  #include <otto/devices/disk.hpp>
  #include <otto/io/rotary.hpp>
  #include <otto/io/buttons.hpp>
}
#include <unistd.h>
#include <signal.h>
//#include <bcm2835.h>

int main( int argc, char* argv[] ) {

  char buffer[8192];

  setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
  static int value = 0;
  volatile static int toggle_state = 0, shutter_state = 0, power_state = 0;
  static bool terminate = false;
  
  struct sigaction action;
  action.sa_handler = [](int signum) {
    terminate = true;
  };
  sigaction(SIGINT, &action, NULL);

  ottoHardwareInit();

  ottoRotarySetCallback( []( int delta ){ value += delta; } );

  ottoButtonPowerSetCallback( []( int isPressed ){
    power_state = isPressed;
  });

  ottoButtonShutterSetCallback( []( int isPressed ){
    shutter_state = isPressed;
  });

  ottoRotaryToggleSetCallback( []( int isUp ){
    toggle_state = isUp;
  });

  uint64_t diskUsage = ottoDiskUsage();
  uint64_t diskSize = ottoDiskSize();
  const char* time_string = ottoSystemCallProcess( "date" );

  std::cout << "Usage: " << diskUsage / (1024 * 1024 * 1024) << "GiB" << std::endl
            << "Size: " << diskSize / (1024 * 1024 * 1024) << "GiB" << std::endl;

  while( !terminate ) {
    printf("\rvalue=%4d, toggle state=%s, power state=%s, shutter state=%s, date=%32s",
      value,
      (toggle_state) ? "down" : "up",
      (power_state) ? "up" : "down",
      (shutter_state) ? "up" : "down",
      time_string);
    usleep(300);
  }
  return 0;
}
