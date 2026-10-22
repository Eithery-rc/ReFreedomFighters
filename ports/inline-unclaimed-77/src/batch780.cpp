// batch780.cpp - unclaimed-77 claim 10 (docs/20-unclaimed-77.md): ZMoveOnSplineIf::FindSplineVal(OpaqueCallParameters_t&) (medium).
// Thiscall, one argument, ret 4. H (0x5003d0) and the virtual slot 0x2fc are stubbed in the harness (GUESS). Both assert paths are
// reproduced: a zero dword at p1 logs "moveonspline_if.cpp:213" (slot 0x20 of [0x700390] returns the log object, its slot 0x2c is
// a cdecl printf) and leaves the result at 0.0; a byte at p4+4 other than 0 or 2 logs line 0x104, then calls the hook [0x7003b0]
// (or traps when it is null).
#include "ff.h"

extern "C" u8 *THISCALL ext_5003d0(void *obj, u32 idx);   // stubbed (GUESS): indexed accessor, one argument, ret 4

typedef void (*log2_t)(void *, const char *);
typedef void (*log3_t)(void *, const char *, const char *);

// 0x5194c0 (medium).
static void THISCALL zMoveOnSplineFindSplineVal(u8 *self, u8 *arg) {
  float r = 0.0f;
  u8 *p1 = ext_5003d0(*(void **)(arg + 4), 0);
  if (*(u32 *)p1 != 0) {
    u8 *p2 = ext_5003d0(*(void **)(arg + 4), 1);
    u8 *p3 = ext_5003d0(*(void **)(arg + 4), 0);
    float v = *(float *)p2;
    void *obj = *(void **)(self + 0x14);
    void **vt = *(void ***)obj;
    r = ((float (THISCALL *)(void *, u32, float))(*(void **)((u8 *)vt + 0x2fc)))(obj, *(u32 *)p3, v);
  } else {
    void *log = vcall<void *>(*(void **)0x700390, 0x20, (const char *)0x69f28c, 0xd5u);
    (*(log2_t *)(*(u8 **)log + 0x2c))(log, (const char *)0x69f2c4);
  }
  u8 *p4 = ext_5003d0(*(void **)(arg + 8), 0);
  u8 t = p4[4];
  if (t != 0 && t != 2) {
    void *log = vcall<void *>(*(void **)0x700390, 0x20, (const char *)0x69c8e0, 0x104u);
    (*(log3_t *)(*(u8 **)log + 0x2c))(log, (const char *)0x69c6b0, (const char *)0x69c938);
    void (*h)() = *(void (**)())0x7003b0;
    if (h)
      h();
    else
      __builtin_debugtrap();
  }
  p4[4] = 2;
  *(float *)p4 = r;
}
PCREG(5194c0, zMoveOnSplineFindSplineVal);
