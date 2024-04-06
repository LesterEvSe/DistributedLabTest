# Student's Capital
From reading the assignment to full realization spent approximately 1 hour.  
It is assumed that the lengths of arrays gains and price will be the same and the input numbers will be in the range [-2^31; 2^31-1]

## Build and Run for Linux
Start console from project directory and enter the commands
``` Bash
mkdir build
cd build
cmake ..
make
./StudentCapital
```

# Complexity
Suppose that N is the number of notebooks, and K the number of elements in the gains array and in the price array.  
**Time Complexity: $O(K * LogK)$** - The std::sort algorithm requires $O(K * LogK)$ of time.  
The priority queue insertion requires $O(LogK)$ of time. We do the insertion at most N times.  
As a result, we get in the worst case$O(K * LogK + N * LogK) = O(std::min(K, N) * LogK) = O(K * LogK)$  
**Space Complexity: $O(K)$** - We create an additional vecpair array and a priority queue
