from pilot import S
from unicorn.x86_const import UC_X86_REG_EDX
from recruits_util import rnd,clear_hooks,pystub,hook_rec

def gen(c):
    clear_hooks(c); e=c.emu; r=c.rng
    hook_rec(c,0x7003b0,0,ret=lambda em,k:r.getrandbits(32))
    def qpc(em,regs):
        p=em.arg32(0); v=r.getrandbits(64)
        em.w32(p,v & 0xffffffff); em.w32(p+4,v>>32)
        em.ret(eax=1,argbytes=4)
    e.stub_import('QueryPerformanceCounter',qpc)
    def clock(em,regs): em.ret(eax=r.randrange(1,0x7fffffff))
    e.stub_import('clock',clock)
    selfp=rnd(c,0x2400); vt=rnd(c,0x210)
    flag=r.choice([0,1])
    e.w32(selfp,vt); e.w8(selfp+0x1e90,flag)
    # flag 0: the timestamp comes from sysobj slot 0x1c8 (thiscall, file and line, 64-bit result in EDX:EAX) instead of QueryPerformanceCounter
    def sysclock(em,regs):
        v=r.getrandbits(64)
        em.calllog.append(('clk',em.reg('ecx'),em.arg32(0),em.arg32(1)))
        em.mu.reg_write(UC_X86_REG_EDX,v>>32)
        em.ret(eax=v&0xffffffff,argbytes=8)
    sysvt=rnd(c,0x210); sysp=rnd(c,0x40)
    e.w32(sysp,sysvt); e.w32(sysvt+0x1c8,e.stub_fn('sysclock',sysclock)); e.w32(0x70039c,sysp)
    e.w32(vt+0x1fc,pystub(c,5,this=True,ret=0))
    return [selfp]
S(0x4234f0,'GUESS stamp event time','thiscall',None,ret=None,gen=gen,note='batch104022')
