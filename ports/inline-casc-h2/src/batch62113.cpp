#include "ff.h"
static u32 THISCALL fn454f20(u8 *self, u32 wanted) {
  u8 *list = G(u8 *, self + 0x5c);
  if (!list) return 0;
  u32 valid__it[4] = {0}; u32 &valid = valid__it[0];  // 12-byte iterator state: the slots 0x4c / 0x5c write up to 3 dwords
  vcall<void>(list, 0x4c, &valid);
  u32 item = vcall<u32>(list, 0x5c, &valid);
  while (valid) {
    if (G(u32, (u8 *)item + 0x34) == wanted) return item;
    item = vcall<u32>(list, 0x5c, &valid);
  }
  return 0;
}
PCREG(454f20, fn454f20);
