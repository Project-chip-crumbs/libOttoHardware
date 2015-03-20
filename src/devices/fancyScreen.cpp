#include <stak/devices/fancyScreen.hpp>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>


enum DISPLAY_COMMANDS {
  SEPS114A_SOFT_RESET = 0x01,
  SEPS114A_DISPLAY_ON_OFF = 0x02,
  SEPS114A_ANALOG_CONTROL = 0x0F,
  SEPS114A_STANDBY_ON_OFF = 0x14,
  SEPS114A_OSC_ADJUST = 0x1A,
  SEPS114A_ROW_SCAN_DIRECTION = 0x09,
  SEPS114A_DISPLAY_X1 = 0x30,
  SEPS114A_DISPLAY_X2 = 0x31,
  SEPS114A_DISPLAY_Y1 = 0x32,
  SEPS114A_DISPLAY_Y2 = 0x33,
  SEPS114A_DISPLAYSTART_X = 0x38,
  SEPS114A_DISPLAYSTART_Y = 0x39,
  SEPS114A_CPU_IF = 0x0D,
  SEPS114A_MEM_X1 = 0x34,
  SEPS114A_MEM_X2 = 0x35,
  SEPS114A_MEM_Y1 = 0x36,
  SEPS114A_MEM_Y2 = 0x37,
  SEPS114A_MEMORY_WRITE_READ = 0x1D,
  SEPS114A_DDRAM_DATA_ACCESS_PORT = 0x08,
  SEPS114A_DISCHARGE_TIME = 0x18,
  SEPS114A_PEAK_PULSE_DELAY = 0x16,
  SEPS114A_PEAK_PULSE_WIDTH_R = 0x3A,
  SEPS114A_PEAK_PULSE_WIDTH_G = 0x3B,
  SEPS114A_PEAK_PULSE_WIDTH_B = 0x3C,
  SEPS114A_PRECHARGE_CURRENT_R = 0x3D,
  SEPS114A_PRECHARGE_CURRENT_G = 0x3E,
  SEPS114A_PRECHARGE_CURRENT_B = 0x3F,
  SEPS114A_COLUMN_CURRENT_R = 0x40,
  SEPS114A_COLUMN_CURRENT_G = 0x41,
  SEPS114A_COLUMN_CURRENT_B = 0x42,
  SEPS114A_ROW_OVERLAP = 0x48,
  SEPS114A_SCAN_OFF_LEVEL = 0x49,
  SEPS114A_ROW_SCAN_ON_OFF = 0x17,
  SEPS114A_ROW_SCAN_MODE = 0x13,
  SEPS114A_SCREEN_SAVER_CONTEROL = 0xD0,
  SEPS114A_SS_SLEEP_TIMER = 0xD1,
  SEPS114A_SCREEN_SAVER_MODE = 0xD2,
  SEPS114A_SS_UPDATE_TIMER = 0xD3,
  SEPS114A_RGB_IF = 0xE0,
  SEPS114A_RGB_POL = 0xE1,
  SEPS114A_DISPLAY_MODE_CONTROL = 0xE5
};


static const int fancy_screen_pin_reset = 30;
static const int fancy_screen_pin_dc = 31;
static const int fancy_screen_pin_cs = 7;

static uint16_t fancy_screen_framebuffer[2][96*96];



static int fs_write_command(uint8_t* command_ptr) {
  //Select index addr
  digitalWrite( fancy_screen_pin_dc, LOW );
  wiringPiSPIDataRW(0, command_ptr, sizeof(uint8_t));
  return 0;
}
static int fs_write_command_value(uint8_t* command_ptr) {
  //Select index addr
  digitalWrite( fancy_screen_pin_dc, LOW );
  wiringPiSPIDataRW(0, command_ptr, sizeof(uint8_t));
  digitalWrite( fancy_screen_pin_dc, HIGH );
  wiringPiSPIDataRW(0, command_ptr + sizeof(uint8_t), sizeof(uint8_t));
  digitalWrite( fancy_screen_pin_dc, LOW );
  return 0;
}

STAK_EXPORT void stakFancyScreenInit() {
  static uint8_t screen_init_sequence[] = {
    SEPS114A_SOFT_RESET, 0x00,
    SEPS114A_STANDBY_ON_OFF, 0x01,
    // Wait for 5ms (1ms Delay Minimum)
    SEPS114A_STANDBY_ON_OFF, 0x00,
    // 1ms Delay Minimum (1ms Delay Minimum)
    
    SEPS114A_DISPLAY_ON_OFF, 0x00,
    SEPS114A_ANALOG_CONTROL, 0x00,
    SEPS114A_OSC_ADJUST, 0x0a,
    SEPS114A_DISPLAY_X1, 0x00,
    SEPS114A_DISPLAY_X2, 0x5F,
    SEPS114A_DISPLAY_Y1, 0x00,
    SEPS114A_DISPLAY_Y2, 0x5F,
    SEPS114A_RGB_IF, 0x00,
    SEPS114A_RGB_POL, 0x00,
    SEPS114A_DISPLAY_MODE_CONTROL, 0x80,
    SEPS114A_CPU_IF, 0x00,
    SEPS114A_MEMORY_WRITE_READ, 0x01,
    SEPS114A_ROW_SCAN_DIRECTION, 0x00,
    SEPS114A_ROW_SCAN_MODE, 0x00,          // Alternate scan mode
    SEPS114A_COLUMN_CURRENT_R, 0x6E,
    SEPS114A_COLUMN_CURRENT_G, 0x4F,
    SEPS114A_COLUMN_CURRENT_B, 0x77,
    SEPS114A_ROW_OVERLAP, 0x00,
    SEPS114A_DISCHARGE_TIME, 0x01,
    SEPS114A_PEAK_PULSE_DELAY, 0x05,
    SEPS114A_PEAK_PULSE_WIDTH_R, 0x02,
    SEPS114A_PEAK_PULSE_WIDTH_G, 0x02,
    SEPS114A_PEAK_PULSE_WIDTH_B, 0x02,
    SEPS114A_PRECHARGE_CURRENT_R, 0x14,
    SEPS114A_PRECHARGE_CURRENT_G, 0x50,
    SEPS114A_PRECHARGE_CURRENT_B, 0x19,
    SEPS114A_ROW_SCAN_ON_OFF, 0x00,
    SEPS114A_SCAN_OFF_LEVEL, 0x04,
    SEPS114A_DISPLAYSTART_X, 0x00,
    SEPS114A_DISPLAYSTART_Y, 0x00,
    SEPS114A_DISPLAY_ON_OFF, 0x01,
    SEPS114A_MEMORY_WRITE_READ, 0x00
  };
  int offset = ( 6 * sizeof(uint8_t) );

  // open spidev0.0 @ 4Mhz
  wiringPiSPISetup( 0, 4000000 );
  pinMode( fancy_screen_pin_reset, OUTPUT );
  pinMode( fancy_screen_pin_dc, OUTPUT );
  pinMode( fancy_screen_pin_cs, OUTPUT );

  digitalWrite( fancy_screen_pin_reset, LOW );
  usleep(5000);
  digitalWrite( fancy_screen_pin_reset, HIGH );
  usleep(5000);

  //wiringPiSPIDataRW( 0, screen_init_sequence, 4 );
  fs_write_command_value( screen_init_sequence );
  fs_write_command_value( screen_init_sequence + 2 );
  usleep(5000);
  //wiringPiSPIDataRW( 0, screen_init_sequence, 2 );
  fs_write_command_value( screen_init_sequence + 4 );
  usleep(5000);
  for( int index = 6; index < sizeof(screen_init_sequence); index += 2 ) {
    fs_write_command_value( screen_init_sequence + index );
  }
  //wiringPiSPIDataRW( 0, screen_init_sequence, sizeof(screen_init_sequence) - ( 6 * sizeof(uint8_t) ) );

  //fancy_screen_framebuffer[0] = new uint16_t[96*96];
  //fancy_screen_framebuffer[1] = new uint16_t[96*96];
  memset(fancy_screen_framebuffer[0], 0x33, 96*96*2);
}
inline uint16_t swap_rgb (uint16_t rgb)
{
    return  (((rgb << 8) & 0xff00) |
             ((rgb >> 8) & 0x00ff));
}


inline uint32_t swap_rgb32 (uint32_t rgb)
{
    return  (((rgb << 8) & 0xff00ff00) |
             ((rgb >> 8) & 0x00ff00ff));
}

void stakFancyScreenUpdate( ) {
  //
  // Swap framebuffer data in 32 bit blocks
  uint32_t *vmem32 = (uint32_t*)fancy_screen_framebuffer, *vmem32_end = vmem32 + 4608;
  while( vmem32 < vmem32_end) {
      *vmem32 = swap_rgb32( *vmem32 );
      vmem32++;
  }

  //
  //
  static uint8_t screen_update_sequence[] = {
    SEPS114A_MEMORY_WRITE_READ, 0x01,
    SEPS114A_MEM_X1, 0x00,
    SEPS114A_MEM_X2, 0x5F,
    SEPS114A_MEM_Y1, 0x00,
    SEPS114A_MEM_Y2, 0x5F,
    SEPS114A_DISPLAYSTART_X, 0x00,
    SEPS114A_DISPLAYSTART_Y, 0x00,
    SEPS114A_DDRAM_DATA_ACCESS_PORT
  };
  for( int index = 0; index < sizeof(screen_update_sequence) - sizeof(uint8_t); index += 2 ) {
    fs_write_command_value( screen_update_sequence + index );
  }
  fs_write_command( screen_update_sequence + 15 );

  //wiringPiSPIDataRW(0, screen_update_sequence, sizeof( screen_update_sequence ) );

  //
  //
  digitalWrite( fancy_screen_pin_dc, HIGH );

  uint8_t* data = (uint8_t*)fancy_screen_framebuffer;
  int length = 96*96*2;
  int split = 0;
  int offset = 0;
  if(length > 2048) {
    int remainder = (length % 2048);
    int chunks = (length - remainder) / 2048;
    for(;split < chunks; split++) {
      offset = (split * 2048);
      int size = (length - (split * 2048)) % 2048;
      if(size == 0) size = 2048;
      if( wiringPiSPIDataRW( 0, data + offset, size ) < 0) {
        perror("SPI_IOC_MESSAGE");
      }
    }
  }
  else {
    if( wiringPiSPIDataRW( 0, data, length) < 0) {
      perror("SPI_IOC_MESSAGE");
    }
  }
  digitalWrite( fancy_screen_pin_dc, LOW );
}

/*
int stak_seps114a_update(stak_seps114a_s* device) {
    stak_seps114a_write_command_value(device, SEPS114A_MEMORY_WRITE_READ,0x01);
    stak_seps114a_write_command_value(device, SEPS114A_MEM_X1,0x00);
    stak_seps114a_write_command_value(device, SEPS114A_MEM_X2,0x5F);
    stak_seps114a_write_command_value(device, SEPS114A_MEM_Y1,0x00);
    stak_seps114a_write_command_value(device, SEPS114A_MEM_Y2,0x5F);
    stak_seps114a_write_command_value(device, SEPS114A_DISPLAYSTART_X,0x00);
    stak_seps114a_write_command_value(device, SEPS114A_DISPLAYSTART_Y,0x00);
    stak_seps114a_write_command(device, SEPS114A_DDRAM_DATA_ACCESS_PORT);

#if 1
    uint32_t *vmem32 = (uint32_t*)device->framebuffer, *vmem32_end = vmem32 + 4608;
    while( vmem32 < vmem32_end) {
        *vmem32 = swap_rgb32( *vmem32 );
        vmem32++;
    }
#else
    uint16_t *vmem16 = (uint16_t *)device->framebuffer;
    int x, y;
    for (y = 0; y < 96; y++) {
        for (x = 0; x < 96; x++) {
            vmem16[y*96+x] = swap_rgb(vmem16[y*96+x]);
        }
    }
#endif
    GPIO_ON(STAK_SEPS114A_PIN_DC);

    stak_seps114a_write_data(device, (uint8_t*)device->framebuffer, 96*96*2);
    return 0;
}*/