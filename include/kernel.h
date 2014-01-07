#ifndef _KERNEL_H
#define _KERNEL_H

#define FASTCALL __attribute__((fastcall)) 
#define STDCALL __attribute__((stdcall)) 

#define SIZEOFARRAY(x) (sizeof(x) / sizeof(*(x)))

#endif
