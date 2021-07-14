#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int checkblock (unsigned char *bitmap, long nom, long nmax){
	if( nom > nmax){
		return -1;
	}
    long nbyte = nom / 8;
    int bit = nom % 8;
    return (bitmap[nbyte]>>bit) & 1;
}

long free_blocks(unsigned char *bitmap, long nblocks)
{
    int co =(nblocks + 7) / 8;
    long c = 0;
    for (long i = 0; i < co; i ++){
        if (bitmap[i] != 0xFF){
            int cp = bitmap[i];
            int bc;
            if(i < co-1) {
                bc = 8;
            } else {
                bc = nblocks % 8;
            }
            for (int j = 0; j < bc; j++){
                c += !(cp & 1);
                cp >>= 1;
            }
        }
    }
    return c;
}

int main (int argc, char *argv[]) {
     unsigned char bitmap[10] ={
        0xFF, 0x7F, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF0, 0x00
     };
     long n = free_blocks(bitmap, 79);
     printf("%ld\n", n);

     int busy1 = checkblock(bitmap, 14, 80);
     int busy2 = checkblock(bitmap, 15, 80);
     printf("%d %d\n",busy1, busy2);
     return 0;
}
