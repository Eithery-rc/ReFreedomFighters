// batch235.cpp - small leaves, slice 0/1. 0x503200 (name GUESS): thiscall(a) (ret 4). A = 0x5003d0(a->[4], 0); vA = dword(A);
// B = 0x5003d0(a->[4], 1); if byte(B+4) == 3: edi = dword(B); else (4): edi = dword(B)->vt[0x34](); (other values take an
// error path not modelled here). C..G = 0x5003d0(a->[4], 2..6); L = {dword(C), dword(D), dword(E), dword(F), float(G)} (5 slots).
// r = child->vt[0x114](edi, 0, 0x69ca10, 0x106) (the exe pushes five words, but slot 0x114 pops four: &L stays pending), child =
// [[0x70039c]+0x9b]. O = [this+0xc]: O->vt[0x12c](O, vA, (u16)r, &L) (&L is the third word of slot 0x12c, ret 0xc). Returns void.
#include "ff.h"

extern "C" u8 *THISCALL ext_5003d0(u8 *self, u32 zero);                      // one stack word, ret 4 (stubbed)

typedef u32(THISCALL *SlotNone)(u8 *);             // vtable slot, no stack words, eax result
typedef void(THISCALL *SlotThree)(u8 *, u32, u32, u32);   // vtable 0x12c: three stack words
typedef u32(THISCALL *SlotFour)(u8 *, u32, u32, u32, u32);   // vtable 0x114: four stack words, eax result

static u32 vslot15(u8 *obj, u32 off) { return *(u32 *)(*(u32 *)obj + off); }

static void THISCALL dispatch_503200(u8 *self, u8 *a) {
  u8 *A = ext_5003d0(*(u8 **)(a + 4), 0);
  u32 vA = *(u32 *)A;
  u8 *B = ext_5003d0(*(u8 **)(a + 4), 1);
  u32 edi;
  if (B[4] == 3) {
    edi = *(u32 *)B;
  } else {
    u8 *obj = *(u8 **)B;
    edi = ((SlotNone)vslot15(obj, 0x34))(obj);
  }
  u8 *C = ext_5003d0(*(u8 **)(a + 4), 2);
  u32 L0 = *(u32 *)C;
  u8 *D = ext_5003d0(*(u8 **)(a + 4), 3);
  u32 L1 = *(u32 *)D;
  u8 *E = ext_5003d0(*(u8 **)(a + 4), 4);
  u32 L2 = *(u32 *)E;
  u8 *F = ext_5003d0(*(u8 **)(a + 4), 5);
  u32 L3 = *(u32 *)F;
  u8 *Gp = ext_5003d0(*(u8 **)(a + 4), 6);
  u32 L[5] = {L0, L1, L2, L3, *(u32 *)Gp};
  u8 *child = *(u8 **)(G(u8 *, 0x70039c) + 0x9b);
  u32 r = ((SlotFour)vslot15(child, 0x114))(child, edi, 0, 0x69ca10u, 0x106u);
  u8 *O = *(u8 **)(self + 0xc);
  ((SlotThree)vslot15(O, 0x12c))(O, vA, r & 0xffffu, (u32)L);
}
PCREG(503200, dispatch_503200);
