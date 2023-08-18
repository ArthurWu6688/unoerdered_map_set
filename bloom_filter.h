//
// Created by 93539 on 2023/8/18.
//

#ifndef UNORDERED_MAP_UNORDERED_SET_BLOOM_FILTER_H
#define UNORDERED_MAP_UNORDERED_SET_BLOOM_FILTER_H

#include <iostream>
#include <bitset>

namespace wyp {
    struct BKDRHash {
        size_t operator()(const std::string &key) {
            size_t hash = 0;
            for (auto ch: key) {
                hash *= 131;
                hash += ch;
            }
            return hash;
        }
    };

    struct APHash {
        size_t operator()(const std::string &key) {
            size_t hash = 0;
            int i = 0;
            for (auto ch: key) {
                if ((i & 1) == 0) {
                    hash ^= ((hash << 7) ^ (ch) ^ (hash >> 3));
                } else {
                    hash ^= (~((hash << 11) ^ (ch) ^ (hash >> 5)));
                }
                ++i;
            }
            return hash;
        }
    };

    struct DJBHash {
        size_t operator()(const std::string &key) {
            size_t hash = 5318;
            for (auto ch: key) {
                hash += (hash << 5) + ch;
            }
            return hash;
        }
    };

    template<size_t N, size_t X = 5, class K = std::string,
            class HashFunc1 = BKDRHash,
            class HashFunc2 = APHash,
            class HashFunc3 = DJBHash>
    class bloom_filter {
    public:
        void set(const K &Key) {
            size_t hash1 = HashFunc1()(Key) % (N * X);
            size_t hash2 = HashFunc2()(Key) % (N * X);
            size_t hash3 = HashFunc3()(Key) % (N * X);
            _bs.set(hash1);
            _bs.set(hash2);
            _bs.set(hash3);
        }

        bool test(const K &Key) {
            size_t hash1 = hash1 = HashFunc1()(Key) % (N * X);
            if (!_bs.test(hash1)) {
                return false;
            }
            size_t hash2 = HashFunc2()(Key) % (N * X);
            if (!_bs.test(hash2)) {
                return false;
            }
            size_t hash3 = HashFunc3()(Key) % (N * X);
            if (!_bs.test(hash3)) {
                return false;
            }
            return true;
        }

    private:
        std::bitset<N * X> _bs;
    };

} // wyp

#endif //UNORDERED_MAP_UNORDERED_SET_BLOOM_FILTER_H
