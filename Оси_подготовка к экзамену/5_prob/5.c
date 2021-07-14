#include <stdio.h>
#include <inttypes.h>



int main ()
{
    int64_t out[64] = {0};
    int64_t  val;
    while(scanf("%"SCNx64, &val) > 0){
        for(int i = 0; i < 64; i++){
            int64_t g = 1;
            if((val & (g << i)) != 0){
                out[i] += val;
            }
        }
    }
    for(int i = 0; i < 64; i++){
        printf("%"PRId64"\n", out[i]);
    }
    return 0;
}
