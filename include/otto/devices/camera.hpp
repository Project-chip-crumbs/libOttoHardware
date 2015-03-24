#ifndef STAK_DEVICES_CAMERA_HPP
#define STAK_DEVICES_CAMERA_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

// TODO: Camera api needs a bit of research and thought this should be able to
// provide full functionality needed to at least generate a basic frame of
// various resolutions. Any further functionality added should consider the
// common capabilities available to many cameras, so any special effects
// features should be left out here or have some way to query for availability.
// We want to avoid the issue that, e.g. GL extensions create however.

#if 0 // disabled until more research is done.
STAK_EXPORT void ottoCameraEnable( uint32_t cameraNumber );
STAK_EXPORT void ottoCameraDisable( uint32_t cameraNumber );
STAK_EXPORT void ottoCameraStart( uint32_t cameraNumber );
STAK_EXPORT void ottoCameraStop( uint32_t cameraNumber );
#endif

#endif//STAK_DEVICES_CAMERA_HPP
