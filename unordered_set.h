//
// Created by 93539 on 2023/8/10.
//

#ifndef UNORDERED_MAP_UNORDERED_SET_UNORDERED_SET_H
#define UNORDERED_MAP_UNORDERED_SET_UNORDERED_SET_H

#include "HashTable.h"

namespace wyp {
    template<class K>
    class setKeyOfT {
    public:
        const K &operator()(const K &Key) {
            return Key;
        }
    };

    template<class K, class Hash = HashFunc<K>>
    class unordered_set {
    public:
        typedef typename HashTable<K, K, Hash, setKeyOfT<K>>::iterator iterator;

        iterator begin() {
            return _ht.begin();
        }

        iterator end() {
            return _ht.end();
        }

        std::pair<iterator, bool> insert(const K &Key) {
            return _ht.insert(Key);
        }

    private:
        HashTable<K, K, Hash, setKeyOfT<K>> _ht;
    };
} //wyp


#endif //UNORDERED_MAP_UNORDERED_SET_UNORDERED_SET_H
