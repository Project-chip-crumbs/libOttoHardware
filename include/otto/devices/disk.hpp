#ifndef STAK_DEVICES_DISK_HPP
#define STAK_DEVICES_DISK_HPP
#include <otto/otto.hpp>
#include <otto/types.hpp>

// Return used size of user data partition in bytes
STAK_EXPORT uint64_t ottoDiskUsage();

// Return total size of user data partition in bytes
STAK_EXPORT uint64_t ottoDiskSize();

#endif//STAK_DEVICES_DISK_HPP
