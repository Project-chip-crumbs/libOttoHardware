#include <otto/io/buttons.hpp>
#include <wiringPi.h>

const int pin_button_power = 24;
const int pin_button_shutter = 23;

STAK_EXPORT void ottoButtonPowerSetCallback( button_callback_t callback ) {
  static button_callback_t button_callback = nullptr;
  button_callback = callback;

  wiringPiISR( pin_button_power, INT_EDGE_BOTH, []( ){
    static volatile int state = -1;
    int level = digitalRead( pin_button_power );
    if ( state == level )
      return;
    state = level;
    button_callback( ( state == 0 ) );
  } );
}

STAK_EXPORT void ottoButtonShutterSetCallback( button_callback_t callback ) {
  static button_callback_t button_callback = nullptr;
  button_callback = callback;

  wiringPiISR( pin_button_shutter, INT_EDGE_BOTH, []( ){
    static volatile int state = -1;
    int level = digitalRead( pin_button_shutter );
    if ( state == level )
      return;
    state = level;
    
    button_callback( ( state == 0) );
  } );
}