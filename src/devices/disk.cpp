#include <otto/devices/disk.hpp>
#include <cstdio>

static void read_disk( uint64_t *total, uint64_t *used ) {
  char buffer[ 2048 ];

  // call df with a blocksize of 512 bytes and return just the last line of the
  // output so we can easily scan it for disk usage statistics
  FILE *fp = popen( "df -k / | tail -n 1", "r" );
  fgets( buffer, 2048, fp );
  pclose( fp );
  buffer[ 2047 ] = '\0';
  sscanf( buffer, "%*s %llu %llu %*i %*i%%", total, used );
}


// Return used size of user data partition in bytes
STAK_EXPORT uint64_t ottoDiskUsage() {
  uint64_t total = 0, used = 0;
  read_disk( &total, &used );
  return used * 1024ULL;
}

// Return total size of user data partition in bytes
STAK_EXPORT uint64_t ottoDiskSize() {
  uint64_t total = 0, used = 0;
  read_disk( &total, &used );
  return total * 1024ULL;
}
