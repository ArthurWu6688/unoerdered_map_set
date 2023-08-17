//
// Created by 93539 on 2023/8/17.
//

#ifndef BITSET_BITSET_H
#define BITSET_BITSET_H

#include <iostream>
#include <vector>

namespace wyp {
    template<size_t N>
    class bitset {
    public:
        bitset() {
            _bits.resize(N / 8 + 1, 0);
        }

        void set(size_t x) {
            size_t i = x / 8;
            size_t j = x % 8;
            _bits[i] |= (1 << j);
        }

        void reset(size_t x) {
            size_t i = x / 8;
            size_t j = x % 8;
            _bits[i] &= ~(1 << j);
        }

        bool test(size_t x) {
            size_t i = x / 8;
            size_t j = x % 8;
            return _bits[i] & (1 << j);
        }

    private:
        std::vector<char> _bits;
    };

} // wyp

#endif //BITSET_BITSET_H
