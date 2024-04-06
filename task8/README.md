# Student's Capital
From reading the assignment to full realization spent approximately 1 hour.

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
Time Complexity: $O(height * width)$  
Space Complexity: $O(K)$ - We create an additional vecpair array and a priority queue
