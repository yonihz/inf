/*

Psuede-code for circular queue:

Data structure:
arr
capacity (size of arr)
size (populated elements in array)
read_idx (index of front element)

Initialization:
arr = ...
capacity = ...
size = 0;
read_idx = 0;


Push:
1. Check if full (size >= capacity) => if true, do nothing
2. copy data to arr in the index (read_idx + size) % capacity
3. Increment size: size = size + 1

Pop:
1. Check if empty (size <= 0) => if true, do nothing
2. Increment index: idx_read = (idx_read + 1) % cap
3. Decrement size: size = size - 1
4. Optional: if empty (size == 0) => read_idx = 0;

*/
