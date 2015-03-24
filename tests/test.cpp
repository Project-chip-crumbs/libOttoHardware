#include <iostream>
#include <stak/stak.hpp>
#include <stak/system.hpp>
#include <stak/devices/disk.hpp>
#include <stak/io/rotary.hpp>
#include <stak/io/buttons.hpp>
#include <unistd.h>

int main( int argc, char* argv[] ) {
  static int value = 0;
  static int toggle_state = 0;

  stakHardwareInit();
  stakRotarySetCallback( []( int delta ){ value += delta; } );

  /*stakButtonPowerSetCallback( []( int isPressed ){
    std::cout << "Power " << ( isPressed ? "pressed!" : "released!" ) << std::endl;
  });

  stakButtonShutterSetCallback( []( int isPressed ){
    std::cout << "Shutter " << ( isPressed ? "pressed!" : "released!" ) << std::endl;
  });*/

  stakRotaryToggleSetCallback( []( int isUp ){
    toggle_state = isUp;
  });

  uint64_t diskUsage = stakDiskUsage();
  uint64_t diskSize = stakDiskSize();
  const char* time_string = stakSystemCallProcess( "date" );

  std::cout << "Usage: " << diskUsage / (1024 * 1024 * 1024) << "GiB" << std::endl
            << "Size: " << diskSize / (1024 * 1024 * 1024) << "GiB" << std::endl;

  while( true ) {
    printf("\rvalue=%4d, toggle_state=%7s, date=%32s", value, toggle_state ? "up!" : "down!", time_string);
    usleep(300);
  }
  return 0;
}
