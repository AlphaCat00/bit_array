#ifndef __BIT_ARRAY__
#define __BIT_ARRAY__
#include <stdint.h>
#include <type_traits>
template <uint64_t bits, uint64_t size, class Enable = void>
class bit_array_base;

// 000
template <uint64_t bits, uint64_t size>
    class bit_array_base < bits,
    size, typename std::enable_if<!(bits & 7) && bits<64>::type> {
   protected:
    constexpr static uint64_t _shift = 0;
    constexpr static uint64_t _size = 1 << _shift;
    constexpr static uint64_t _mask = _size - 1;
    struct {
        uint64_t _0 : bits;
    } __attribute__((__packed__)) _buf[(size + _mask) >> _shift];

   public:
    inline uint64_t get(uint64_t index) {
        return _buf[index >> _shift]._0;
    }

    inline void set(uint64_t index, uint64_t val) {
        _buf[index >> _shift]._0 = val;
    }
};

// 100
template <uint64_t bits, uint64_t size>
    class bit_array_base < bits,
    size, typename std::enable_if<!(bits & 3) && (bits & 4) && bits<64>::type> {
   protected:
    constexpr static uint64_t _shift = 1;
    constexpr static uint64_t _size = 1 << _shift;
    constexpr static uint64_t _mask = _size - 1;
    struct {
        uint64_t _0 : bits;
        uint64_t _1 : bits;
    } __attribute__((__packed__)) _buf[(size + _mask) >> _shift];

   public:
    inline uint64_t get(uint64_t index) {
        switch (index & _mask) {
            case 0:
                return _buf[index >> _shift]._0;
            case 1:
                return _buf[index >> _shift]._1;
        }
        return 0;
    }

    inline void set(uint64_t index, uint64_t val) {
        switch (index & _mask) {
            case 0:
                _buf[index >> _shift]._0 = val;
            case 1:
                _buf[index >> _shift]._1 = val;
        }
    }
};

// X10
template <uint64_t bits, uint64_t size>
    class bit_array_base < bits,
    size, typename std::enable_if<!(bits & 1) && (bits & 2) && bits<64>::type> {
   protected:
    constexpr static uint64_t _shift = 2;
    constexpr static uint64_t _size = 1 << _shift;
    constexpr static uint64_t _mask = _size - 1;
    struct {
        uint64_t _0 : bits;
        uint64_t _1 : bits;
        uint64_t _2 : bits;
        uint64_t _3 : bits;
    } __attribute__((__packed__)) _buf[(size + _mask) >> _shift];

   public:
    inline uint64_t get(uint64_t index) {
        switch (index & _mask) {
            case 0:
                return _buf[index >> _shift]._0;
            case 1:
                return _buf[index >> _shift]._1;
            case 2:
                return _buf[index >> _shift]._2;
            case 3:
                return _buf[index >> _shift]._3;
        }
        return 0;
    }

    inline void set(uint64_t index, uint64_t val) {
        switch (index & _mask) {
            case 0:
                _buf[index >> _shift]._0 = val;
            case 1:
                _buf[index >> _shift]._1 = val;
            case 2:
                _buf[index >> _shift]._2 = val;
            case 3:
                _buf[index >> _shift]._3 = val;
        }
    }
};

// XX1
template <uint64_t bits, uint64_t size>
    class bit_array_base < bits,
    size, typename std::enable_if<(bits & 1) && bits<64>::type> {
   protected:
    constexpr static uint64_t _shift = 3;
    constexpr static uint64_t _size = 1 << _shift;
    constexpr static uint64_t _mask = _size - 1;
    struct {
        uint64_t _0 : bits;
        uint64_t _1 : bits;
        uint64_t _2 : bits;
        uint64_t _3 : bits;
        uint64_t _4 : bits;
        uint64_t _5 : bits;
        uint64_t _6 : bits;
        uint64_t _7 : bits;
    } __attribute__((__packed__)) _buf[(size + _mask) >> _shift];

   public:
    inline uint64_t get(uint64_t index) {
        switch (index & _mask) {
            case 0:
                return _buf[index >> _shift]._0;
            case 1:
                return _buf[index >> _shift]._1;
            case 2:
                return _buf[index >> _shift]._2;
            case 3:
                return _buf[index >> _shift]._3;
            case 4:
                return _buf[index >> _shift]._4;
            case 5:
                return _buf[index >> _shift]._5;
            case 6:
                return _buf[index >> _shift]._6;
            case 7:
                return _buf[index >> _shift]._7;
        }
        return 0;
    }

    inline void set(uint64_t index, uint64_t val) {
        switch (index & _mask) {
            case 0:
                _buf[index >> _shift]._0 = val;
            case 1:
                _buf[index >> _shift]._1 = val;
            case 2:
                _buf[index >> _shift]._2 = val;
            case 3:
                _buf[index >> _shift]._3 = val;
            case 4:
                _buf[index >> _shift]._4 = val;
            case 5:
                _buf[index >> _shift]._5 = val;
            case 6:
                _buf[index >> _shift]._6 = val;
            case 7:
                _buf[index >> _shift]._7 = val;
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
    uint64_t array_type() { return this->_shift; }
};

#endif