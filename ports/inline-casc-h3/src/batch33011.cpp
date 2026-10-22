// batch33011.cpp - cascade h3 tier B: four more simple thunk functions
#include "ff.h"

// four pure forwarders (`push ebp; mov ebp,esp; pop ebp; jmp target`): the stack arguments belong to the target (0x4d7c30 ret 0x10, 0x43ff00 ret 0x14,
// 0x5fa590 ret 8, 0x5355a0 ret 0xc), so the ports are plain jmps; a call with the arguments dropped pops the wrong amount
// 0x4d5760: thunk wrapper
extern "C" __attribute__((naked)) void fn4d5760() { asm volatile("jmp ext_4d7c30"); }
PCREG(4d5760, fn4d5760);

// 0x4f9e00: thunk wrapper
extern "C" __attribute__((naked)) void fn4f9e00() { asm volatile("jmp ext_43ff00"); }
PCREG(4f9e00, fn4f9e00);

// 0x50b7e0: thunk wrapper
extern "C" __attribute__((naked)) void fn50b7e0() { asm volatile("jmp ext_5fa590"); }
PCREG(50b7e0, fn50b7e0);

// 0x533100: thunk wrapper
extern "C" __attribute__((naked)) void fn533100() { asm volatile("jmp ext_5355a0"); }
PCREG(533100, fn533100);
