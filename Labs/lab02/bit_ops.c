#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns
    // 0 or 1)
    if(n <=31 && n >= 0){
        unsigned temp = 1 << n;
        temp = temp & x;
        temp >>= n;
        return temp;
    }else

    return -1;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    unsigned temp = v << n;
    unsigned nth_bit = ~(1 << n);
    (*x) = (*x) & nth_bit ;
    (*x) = (*x) | temp;    
    return;
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    unsigned temp = 1 << n;
    (*x) = (*x) ^ temp;
}

