"""specs_s4104.py - unclaimed-41 batch 4 (slice 13, leaves): four small functions. Each is a thiscall with no stack arguments.

0x4d8c10 (getter): returns this+0x84 (eax compared). 0x5f0490 (store vtable): writes 0x6b8284 at +0 (heap compared).
0x5ab110 (conditional counter): +0x300 is 0x10000000 in half the cases; the counter at +0x8b7 is incremented otherwise.
0x438c10 (tail-jump forwarder): jumps to vtable slot +0x10 of this, the stack argument is the slot's, and returns its eax; the slot is a checksum stub
with one stack argument (the forwarder has none of its own: the callee's are the caller's, ret 4 in the exe).
Faulting cases must be 0 (JSON)."""
from pilot import S
import helper_stubs as hs


def _rnd(c, n, align=4):
    a = c.emu.alloc(n, align)
    c.emu.wbytes(a, bytes(c.rng.getrandbits(8) for _ in range(n)))
    return a


def _getter(c):
    return [_rnd(c, 0x100)]


def _store(c):
    return [_rnd(c, 0x40)]


def _cond(c):
    o = _rnd(c, 0x900)
    if c.rng.random() < 0.5:
        c.emu.w32(o + 0x300, 0x10000000)
    else:
        c.emu.w32(o + 0x300, c.rng.getrandbits(32))
    return [o]


def _fwd(c):
    vt = c.emu.alloc(0x40, 4)
    s, _, _ = hs.stub(c, 1, ecx=True, edx=False, ret=c.rng.getrandbits(32))     # the slot takes one stack argument (ret 4): the caller's
    c.emu.w32(vt + 0x10, s)
    o = _rnd(c, 0x100)
    c.emu.w32(o, vt)
    return [o, c.rng.getrandbits(32)]


S(0x4d8c10, 'getAddr84 (unknown) thiscall', 'thiscall', None, ret='eax', gen=_getter,
  note='unclaimed-41 batch 4; getter this+0x84')
S(0x5f0490, 'storeVtable (unknown) thiscall', 'thiscall', None, ret=None, gen=_store,
  note='unclaimed-41 batch 4; writes 0x6b8284 at +0')
S(0x5ab110, 'condIncCounter (unknown) thiscall', 'thiscall', None, ret=None, gen=_cond,
  note='unclaimed-41 batch 4; counter at +0x8b7 when +0x300 != 0x10000000')
S(0x438c10, 'forwardVt10 (unknown) thiscall', 'thiscall', None, ret='eax', gen=_fwd,
  note='unclaimed-41 batch 4; tail-jump to vtable slot +0x10 (checksum stub, no arguments; GUESS)')
