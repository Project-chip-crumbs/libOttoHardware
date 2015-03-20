#ifndef STAK_IO_BUTTONS_HPP
#define STAK_IO_BUTTONS_HPP
#include <stak/stak.hpp>
#include <stak/types.hpp>

// pwm functionality operates on pwm channels rather than gpio pins which
// allows developers to ignore the specifics of pin configuration unless
// they explicitly need to for other reasons

typedef void (*button_callback_t)( int isPressed );

STAK_EXPORT void stakButtonPowerSetCallback( button_callback_t callback );
STAK_EXPORT void stakButtonShutterSetCallback( button_callback_t callback );

#endif//STAK_IO_BUTTONS_HPP
