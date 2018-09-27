
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int MIN_BUFFER_SIZE = 1024;       // 2**10
const int MAX_BUFFER_SIZE = 67108864*4; // 2**28
const int NANOS_PER_SEC = 1000000000;



int main() {

    // seed random num generator
    srand(time(NULL));

    u_int32_t iterations = 100000;
   
    // calculate time to generate rand_bits (store as rand_gen_time)
    clock_t start = clock();
    for(int i=0;i<iterations;i++) {
        long rand_bits = random();
    }
    clock_t end = clock();
    double rand_gen_time = (end - start)/((double)CLOCKS_PER_SEC*iterations);


    // begin main loop
    for (u_int32_t buff_size = MIN_BUFFER_SIZE; buff_size <= MAX_BUFFER_SIZE; buff_size *= 2) {
        printf("Initializing new array\n");
        u_int8_t* numbers = malloc(sizeof(u_int8_t) * buff_size);
        // fill in buffer w rand val.s
        for(u_int32_t j = 0; j < buff_size; j++) {
            int r = rand();
            numbers[j] = r%100;
        }

        iterations = 1000000;

        // measure read/write time
        // start the timer
        clock_t start = clock();
        for(int j=0;j<iterations;j++) {
            long rand_index = random() % buff_size;
            // read/write to numbers[rand_index]
            numbers[rand_index] += 1;
        }
        //end the timer
        clock_t end = clock();
        double long time_elapsed = NANOS_PER_SEC*((end - start) - (iterations*rand_gen_time))/(iterations*(double)CLOCKS_PER_SEC);

        printf("Latency per read with N = %d is %Lf\n", buff_size, time_elapsed);        
            
        printf("Freeing array\n\n");
        free(numbers);
    }
}