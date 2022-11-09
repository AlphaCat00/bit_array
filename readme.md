# bit_array

A compact C++ array whose elements' length can be arbitrary **bits** (<64).

# example


    #include <stdio.h>
    #include "bit_array.h"

    int main() {
        using namespace compact_bit_array;
        bit_array<6, 4> a;
        bit_array<3, 4> b;
        b[0] = a[0] = 22;
        printf("%ld %ld\n", a.get(0), uint64_t(b[0]));
        printf("%ld\n", sizeof(bit_array<3, 4>));
        printf("%ld\n", sizeof(bit_array<4, 4>));
        printf("%ld\n", sizeof(bit_array<6, 4>));
        printf("%ld\n", sizeof(bit_array<8, 4>));
        printf("%ld\n", sizeof(bit_array<16, 4>));
        
        bit_array<5, 500, impl_bitwise<5,500>> test;
        printf("%ld\n", sizeof(test));
        for (uint64_t i = 0; i < 500; i++)
            test.set(i, i);
        for (uint64_t i = 0; i < 500; i++)
            printf("%ld\n", test.get(i));
        return 0;
    }

