
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


const int MIN_BUFFER_SIZE = 1<<10;       // 2**10
const int MAX_BUFFER_SIZE = 1<<28;       // 2**28
const int NANOS_PER_SEC = 1000000000;


// returns randomized array w indexes 1 - buff_size;
u_int32_t* shuffle(u_int32_t buff_size, u_int32_t iterations) {
    //create array of every index of buffer
    u_int32_t* indexes = malloc(sizeof(u_int32_t) * buff_size);
    for(u_int32_t j = 0; j < buff_size; j++) {
        indexes[j] = j;
    }
    // temp stores values during swaps
    u_int8_t temp;
    // shuffle the array
    for(u_int32_t j = 0; j < buff_size; j++) {
        // swap elts at j <-> rand index
        u_int32_t rand_ind = random() % buff_size;
        temp = indexes[rand_ind];
        indexes[rand_ind] = indexes[j];
        indexes[j] = temp;
    }
    return indexes;
}

// returns avg time to generate+access rand. index array (+ read from buffer if numbers != NULL)
double long calc_time(u_int32_t buff_size, u_int32_t iterations, u_int8_t* numbers) {
    u_int32_t dummy;
    clock_t start = clock();
    for(u_int32_t j=0;j<iterations;j++) {
        u_int32_t* shuffled = shuffle(buff_size, iterations);
        for(u_int32_t x = 0; x < buff_size; x++) {
            dummy = shuffled[x];
            if(numbers) {
                dummy = numbers[dummy];
            }
            dummy += 1;
            // ensure dummy does not get optimized away
            if(dummy == 0) {
                printf("action");
            }
        }
    }
    clock_t end = clock();
    double long avg_time = (end - start)*NANOS_PER_SEC/((double)CLOCKS_PER_SEC*iterations*buff_size);
    return avg_time;
}

// returns buff-length array of bytes init.d to rand val.s
u_int8_t* make_buffer(u_int32_t buff_size) {
    u_int8_t* numbers = malloc(sizeof(u_int8_t) * buff_size);
    for(u_int32_t j = 0; j < buff_size; j++) {
        u_int8_t r = rand() % 100;
        numbers[j] = r;
    }
    return numbers;
}



int main() {

    // seed random num generator
    srand(time(NULL));

    // iterations of measurements
    u_int32_t iterations = 1000;
   

    // begin main loop
    for (u_int32_t buff_size = MIN_BUFFER_SIZE; buff_size <= MAX_BUFFER_SIZE; buff_size*=2) {

        // calculate time to generate/randomize/access array of indexes
        double long extra_time = calc_time(buff_size, iterations, NULL);
        printf("extra time: %Lf\n", extra_time);

        // create/initialize buffer of rand vals
        printf("Initializing new array\n");
        u_int8_t* numbers = make_buffer(buff_size);

        // do many random reads to ensure buffer values are cached
        calc_time(buff_size, iterations, numbers);



        // measure read/write time
        double long avg_read_latency = calc_time(buff_size, iterations, numbers) - extra_time;
        
        printf("Latency per read with N = %f is %Lf\n", log2(buff_size), avg_read_latency);        
            
        printf("Freeing array\n\n");
        free(numbers);
    }
}