// batch397.cpp - 0x5095f0 (core: ZActorIf::opaqueCall, one stack argument obj, ret 4; ECX = this is passed on unchanged).
// idx = word obj+0x10. If idx < count (global 0x701048): call table[idx] (global table 0x701050) with obj pushed, ECX kept
// (the entries are thiscall-style handlers that read their object from ECX). Otherwise word obj+0x10 = idx - count and the
// call tail-jumps to 0x5060b0 with the argument still in place.
// Naked asm, the exe's instructions copied one for one, so EAX, ECX, EDX and the stack match (a C port loses ECX).
#include "ff.h"

extern "C" void ext_5060b0(void);   // tail target by address (ret 4)
extern "C" void opaqueCall5095f0(void);
__asm__(
    ".text\n"
    ".globl opaqueCall5095f0\n"
    "opaqueCall5095f0:\n"
    "  pushl %ebp\n"
    "  movl %esp, %ebp\n"
    "  movl 8(%ebp), %eax\n"
    "  pushl %esi\n"
    "  movzwl 0x10(%eax), %edx\n"
    "  movl %edx, %esi\n"
    "  cmpl 0x701048, %esi\n"
    "  jae 1f\n"
    "  pushl %eax\n"
    "  movl 0x701050(,%esi,4), %eax\n"
    "  call *%eax\n"
    "  popl %esi\n"
    "  popl %ebp\n"
    "  ret $4\n"
    "1:\n"
    "  subl 0x701048, %edx\n"
    "  movw %dx, 0x10(%eax)\n"
    "  popl %esi\n"
    "  movl %eax, 8(%ebp)\n"
    "  popl %ebp\n"
    "  jmp ext_5060b0\n");
PCREG(5095f0, opaqueCall5095f0);
