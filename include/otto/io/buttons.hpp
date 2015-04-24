#ifndef OTTO_IO_BUTTONS_HPP
#define OTTO_IO_BUTTONS_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

// pwm functionality operates on pwm channels rather than gpio pins which
// allows developers to ignore the specifics of pin configuration unless
// they explicitly need to for other reasons

typedef void (*button_callback_t)( int isPressed );

STAK_EXPORT void ottoButtonPowerSetCallback( button_callback_t callback );
STAK_EXPORT void ottoButtonShutterSetCallback( button_callback_t callback );

#endif//OTTO_IO_BUTTONS_HPP
