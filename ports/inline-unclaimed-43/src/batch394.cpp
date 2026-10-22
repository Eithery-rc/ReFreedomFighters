// batch394.cpp - 0x55ec30 (core: ZFFActorIf::opaqueCall, one stack argument obj, ret 4; ECX = this is passed on unchanged).
// idx = word obj+0x10. If idx < count (global 0x713f10): call table[idx] (global table 0x713f18) with obj pushed, ECX kept
// (the entries are thiscall-style handlers that read their object from ECX). Otherwise word obj+0x10 = idx - count and the
// call tail-jumps to 0x5095f0 (ZActorIf::opaqueCall) with the argument still in place.
// Naked asm, the exe's instructions copied one for one, so EAX, ECX, EDX and the stack match (a C port loses ECX).
#include "ff.h"

extern "C" void ext_5095f0(void);   // tail target by address (ret 4)
extern "C" void opaqueCall55ec30(void);
__asm__(
    ".text\n"
    ".globl opaqueCall55ec30\n"
    "opaqueCall55ec30:\n"
    "  pushl %ebp\n"
    "  movl %esp, %ebp\n"
    "  movl 8(%ebp), %eax\n"
    "  pushl %esi\n"
    "  movzwl 0x10(%eax), %edx\n"
    "  movl %edx, %esi\n"
    "  cmpl 0x713f10, %esi\n"
    "  jae 1f\n"
    "  pushl %eax\n"
    "  movl 0x713f18(,%esi,4), %eax\n"
    "  call *%eax\n"
    "  popl %esi\n"
    "  popl %ebp\n"
    "  ret $4\n"
    "1:\n"
    "  subl 0x713f10, %edx\n"
    "  movw %dx, 0x10(%eax)\n"
    "  popl %esi\n"
    "  movl %eax, 8(%ebp)\n"
    "  popl %ebp\n"
    "  jmp ext_5095f0\n");
PCREG(55ec30, opaqueCall55ec30);
