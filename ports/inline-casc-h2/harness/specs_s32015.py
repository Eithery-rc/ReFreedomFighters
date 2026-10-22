from pilot import S
from recruits_util import rnd, obj, sysobj, clear_hooks, hook_rec

def gen_505de0(c):
    # tail jump to ext_50a410 (thiscall, ONE stack argument, ret 4): the forwarder's caller pushes it, the callee pops it
    hook_rec(c, 0x50a410, 1, ret=c.rng.getrandbits(32), this=True)
    o = obj(c, 0x100, {})
    return [o, c.rng.getrandbits(32)]

def gen_57f350(c):
    # tail jump to 0x610100 (`ret 4`): no hook, the real callee runs, so the stack argument and the callee pop are compared
    clear_hooks(c)
    return [c.rng.getrandbits(32)]

def gen_5ab090(c):
    # thiscall with conditional increment at offsets 0x300 and 0x8c7
    o = obj(c, 0x900, {})  # size >= 0x8c7 + 4
    # Put a random value at offset 0x300, 50% chance of being 0x10000000 to exercise both branches
    if c.rng.getrandbits(1):
        c.emu.w32(o + 0x300, 0x10000000)  # Don't increment this branch
    else:
        c.emu.w32(o + 0x300, c.rng.getrandbits(32) & 0x0fffffff)  # Do increment
    # Put an initial value at 0x8c7 (unaligned)
    c.emu.w32(o + 0x8c7, 0x1000)
    return [o]

S(0x505de0, 'sub_505de0', 'thiscall', None, ret='eax', gen=gen_505de0)
S(0x57f350, 'sub_57f350', 'stdcall', None, ret='eax', gen=gen_57f350)
S(0x5ab090, 'sub_5ab090', 'thiscall', None, ret='eax', gen=gen_5ab090)
