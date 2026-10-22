"""specs_s67558.py - cascade s6 batch 67558 (0x467260, thiscall(a, b, c) ret 0xc, returns eax). sys[0x1a9f] (object with slot 0x70, bool) is zero sometimes; this[0x153] holds an old handle (or 0);
the object table slot 0x60 maps handles to records (random blocks, or 0); this slots 0x3a0 (writes the matrix / vector into stack locals, result random), 0x390, 0x20 (returns the creator) are stubs;
0x44b610 / 0x44b740 / 0x43ec00 are hooks (43ec00 logs the matrix and vector contents, returns a handle)."""
from pilot import S
from recruits_util import rnd, obj, sysobj, clear_hooks, hook_rec, pystub


def _w(c, a, v, n=4):
    c.emu.wbytes(a, (v & ((1 << (8 * n)) - 1)).to_bytes(n, 'little'))


def _g467260(c):
    clear_hooks(c)
    r = c.rng
    e = c.emu
    recs = [rnd(c, 0xa0) for _ in range(3)]
    so = sysobj(c, table_slots={0x60: pystub(c, 1, this=True, ret=lambda em, k: r.choice(recs + [0]))})
    s1a9f = obj(c, 0x20, {0x70: pystub(c, 1, this=True, ret=lambda em, k: r.choice([0, 1, 0x100]))})
    _w(c, so + 0x1a9f, s1a9f if r.random() < 0.9 else 0)

    def s390(em, k):   # slot 0x390 (ret 0xc): (bone, matrix, vector); slot 0x3a0 is a plain `ret`, the two pushes before it are its 2nd and 3rd args
        em.wbytes(em.arg32(1), bytes(r.getrandbits(8) for _ in range(36)))
        em.wbytes(em.arg32(2), bytes(r.getrandbits(8) for _ in range(12)))
    creator = rnd(c, 0x20)
    t = obj(c, 0x160, {0x3a0: pystub(c, 0, this=True, ret=lambda em, k: r.getrandbits(32)),
                       0x390: pystub(c, 3, this=True, stackmark=(1, 2), side=s390), 0x20: pystub(c, 0, this=True, ret=creator)})
    _w(c, t + 0x153, r.choice([0, 0x31, 0x99]))
    hook_rec(c, 0x44b610, 0, this=True)
    hook_rec(c, 0x44b740, 1, pop=0)
    hook_rec(c, 0x43ec00, 6, this=True, deref={0: 9, 1: 3}, ret=lambda em, k: r.choice([0x31, 0x99, 0x5]))
    return [t, r.getrandbits(32), r.getrandbits(32), r.getrandbits(32)]


S(0x467260, 'GUESS replace_effect_handle', 'thiscall', None, ret='eax', gen=_g467260, note='batch67558')
