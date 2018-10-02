# CSCI389-hw1
### Joe Meyer and Tanmay Dubey
## Results

The graph of average memory read latency against buffer size is given below:
![Memory read latency vs buffer size](/graphs/graph1.gif)

From the data, we can infer the following sizes for the L1, L2 and L3 caches:

Cache | Size
----- | ----
L1 | 128 KB
L2 | 1 MB
L3 | 32 MB

It's possible there's some fixed overhead independent of buffer size that's cuasing our readings to be rather high for lower values. This fixed overhead would not affect the values 
