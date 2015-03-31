#include <otto/io/buttons.hpp>
#include <vector>
#include <future>
#include <iostream>
#include <bcm2835.h>
#include <thread>

const int pin_button_power = 4;
const int pin_button_shutter = 16;

std::thread power_thread, shutter_thread;

STAK_EXPORT void ottoButtonPowerSetCallback( button_callback_t callback ) {
  static button_callback_t button_callback = nullptr;
  static int state = 0;

  if( button_callback == nullptr ) {
    button_callback = callback;
    bcm2835_gpio_fsel( pin_button_power, BCM2835_GPIO_FSEL_INPT );
    bcm2835_gpio_set_pud( pin_button_power, BCM2835_GPIO_PUD_UP );
    state = bcm2835_gpio_lev( pin_button_power );

    // launch interrupt thread
    auto t = std::thread( []{
      while(1) {
        if( bcm2835_gpio_lev( pin_button_power ) != state ) {
          state = bcm2835_gpio_lev( pin_button_power );
          button_callback( bcm2835_gpio_lev( pin_button_power ) );
        }
      }
    } );
    power_thread = std::move(t);
  }
}

STAK_EXPORT void ottoButtonShutterSetCallback( button_callback_t callback ) {
  static button_callback_t button_callback = nullptr;
  static int state = 0;

  if( button_callback == nullptr ) {
    button_callback = callback;
    bcm2835_gpio_fsel( pin_button_shutter, BCM2835_GPIO_FSEL_INPT );
    bcm2835_gpio_set_pud( pin_button_shutter, BCM2835_GPIO_PUD_UP );
    state = bcm2835_gpio_lev( pin_button_shutter );

    // launch interrupt thread
    auto t = std::thread( []{
      while(1) {
        if( bcm2835_gpio_lev( pin_button_shutter ) != state ) {
          state = bcm2835_gpio_lev( pin_button_shutter );
          button_callback( bcm2835_gpio_lev( pin_button_shutter ) );
        }
      }
    } );
    shutter_thread = std::move(t);
  }
}
