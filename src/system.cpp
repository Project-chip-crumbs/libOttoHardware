#include <otto/otto.hpp>
#include <otto/types.hpp>
#include <string>
#include <algorithm>
#include <cstring>
#include <bcm2835.h>
#include <unistd.h>

// TODO(Wynter): Support some sort of timeout here
STAK_EXPORT const char* ottoSystemCallProcess( const char* processCall ) {
  std::string returnData;
  char buffer[ 2048 ];

  // call df with a blocksize of 512 bytes and return just the last line of the
  // output so we can easily scan it for disk usage statistics
  FILE *fp = popen( processCall, "r" );
  int dataRead = -1;
  while( dataRead != 0 ) {
    dataRead = fread( buffer, sizeof(char), 2047, fp );
    buffer[ dataRead ] = '\0';
    returnData += buffer;
  }
  pclose( fp );

  returnData.erase(std::remove_if(returnData.begin(), 
                              returnData.end(),
                              [](char x){ return (x == '\n'); }),
               returnData.end());

  char* returnBuffer = new char[ returnData.size() ];
  strcpy( returnBuffer, returnData.c_str() );
  return returnBuffer;
}


STAK_EXPORT void ottoSystemShutdown( ) {
  ottoSystemCallProcess( "systemctl poweroff" );
  return;
}

STAK_EXPORT void ottoPowerOff( ) {
  int pin=4; 
 
  if( !bcm2835_init() ) {
      fprintf(stderr,"bcm2835_init() failed\n");
      return;
  }

  bcm2835_gpio_fsel( pin, BCM2835_GPIO_FSEL_INPT );

  //bcm2835_gpio_set_pud( pin, BCM2835_GPIO_PUD_UP );
  //bcm2835_gpio_set_pud( pin, BCM2835_GPIO_PUD_OFF );
  bcm2835_gpio_set_pud( pin, BCM2835_GPIO_PUD_DOWN );

  uint8_t value = bcm2835_gpio_lev(pin);
  printf("read from pin %d: %d\n", pin, value);
  sleep(1);
  value = bcm2835_gpio_lev(pin);
  printf("read from pin %d: %d\n", pin, value);
  sleep(1);
  value = bcm2835_gpio_lev(pin);
  printf("read from pin %d: %d\n", pin, value);
  sleep(1);
  value = bcm2835_gpio_lev(pin);
  printf("read from pin %d: %d\n", pin, value);
  sleep(1);

  bcm2835_close();

  return;
}
