#include "ff.h"

// 0x505de0: tail jump to 0x50a410 (a pure forwarder: the stack argument and the `ret N` are the callee's), so a plain jmp with ECX kept
extern "C" __attribute__((naked)) void sub_505de0() {
    asm volatile("jmp ext_50a410");
}
PCREG(505de0, sub_505de0);

// 0x57f350: tail jump to 0x610100 (`ret 4`): a pure forwarder, so a plain jmp (the stack argument is the callee's)
extern "C" __attribute__((naked)) void sub_57f350() {
    asm volatile("jmp ext_610100");
}
PCREG(57f350, sub_57f350);

// 0x5ab090: thiscall, cmp at 0x300, inc at 0x8c7 if not equal (unaligned)
int __thiscall sub_5ab090(int* ecx) {
    if (*(int*)((char*)ecx + 0x300) != 0x10000000) {
        (*(int*)((char*)ecx + 0x8c7))++;
    }
    return 0;
}
PCREG(5ab090, sub_5ab090);
