#include "ff.h"

// 0x5331c0: add ecx 0x8b, jmp 0x534090
// (a pure forwarder with an adjusted this: the stack argument belongs to 0x534090, so jmp, do not call)
extern "C" __attribute__((naked)) void sub_5331c0() {
    asm volatile("add $0x8b, %ecx\n\tjmp ext_534090");
}
PCREG(5331c0, sub_5331c0);

// 0x63fc10: add ecx 0x8270, jmp 0x65f200
extern "C" __attribute__((naked)) void sub_63fc10() {
    asm volatile("add $0x8270, %ecx\n\tjmp ext_65f200");
}
PCREG(63fc10, sub_63fc10);
