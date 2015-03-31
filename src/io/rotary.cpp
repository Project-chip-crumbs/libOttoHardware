#include <otto/io/rotary.hpp>
#include <vector>
#include <future>
#include <bcm2835.h>
#include <functional>
#include <iostream>
#include <thread>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>

const int pin_rotary_a = 14;
const int pin_rotary_b = 15;
const int pin_rotary_s = 17;

STAK_EXPORT void rotary_update( int pin, int state, rotary_callback_t callback ) {
  volatile static int state_a = -1, state_b = -1;
  volatile static int last_gpio = -1;
  int status = 0;

  // debounce
  if( ( pin == last_gpio ) || ( callback == nullptr ) )
    return;

  last_gpio = pin;

  if( pin == pin_rotary_a ) {
    state_a = state;
    if( state_b == state_a ) status = 1;
  } else {
    state_b = state;
    if( state_a == state_b ) status = -1;
  }

  if( status != 0 ) {
    callback( status );
  }
}

std::thread rot_a_thread, rot_b_thread, rot_toggle_thread;

STAK_EXPORT void ottoRotarySetCallback( rotary_callback_t callback ) {
  static rotary_callback_t rotary_callback = nullptr;
  static int stateA = 0;
  static int stateB = 0;

  static int fd_pin_a = 0, fd_pin_b = 0;
  if( rotary_callback == nullptr ) {
    rotary_callback = callback;

    int fd, len;
    char str_gpio[3];
    
    // open gpio export
    if ((fd = open("/sys/class/gpio/export", O_WRONLY)) < 0) return;

    // export pin 14
    len = snprintf(str_gpio, sizeof(str_gpio), "14");
    write(fd, str_gpio, len);

    // export pin 15
    len = snprintf(str_gpio, sizeof(str_gpio), "15");
    write(fd, str_gpio, len);
    close(fd);

    // open gpio edge 14 and set to "both"
    if ((fd = open("/sys/class/gpio/gpio14/edge", O_WRONLY)) < 0) return;
    write(fd, "both", strlen("both") + 1);
    close(fd);

    // open gpio edge 15 and set to "both"
    if ((fd = open("/sys/class/gpio/gpio15/edge", O_WRONLY)) < 0) return;
    write(fd, "both", strlen("both") + 1);
    close(fd);


    auto pin_watch = [](int pin_number, int priority){

      // set thread priority
      struct sched_param schedule;
      memset (&schedule, 0, sizeof(schedule)) ;

      if (priority > sched_get_priority_max (SCHED_RR))
        schedule.sched_priority = sched_get_priority_max (SCHED_RR) ;
      else
        schedule.sched_priority = priority;

      sched_setscheduler (0, SCHED_RR, &schedule);

      // open gpio<pin_number>/value
      char filename[64];
      sprintf( filename, "/sys/class/gpio/gpio%d/value", pin_number );
#ifdef THREAD_NONBLOCKING
      int fd_pin = open( filename, O_RDONLY | O_NONBLOCK);
#else
      int fd_pin = open( filename, O_RDONLY );
#endif
      if( fd_pin == -1 ) return;
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
              rotary_update( pin_number, gpio_val, rotary_callback );
            }
          }
        }
      }
    };

    // launch interrupt thread A
    auto t1 = std::thread( pin_watch, 14, 55 );
    rot_a_thread = std::move(t1);

    auto t2 = std::thread( pin_watch, 15, 55 );
    rot_b_thread = std::move(t2);
  }
}

STAK_EXPORT void ottoRotaryToggleSetCallback( rotary_toggle_callback_t callback ) {
  static rotary_toggle_callback_t toggle_callback = nullptr;
  static int state = 0;
  if( toggle_callback == nullptr ) {
    toggle_callback = callback;
    bcm2835_gpio_fsel( pin_rotary_s, BCM2835_GPIO_FSEL_INPT );
    bcm2835_gpio_set_pud( pin_rotary_s, BCM2835_GPIO_PUD_UP );
    state = bcm2835_gpio_lev( pin_rotary_s );
    // launch interrupt thread
    auto t = std::thread( []{
      while( true ) {
        if( bcm2835_gpio_lev( pin_rotary_s ) != state ) {
          state = bcm2835_gpio_lev( pin_rotary_s );
          toggle_callback( bcm2835_gpio_lev( pin_rotary_s ) );
        }
      }
    } );
    rot_toggle_thread = std::move(t);
  }
}
/*

STAK_EXPORT void ottoRotaryToggleSetCallback( rotary_toggle_callback_t callback ) {
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
}*/