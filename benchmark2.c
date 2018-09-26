//#include <stdint.h>
// Is stdint necessary?

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int N_START = 1024;   // 2**10
const int N_MAX = 67108864; // 2**26
const int NANOS_PER_SEC = 1000000000;
// removed var. 'value', not used


int main() {

    for (int i = N_START; i <= N_MAX; i *= 2) {

        printf("Initializing new array\n");
        u_int32_t *numbers = malloc(sizeof(u_int32_t) * i);
        // changed numbers from uint8 array to uint32 so can hold N_MAX

        for(u_int32_t j = 0; j < i; j++) {
            numbers[j] = j;
        }

        // removed var.s for timing; replacing timer w simpler func

        // avg of 1000 operations in nanosecs
        double avg_of_1000 = 0;

        for(int k = 5; k < 1005; k++) {
            
            // start the timer
            clock_t start = clock();

            // read/write to numbers[k]
            numbers[k]+=1;

            //end the timer
            clock_t end = clock();
            double time_elapsed = (end - start)/(double)CLOCKS_PER_SEC;
            avg_of_1000 += time_elapsed*NANOS_PER_SEC/1000;
            } 
        printf("Latency per read with N = %d is %f\n", i, avg_of_1000);        
            
        printf("Freeing array\n\n");
        free(numbers);
    }
}