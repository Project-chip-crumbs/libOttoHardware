#ifndef STAK_IO_PWM_HPP
#define STAK_IO_PWM_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

// pwm functionality operates on pwm channels rather than gpio pins which
// allows developers to ignore the specifics of pin configuration unless
// they explicitly need to for other reasons

STAK_EXPORT void ottoPwmEnable( uint32_t pwmChannel );
STAK_EXPORT void ottoPwmDisable( uint32_t pwmChannel );
STAK_EXPORT void ottoPwmStart( uint32_t pwmChannel );
STAK_EXPORT void ottoPwmStop( uint32_t pwmChannel );
STAK_EXPORT void ottoPwmChangeFrequency( uint32_t pwmChannel, uint32_t frequency );
STAK_EXPORT void ottoPwmChangeDutyCycle( uint32_t pwmChannel, float dutyCycle );

#endif//STAK_IO_PWM_HPP
