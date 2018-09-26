
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


const int N_START = 1024;   // 2**10
const int N_MAX = 67108864; // 2**26
const int NANOS_PER_SEC = 1000000000;



int main() {

    // timer variables
    struct timespec start = {.tv_sec = 0, .tv_nsec = 0};
    struct timespec end = {.tv_sec = 0, .tv_nsec = 0};

    // calculate time to generate rand_bits (store as rand_gen_time)
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(int i=0;i<100000;i++) {
        long rand_bits = random();
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double rand_gen_time = (end.tv_nsec - start.tv_nsec)/100000;


    // begin main loop
    for (int i = N_START; i <= N_MAX; i *= 2) {
        printf("Initializing new array\n");
        u_int32_t* numbers = malloc(sizeof(u_int32_t) * i);
        for(u_int32_t j = 0; j < i; j++) {
            numbers[j] = j;
        }

        // measure read/write time
        // start the timer
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for(int j=0;j<1000000;j++) {
            long rand_index = random() % i;
            // read/write to numbers[rand_index]
            numbers[rand_index] += 1;
        }
        //end the timer
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        double long time_elapsed = (end.tv_nsec - start.tv_nsec) - (1000000*rand_gen_time);

        printf("Latency per read with N = %d is %Lf\n", i, time_elapsed/1000000);        
            
        printf("Freeing array\n\n");
        free(numbers);
    }
}
