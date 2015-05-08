cmake_minimum_required( VERSION 2.8 )
project( libOttoHardware )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
include_directories( include )
include_directories( vendor )
include_directories( SYSTEM "/opt/stak/sdk/include" )
file( GLOB_RECURSE src "src/*.cpp" "vendor/bcm2835.c" )

add_library( OttoHardware SHARED ${src} ${deps_src} )
target_link_libraries( OttoHardware bcm2835 )

add_executable( otto-poweroff tools/otto-poweroff.cpp )
target_link_libraries( otto-poweroff OttoHardware bcm2835 )

# FILE(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
install ( DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/otto" DESTINATION ${CMAKE_INSTALL_PREFIX}/include )
install ( TARGETS OttoHardware EXPORT OttoHardware DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )
install ( TARGETS otto-poweroff EXPORT otto-poweroff DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )

