
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int N_START = 1024;   // 2**10
const int N_MAX = 67108864*4; // 2**28
const int NANOS_PER_SEC = 1000000000;



int main() {

    // seed random num generator
    srand(time(NULL));
   
    // calculate time to generate rand_bits (store as rand_gen_time)
    clock_t start = clock();
    for(int i=0;i<100000;i++) {
        long rand_bits = random();
    }
    clock_t end = clock();
    double rand_gen_time = (end - start)/((double)CLOCKS_PER_SEC*100000);


    // begin main loop
    for (int i = N_START; i <= N_MAX; i *= 2) {
        printf("Initializing new array\n");
        u_int8_t* numbers = malloc(sizeof(u_int8_t) * i);
        for(u_int32_t j = 0; j < i; j++) {
            int r = rand();
            numbers[j] = r%100;
        }

        // measure read/write time
        // start the timer
        clock_t start = clock();
        for(int j=0;j<1000000;j++) {
            long rand_index = random() % i;
            // read/write to numbers[rand_index]
            numbers[rand_index] += 1;
        }
        //end the timer
        clock_t end = clock();
        double long time_elapsed = NANOS_PER_SEC*((end - start) - (1000000*rand_gen_time))/(1000000*(double)CLOCKS_PER_SEC);

        printf("Latency per read with N = %d is %Lf\n", i, time_elapsed);        
            
        printf("Freeing array\n\n");
        free(numbers);
    }
}