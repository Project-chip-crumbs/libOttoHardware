#include <stak/io/rotary.hpp>
#include <wiringPi.h>

const int pin_rotary_a = 23;
const int pin_rotary_b = 24;
const int pin_rotary_s = 25;

STAK_EXPORT void rotary_update( int pin, int state, rotary_callback_t callback ) {
  static int state_a = -1, state_b = -1;
  static int last_gpio = -1;

  // debounce
  if( ( pin == last_gpio ) || ( !callback ) )
    return;

  last_gpio = pin;

  if( pin == pin_rotary_a ) {
    state_a = state;
    if( state_b == state_a ) callback(1);
  } else {
    state_b = state;
    if( state_a == state_b ) callback(-1);
  }
}

STAK_EXPORT void stakRotarySetCallback( rotary_callback_t callback ) {
  static rotary_callback_t rotary_callback = nullptr;
  rotary_callback = callback;

  // start ISR for pin A to call rotary_update with callback info
  wiringPiISR( pin_rotary_a, INT_EDGE_BOTH, []( ){
    rotary_update( pin_rotary_a, digitalRead( pin_rotary_a ), rotary_callback );
  } );

  // start ISR for pin B to call rotary_update with callback info
  wiringPiISR( pin_rotary_b, INT_EDGE_BOTH, []( ){
    rotary_update( pin_rotary_b, digitalRead( pin_rotary_b ), rotary_callback );
  } );
}

STAK_EXPORT void stakRotaryToggleSetCallback( rotary_toggle_callback_t callback ) {
  static rotary_toggle_callback_t toggle_callback = nullptr;
  toggle_callback = callback;

  wiringPiISR( pin_rotary_s, INT_EDGE_BOTH, []( ){
    static volatile int state = -1;
    int level = digitalRead( pin_rotary_s );
    if ( state == level )
      return;
    state = level;
    
    toggle_callback( ( state == 0) );
  } );
}