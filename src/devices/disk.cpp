#include <stak/devices/disk.hpp>
#include <cstdio>

static void read_disk(uint64_t *total, uint64_t *used) {
  char buffer[2048];
  FILE *fp = popen("df / | tail -n 1", "r");
  fgets(buffer, 2048, fp);
  pclose(fp);
  buffer[2047]='\0';

  sscanf(buffer, "%*s %llu %llu %*i %*i%%", total, used );
}


// Return used size of user data partition in bytes
STAK_EXPORT uint64_t stakDiskUsage() {
  uint64_t total = 0, used = 0;
  read_disk( &total, &used );
  return used * 512ULL;
}

// Return total size of user data partition in bytes
STAK_EXPORT uint64_t stakDiskSize() {
  uint64_t total = 0, used = 0;
  read_disk( &total, &used );
  return total * 512ULL;
}
