#ifndef OTTO_IO_BUZZER_HPP
#define OTTO_IO_BUZZER_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

// buzzer functionality is essentially a wrapper around pwm functionality with
// some naming changed to accomodate the idea that someone working with a piezo
// buzzer will be more focused on generating audio rather than dealing with the
// specifics of how pwm translates to audible output

STAK_EXPORT void ottoBuzzerEnable( uint32_t pwmChannel );
STAK_EXPORT void ottoBuzzerDisable( uint32_t pwmChannel );
STAK_EXPORT void ottoBuzzerStart( uint32_t pwmChannel );
STAK_EXPORT void ottoBuzzerStop( uint32_t pwmChannel );
STAK_EXPORT void ottoBuzzerChangeFrequency( uint32_t pwmChannel, uint32_t frequency );

// halfSteps should be a signed integer of how many steps the note is relative
// to middle c
// TODO(Wynter: Should this be relative to A440?
STAK_EXPORT void ottoBuzzerChangeNote( uint32_t pwmChannel, int32_t halfSteps );
STAK_EXPORT void ottoBuzzerChangeVolume( uint32_t pwmChannel, float volume );

#endif//OTTO_IO_BUZZER_HPP
