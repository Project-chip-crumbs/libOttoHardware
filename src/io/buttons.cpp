#include <otto/io/buttons.hpp>
#include <vector>
#include <future>
#include <iostream>
#include <bcm2835.h>
#include <thread>



#include <sys/epoll.h>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>

const int pin_button_power = 4;
const int pin_button_shutter = 16;

std::thread power_thread, shutter_thread;

static void pin_watch(int pin_number, button_callback_t callback){

  int fd, len;
  char str_gpio[3];
  char filename[64];
  
  // open gpio export
  if ((fd = open("/sys/class/gpio/export", O_WRONLY)) < 0) return;

  // export pin 14
  len = snprintf(str_gpio, sizeof(str_gpio), "%d", pin_number );
  write(fd, str_gpio, len);

  // open gpio edge 14 and set to "both"
  sprintf( filename, "/sys/class/gpio/gpio%d/edge", pin_number );
  if ((fd = open(filename, O_WRONLY)) < 0) return;
  write(fd, "both", strlen("both") + 1);
  close(fd);
  // open gpio<pin_number>/value
  sprintf( filename, "/sys/class/gpio/gpio%d/value", pin_number );
  int fd_pin = open( filename, O_RDONLY );

  if( fd_pin == -1 ) return;


  bcm2835_gpio_set_pud( pin_number, BCM2835_GPIO_PUD_UP );

  struct pollfd poll_pin = { .fd = fd_pin, .events = POLLPRI|POLLERR };

  // loop infinitely and poll events
  while( true ) {
    int rv = poll(&poll_pin, 1, -1);

    // if we received a gpio event
    if( rv > 0 ) {
      if( poll_pin.revents & POLLPRI ) {
        // IRQ fired

        char buf[2];
        int n = pread(poll_pin.fd, buf, sizeof(buf), 0);
        if (n > 0)
        {
          char gpio_val = (buf[0] == 48) ? 0 : 1;
          callback( gpio_val );
          //rotary_update( pin_number, gpio_val, rotary_callback );
        }
      }
    }
  }
};

STAK_EXPORT void ottoButtonPowerSetCallback( button_callback_t callback ) {
  static button_callback_t button_callback = nullptr;
  static int state = 0;

  if( button_callback == nullptr ) {

    // launch interrupt thread
    auto t = std::thread( pin_watch, pin_button_power, callback );
    power_thread = std::move(t);
  }
}

STAK_EXPORT void ottoButtonShutterSetCallback( button_callback_t callback ) {
  static button_callback_t button_callback = nullptr;
  static int state = 0;

  if( button_callback == nullptr ) {

    // launch interrupt thread
    auto t = std::thread( pin_watch, pin_button_shutter, callback );
    shutter_thread = std::move(t);
  }
}
