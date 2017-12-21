// SYS.h

#ifndef _SYS_h
#define _SYS_h

#ifdef __cplusplus
extern "C" {
#endif

extern void Hardware_Init();
extern void Software_Init();
extern void CPU_Init();
static void Init_FLAG_SYS();
static void Init_RAM_SYS();

#ifdef __cplusplus
} // extern "C"
#endif
#endif

