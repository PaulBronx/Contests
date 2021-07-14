#include <signal.h>
#include <unistd.h>

enum {
    WORD_SIZE = 32,
    OFFSET_BITS = 9,
    PAGE_SIZE = 1 << OFFSET_BITS,        //512d  = 00000000.00000000.00000010.00000000
    OFFSET_MASK = PAGE_SIZE - 1,         //512-1 = 00000000.00000000.00000001.11111111
    PAGE_NOT_PRESENT = 1<<(WORD_SIZE-1), //        10000000.00000000.00000000.00000000
    SIGPL = 30,
    No_Page = -1
};

unsigned To_PA(unsigned *Pt, unsigned vaddr, int pid)
{
    //uint32_t vaddr; //PPPPPPPP.PPPPPPPP.PPPPPPPo.oooooooo
    unsigned page = vaddr >> OFFSET_BITS; // 00000000.0PPPPPPP.PPPPPPPP.PPPPPPPP
    unsigned offset = vaddr & OFFSET_MASK; // 00000000.00000000.0000000o.oooooooo

    //uint32_t Pt[SIZE]; // {p0000000.0PPPPPPP.PPPPPPPP.PPPPPPPP}[SIZE], p=1 - нет страницы

    unsigned baddr = Pt[page]; //p0000000.0PPPPPPP.PPPPPPPP.PPPPPPPP

    if(baddr & PAGE_NOT_PRESENT) {
        kill(pid, SIGPL);
        _exit(No_Page);
    }

    unsigned paddr = (baddr << OFFSET_BITS) | offset; //PPPPPPPP.PPPPPPPP.PPPPPPPo.oooooooo

    return paddr;
}


#include <stdio.h>
#define VA(pg,off) (((pg)<<OFFSET_BITS) | (off))

unsigned Pt[100] = {
        10, 20, 30, -1, -1, -1
};

int main() {
    unsigned paddr = To_PA(Pt, VA(1,100), getpid());
    unsigned good_paddr = VA(20, 100);

    printf("a1 = %08x, a2 = %08X\n", paddr, good_paddr);

    paddr = To_PA(Pt, VA(4,100), getpid());

    return 0;
}
