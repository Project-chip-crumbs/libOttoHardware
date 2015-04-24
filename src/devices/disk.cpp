#include <otto/devices/disk.hpp>

volatile unsigned long long __ottoDiskUsage_total = 0;
volatile unsigned long long __ottoDiskUsage_used = 0;
/*static void read_disk( uint64_t *total, uint64_t *used ) {
  char buffer[ 2048 ];

  // call df with a blocksize of 512 bytes and return just the last line of the
  // output so we can easily scan it for disk usage statistics
  FILE *fp = popen( "df -k /dev/mmcblk0p4 | tail -n 1", "r" );
  fgets( buffer, 2048, fp );
  pclose( fp );
  buffer[ 2047 ] = '\0';
  sscanf( buffer, "%*s %llu %llu %*i %*i%%", total, used );
}*/


// Return used size of user data partition in bytes
STAK_EXPORT uint64_t ottoDiskUsage() {
  //uint64_t total = 0, used = 0;
  //read_disk( &total, &used );
  return __ottoDiskUsage_used * 1024ULL;
}

// Return total size of user data partition in bytes
STAK_EXPORT uint64_t ottoDiskSize() {
  //uint64_t total = 0, used = 0;
  //read_disk( &total, &used );
  return __ottoDiskUsage_total * 1024ULL;
}
