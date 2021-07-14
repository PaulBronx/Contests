

unsigned  Vo_to_Pa (unsigned Virt_A,unsigned *Table_str) {
        unsigned VP = Virt_A >> 10;
        unsigned offset = Virt_A & 1023;
        unsigned FP = Table_str[VP]; 
        return(FP << 10) | offset ;
}
