# CSCI389-hw1
### Joe Meyer and Tanmay Dubey
## Results

The graph of average memory read latency against buffer size is given below:
![Memory read latency vs buffer size](/graphs/graph1.gif)

From the data, we can infer the following sizes for the L1, L2 and L3 caches:

Cache | Size
----- | ----
L1 | 100 KB
L2 | 500 KB
L3 | 4 MB

We deduce these cache sizes because the graph illustrates significant jumps in data-access-time at the points where (we infer) L1 and L3 run out of memory, with a roughly linear stretch connecting the two flat sections indicating L1 and L3 which we infer represents data gradually overflowing from L1 to L2, and then from L2 to L3.

It's possible there's some fixed overhead independent of buffer size that's causing our readings to be rather high for lower values. This fixed overhead would disproportionately affect the faster reads, elevating the minimum access time without significantly impacting the maximum time. 

My actual CPU cache volumes (according to the internet) are:

Cache | Size
----- | ----
L1 | 64 KB
L2 | 500 KB
L3 | 3 MB

The graph could lack a clean step form because memory accesses may still be from cache even after all the caches are full - some overflow into disk memory does not mean that reads are happening exclusively from disk. Similarly, some overflow into bigger caches does not mean that some reads are not still happening from L1 and L2. Thus it should not be surprising that the graph is not a perfect step function.
