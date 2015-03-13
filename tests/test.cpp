#include <iostream>
#include <stak/devices/disk.hpp>

int main( int argc, char* argv[] ) {
  int diskUsage = stakDiskUsage();
  int diskSize = stakDiskSize();

  std::cout << "Usage: " << diskUsage << std::endl
            << "Size: " << diskSize << std::endl;
  return 0;
}
