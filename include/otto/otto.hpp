#ifndef STAK_HPP
#define STAK_HPP

#ifdef __cplusplus
	#define STAK_EXPORT extern "C"
#else
	#define STAK_EXPORT
#endif

STAK_EXPORT void ottoHardwareInit();
STAK_EXPORT void ottoHardwareTerminate();

#endif//STAK_HPP
