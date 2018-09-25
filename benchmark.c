#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int N_START = 1024;
const int N_MAX = 67108864; // 2**26
uint8_t value = 0;


int main() {

    for (int i = N_START; i <= N_MAX; i *= 2) {

        printf("Initializing new array\n");
        uint8_t *numbers = malloc(sizeof(uint8_t) * i);
    
        for(int j = 0; j < i; j++) {
            numbers[j] = j;
        }

        struct timespec start = {.tv_sec = 0, .tv_nsec = 0};
        struct timespec end = {.tv_sec = 0, .tv_nsec = 0};

        for(int k = 0; k < 10; k++) {
            
            if (k % 2 == 0) {
                
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                value = numbers[k]; // problem here is we're also measuring time to write to value, which may not be in cache
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                int t = end.tv_nsec - start.tv_nsec;
                printf("Latency of read with N = %d is %d\n", i, t);
            }         
            else {
                
                int j = i - k;
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                value = numbers[j]; // problem here is we're also measuring time to write to value, which may not be in cache
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                int t = end.tv_nsec - start.tv_nsec;
                printf("Latency of read with N = %d is %d\n", i, t);
            }
        }
        printf("Freeing array\n\n");
        free(numbers);
    }
}
