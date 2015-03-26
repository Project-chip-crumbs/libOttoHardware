cmake_minimum_required( VERSION 2.8 )
project( libOttoHardware )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories( include )
include_directories( SYSTEM deps/wiringPi/wiringPi )

file( GLOB_RECURSE src "src/*.cpp" )
file( GLOB deps_src "deps/wiringPi/wiringPi/*.c" )

add_library( OttoHardware ${src} ${deps_src} )
