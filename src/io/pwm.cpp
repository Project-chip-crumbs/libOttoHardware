#include <otto/io/pwm.hpp>
#include <iostream>

//
STAK_EXPORT void ottoPwmEnable( uint32_t pwmChannel ) {
  std::cout << "Enabling Pwm on pwm channel "
            << pwmChannel
            << std::endl;
}

//
STAK_EXPORT void ottoPwmDisable( uint32_t pwmChannel ) {
  std::cout << "Disabling Pwm on pwm channel "
            << pwmChannel
            << std::endl;
}

//
STAK_EXPORT void ottoPwmStart( uint32_t pwmChannel ) {
  std::cout << "Starting Pwm on pwm channel "
            << pwmChannel
            << std::endl;
}

//
STAK_EXPORT void ottoPwmStop( uint32_t pwmChannel ) {
  std::cout << "Stoping Pwm on pwm channel "
            << pwmChannel
            << std::endl;
}

//
STAK_EXPORT void ottoPwmChangeFrequency( uint32_t pwmChannel, uint32_t frequency ) {
  std::cout << "Setting Pwm frequency to "
            << frequency
            << "Hz on pwm channel "
            << pwmChannel
            << std::endl;
}

//
STAK_EXPORT void ottoPwmChangeDutyCycle( uint32_t pwmChannel, float dutyCycle ) {
  std::cout << "Setting Pwm cycle to "
            << dutyCycle
            << " steps on pwm channel "
            << pwmChannel
            << std::endl;
}
