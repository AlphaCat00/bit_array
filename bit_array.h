#ifndef __BIT_ARRAY__
#define __BIT_ARRAY__
#include <stdint.h>

#include <type_traits>
template <uint64_t bits, uint64_t size, class Enable = void>
class bit_array_base;

template <uint64_t bits, uint64_t size>
    class bit_array_base < bits,
    size, typename std::enable_if<bits<64>::type> {
   protected:
    constexpr static uint64_t _shift = 3;
    constexpr static uint64_t _mask = (1 << _shift) - 1;
    struct _buf_t {
        uint64_t _0 : bits;
        uint64_t _1 : bits;
        uint64_t _2 : bits;
        uint64_t _3 : bits;
        uint64_t _4 : bits;
        uint64_t _5 : bits;
        uint64_t _6 : bits;
        uint64_t _7 : bits;
    } __attribute__((__packed__));
    uint8_t _buf[(size * bits + 7) >> 3];
    inline _buf_t &_get_buf(uint64_t index) {
        return reinterpret_cast<_buf_t *>(_buf)[index >> _shift];
    };

   public:
    inline uint64_t get(uint64_t index) {
        switch (index & _mask) {
            case 0:
                return _get_buf(index)._0;
            case 1:
                return _get_buf(index)._1;
            case 2:
                return _get_buf(index)._2;
            case 3:
                return _get_buf(index)._3;
            case 4:
                return _get_buf(index)._4;
            case 5:
                return _get_buf(index)._5;
            case 6:
                return _get_buf(index)._6;
            case 7:
                return _get_buf(index)._7;
        }
        return 0;
    }

    inline void set(uint64_t index, uint64_t val) {
        switch (index & _mask) {
            case 0:
                _get_buf(index)._0 = val;
            case 1:
                _get_buf(index)._1 = val;
            case 2:
                _get_buf(index)._2 = val;
            case 3:
                _get_buf(index)._3 = val;
            case 4:
                _get_buf(index)._4 = val;
            case 5:
                _get_buf(index)._5 = val;
            case 6:
                _get_buf(index)._6 = val;
            case 7:
                _get_buf(index)._7 = val;
        }
    }
};

template <uint64_t bits, uint64_t size>
class bit_array : public bit_array_base<bits, size> {
   public:
    class reference {
        bit_array *base;
        uint64_t index;
        reference();

       public:
        reference(bit_array &b, uint64_t i) : base(&b), index(i) {}
        ~reference() {}
        reference &operator=(uint64_t x) {
            base->set(index, x);
            return *this;
        }
        operator uint64_t() const {
            return base->get(index);
        }
    };
    reference operator[](size_t __pos) {
        return reference(*this, __pos);
    }
};

#endif