cmake_minimum_required( VERSION 2.8 )
project( libOttoHardware )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
include_directories( include )
include_directories( SYSTEM "/opt/stak/sdk/include" )
file( GLOB_RECURSE src "src/*.cpp" "vendor/bcm2835.c" )

add_library( OttoHardware STATIC ${src} ${deps_src} )
target_include_directories (OttoHardware PUBLIC include)
target_link_libraries( OttoHardware bcm2835 )

install ( TARGETS OttoHardware EXPORT OttoHardware DESTINATION build )