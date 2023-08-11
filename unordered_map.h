//
// Created by 93539 on 2023/8/10.
//

#ifndef UNORDERED_MAP_UNORDERED_SET_UNORDERED_MAP_H
#define UNORDERED_MAP_UNORDERED_SET_UNORDERED_MAP_H

#include "HashTable.h"

namespace wyp {
    template<class K, class V, class Hash = HashFunc<K>>
    class unordered_map {
        struct MapKeyOfT {
            const K &operator()(const std::pair<const K, V> &kv) {
                return kv.first;
            }
        };

    public:

        typedef typename HashTable<K, std::pair<const K, V>, Hash, MapKeyOfT>::iterator iterator;

        iterator begin() {
            return _ht.begin();
        }

        iterator end() {
            return _ht.end();
        }

        std::pair<iterator, bool> insert(const std::pair<K, V> &value) {
            return _ht.insert(value);
        }

        V &operator[](const K &key) {
            std::pair<iterator, bool> ret = _ht.insert(std::make_pair(key, V()));
            return ret.first->second;
        }

    private:
        HashTable <K, std::pair<const K, V>, Hash, MapKeyOfT> _ht;
    };
} //wyp

#endif //UNORDERED_MAP_UNORDERED_SET_UNORDERED_MAP_H
