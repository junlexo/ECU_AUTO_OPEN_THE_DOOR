// WDT.h

#ifndef _WDT_h
#define _WDT_h

#ifdef __cplusplus
extern "C" {
#endif
	extern void WDT_Init();
	extern void WDT_Reset();
	extern void WDT_RegisterFunc(void (*FuncPtr)(void));
#ifdef __cplusplus
} // extern "C"
#endif

#endif

