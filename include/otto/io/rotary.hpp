#ifndef STAK_IO_ROTARY_HPP
#define STAK_IO_ROTARY_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

// pwm functionality operates on pwm channels rather than gpio pins which
// allows developers to ignore the specifics of pin configuration unless
// they explicitly need to for other reasons

typedef void (*rotary_callback_t)( int delta );
typedef void (*rotary_toggle_callback_t)( int isUp );

STAK_EXPORT void ottoRotarySetCallback( rotary_callback_t callback );
STAK_EXPORT void ottoRotaryToggleSetCallback( rotary_toggle_callback_t callback );

#endif//STAK_IO_ROTARY_HPP
