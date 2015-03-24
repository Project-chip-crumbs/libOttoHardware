#include <iostream>
#include <otto/otto.hpp>
#include <otto/system.hpp>
#include <otto/devices/disk.hpp>
#include <otto/io/rotary.hpp>
#include <otto/io/buttons.hpp>
#include <unistd.h>

int main( int argc, char* argv[] ) {
  static int value = 0;
  static int toggle_state = 0;

  ottoHardwareInit();
  ottoRotarySetCallback( []( int delta ){ value += delta; } );

  /*ottoButtonPowerSetCallback( []( int isPressed ){
    std::cout << "Power " << ( isPressed ? "pressed!" : "released!" ) << std::endl;
  });

  ottoButtonShutterSetCallback( []( int isPressed ){
    std::cout << "Shutter " << ( isPressed ? "pressed!" : "released!" ) << std::endl;
  });*/

  ottoRotaryToggleSetCallback( []( int isUp ){
    toggle_state = isUp;
  });

  uint64_t diskUsage = ottoDiskUsage();
  uint64_t diskSize = ottoDiskSize();
  const char* time_string = ottoSystemCallProcess( "date" );

  std::cout << "Usage: " << diskUsage / (1024 * 1024 * 1024) << "GiB" << std::endl
            << "Size: " << diskSize / (1024 * 1024 * 1024) << "GiB" << std::endl;

  while( true ) {
    printf("\rvalue=%4d, toggle_state=%7s, date=%32s", value, toggle_state ? "up!" : "down!", time_string);
    usleep(300);
  }
  return 0;
}
