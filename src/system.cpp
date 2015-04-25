#include <otto/otto.hpp>
#include <otto/types.hpp>
#include <string>
#include <algorithm>
#include <cstring>

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
  ottoSystemCallProcess( "systemctl stop otto-boot" );
  ottoSystemCallProcess( "poweroff" );
  return;
}