"""specs_s33011.py - cascade h3 tier B batch 33011: four more simple thunk wrapper functions."""
from pilot import S
from recruits_util import rnd, obj, clear_hooks, hook_rec


def _me(c, n=0x200):
    return rnd(c, n)


def _g4d5760(c):
    """Thunk wrapper."""
    clear_hooks(c)
    hook_rec(c, 0x7003b0, 0, this=False)
    hook_rec(c, 0x4d7c30, 4, this=True)      # the target pops 4 dwords: the thunk is a pure jmp and passes the caller's stack arguments on
    return [_me(c)] + [c.rng.getrandbits(32) for _ in range(4)]


def _g4f9e00(c):
    """Thunk wrapper."""
    clear_hooks(c)
    hook_rec(c, 0x7003b0, 0, this=False)
    hook_rec(c, 0x43ff00, 5, this=True)      # the target pops 5 dwords: the thunk is a pure jmp and passes the caller's stack arguments on
    return [_me(c)] + [c.rng.getrandbits(32) for _ in range(5)]


def _g50b7e0(c):
    """Thunk wrapper."""
    clear_hooks(c)
    hook_rec(c, 0x7003b0, 0, this=False)
    hook_rec(c, 0x5fa590, 2, this=True)      # the target pops 2 dwords: the thunk is a pure jmp and passes the caller's stack arguments on
    return [_me(c)] + [c.rng.getrandbits(32) for _ in range(2)]


def _g533100(c):
    """Thunk wrapper."""
    clear_hooks(c)
    hook_rec(c, 0x7003b0, 0, this=False)
    hook_rec(c, 0x5355a0, 3, this=True)      # the target pops 3 dwords: the thunk is a pure jmp and passes the caller's stack arguments on
    return [_me(c)] + [c.rng.getrandbits(32) for _ in range(3)]


S(0x4d5760, 'thunk_4d7c30', 'thiscall', None, ret=None, gen=_g4d5760)
S(0x4f9e00, 'thunk_43ff00', 'thiscall', None, ret=None, gen=_g4f9e00)
S(0x50b7e0, 'thunk_5fa590', 'thiscall', None, ret=None, gen=_g50b7e0)
S(0x533100, 'thunk_5355a0', 'thiscall', None, ret=None, gen=_g533100)
