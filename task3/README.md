# Website Analytics
Implementation took approximately 1 hour.    

## Build and Run for Linux
Start console from project directory and enter the commands
``` Bash
g++ -std=c++20 -o WebAnalytics main.cpp CSVHandler.cpp
./WebAnalytics
```

# Complexity
N - lines in the first file  
K - lines in the second file  

**Time Complexity: $O(N+K)$** - We simply traverse both files line by line and convert the first 2 columns to numbers,
hence the complexity is $O(N+K)$. Inserting into a hast table or at the end of an array, and all checks, takes $O(1)$ on average.  

**Space Complexity: $O(N)$** - It creates 2 additional vectors, to save the results, 
2 hash tables to validate the already entered users, this takes $O(N)$ of memory. 
And at the end the key-value hash table, which contains other hash tables, but here it is also $O(N)$, 
because no more than N keys will be written here and the sum of all written values will not exceed N.
