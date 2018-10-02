# CSCI389-hw1
### Joe Meyer and Tanmay Dubey
## Results

The graph of average memory read latency against buffer size is given below:
![Memory read latency vs buffer size](/graphs/graph1.gif)

From the data, we can infer the following sizes for the L1, L2 and L3 caches:

Cache | Size
----- | ----
L1 | 128 KB
L2 | 512 KB
L3 | 4 MB

We deduce these cache sizes because the graph illustrates significant jumps in data-access-time at the points where (we infer) L1 and L3 run out of memory, with a roughly linear stretch connecting the two flat sections indicating L1 and L3 which we infer represents data gradually overflowing from L1 to L2, and then from L2 to L3.

We did not get the values linked to on the assignment page; our numbers were considerably higher for both L1 and L2, and somewhat low for main memory. The low readings for large buffers can be explained due to not all the values being fetched from main memory; even for 32 MB buffers, a significant portion of the buffer would still be cached, and thus the average latencies are slightly lower than those for main memory. The high readings for small buffers are harder to explain--one possible cause could be some fixed overhead independent of buffer size. This overhead would increase the readings significantly for smaller buffer sizes, and less so for larger ones. Examples of overhead in our code (not necessarily independent of buffer size) are the modulo calculations and the loop condition in the `for` loop. 

My actual CPU cache volumes (according to the internet) are:

Cache | Size
----- | ----
L1 | 64 KB
L2 | 512 KB
L3 | 3 MB

The graph could lack a clean step form because memory accesses may still be from cache even after all the caches are full - some overflow into disk memory does not mean that reads are happening exclusively from disk. Similarly, some overflow into bigger caches does not mean that some reads are not still happening from L1 and L2. Thus it should not be surprising that the graph is not a perfect step function.

NOTE: Our data is from benchmark9.c. We made a benchmark11.c which attempted to fix our abnormally high minimum access time by utilizing a different randomization method, but benchmark11.c does not yield sensible data. We include it anyway because we put a lot of time into improving the clarity/randomization method of the code.
