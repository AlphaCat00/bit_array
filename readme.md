# bit_array

A compact C++ array whose elements' length can be arbitrary **bits** (<64).

# example


    #include <stdio.h>
    #include "bit_array.h"

    int main() {
        bit_array<6, 4> a;
        bit_array<3, 4> b;
        b[0] = a[0] = 22;
        printf("%ld %ld\n", a.get(0), uint64_t(b[0]));
        printf("%ld\n", sizeof(bit_array<3, 4>));
        printf("%ld\n", sizeof(bit_array<4, 4>));
        printf("%ld\n", sizeof(bit_array<6, 4>));
        printf("%ld\n", sizeof(bit_array<8, 4>));
        printf("%ld\n", sizeof(bit_array<16, 4>));
        return 0;
    }

