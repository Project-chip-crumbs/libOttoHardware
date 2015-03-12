#include <iostream>
#include <string>
#include <regex>
#include <cstdio>

int read_disk() {
  char buffer[2048];
  FILE *fp = popen("df / | tail -n 1", "r");
  fread(buffer, 1, 2048, fp);
  buffer[2047]='\0';

  std::string out_string(buffer);
  std::cout << out_string << std::endl;

  std::smatch matches;

  if( std::regex_match( buffer, std::regex("(.*)") ) ) {
    std::cout << "Matches: " << matches.size() << std::endl;  
  } else {
    std::cout << "No matches found!" << std::endl;

  }
  
  //your code
  pclose(fp);
  return 0;
}

int main( int argc, char* argv[] ) {
	read_disk();
	return 0;
}
