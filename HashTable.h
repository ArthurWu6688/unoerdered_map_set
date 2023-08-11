//
// Created by 93539 on 2023/8/10.
//

#ifndef UNORDERED_MAP_UNORDERED_SET_HASHTABLE_H
#define UNORDERED_MAP_UNORDERED_SET_HASHTABLE_H

#include <iostream>
#include <vector>

namespace wyp {
    template<class K>
    class HashFunc {
    public:
        size_t operator()(const K &Key) {
            return (size_t) Key;
        }
    };

    template<>
    class HashFunc<std::string> {
    public:
        size_t operator()(const std::string &Key) {
            size_t hash = 0;
            for (auto ch: Key) {
                hash *= 131;
                hash += ch;
            }
            return hash;
        }
    };

    template<class T>
    struct HashNode {
        T _Data;
        HashNode<T> *_next;

        HashNode(const T &Data)
                : _Data(Data), _next(nullptr) {

        }
    };

    template<class K, class T, class Hash, class KeyOfT>
    class HashTable;

    template<class K, class T, class Hash, class KeyOfT>
    struct __HTIterator {
        typedef HashNode<T> Node;
        typedef __HTIterator<K, T, Hash, KeyOfT> Self;
        typedef HashTable<K, T, Hash, KeyOfT> HT;

        __HTIterator(Node *node, HT *ht)
                : _node(node), _ht(ht) {

        }

        HT *_ht;
        Node *_node;

        T *operator->() {
            return &_node->_Data;
        }

        T &operator*() {
            return _node->_Data;
        }

        bool operator!=(const Self &it) const {
            return _node != it._node;
        }

        bool operator==(const Self &it) const {
            return _node == it._node;
        }

        Self &operator++() {
            if (_node->_next) {
                _node = _node->_next;
            } else {
                size_t index = Hash()(KeyOfT()(_node->_Data)) % _ht->_table.size();
                ++index;
                while (index < _ht->_table.size()) {
                    if (_ht->_table[index]) {
                        _node = _ht->_table[index];
                        break;
                    } else {
                        ++index;
                    }
                }
                if (index == _ht->_table.size()) {
                    _node = nullptr;
                }
            }
            return *this;
        }
    };

    template<class K, class T, class Hash, class KeyOfT>
    class HashTable {
        typedef HashNode<T> Node;

        friend struct __HTIterator<K, T, Hash, KeyOfT>;
    public:
        typedef __HTIterator<K, T, Hash, KeyOfT> iterator;

        iterator begin() {
            for (size_t i = 0; i < _table.size(); ++i) {
                if (_table[i] != nullptr) {
                    return iterator(_table[i], this);
                }
            }
            return iterator(nullptr, this);
        }

        iterator end() {
            return iterator(nullptr, this);
        }

    public:
        HashTable() {
            _table.resize(__stl_next_prime(_n));
        }

        std::pair<iterator, bool> insert(const T &value) {
            iterator it = find(KeyOfT()(value));
            if (it != end()) {
                return std::make_pair(it, false);
            }
            if (_n == _table.size()) {
                std::vector<Node *> newTable;
                newTable.resize(__stl_next_prime(_n));
                for (size_t i = 0; i < _table.size(); ++i) {
                    Node *cur = _table[i];
                    while (cur) {
                        Node *next = cur->_next;
                        size_t index = Hash()(KeyOfT()(cur->_Data)) % newTable.size();
                        cur->_next = newTable[index];
                        newTable[index] = cur;
                        cur = next;
                    }
                    _table[i] = nullptr;
                }
                _table.swap(newTable);
            }
            size_t index = Hash()(KeyOfT()(value)) % _table.size();
            Node *newNode = new Node(value);
            newNode->_next = _table[index];
            _table[index] = newNode;
            ++_n;
            return std::make_pair(iterator(newNode, this), true);
        }

        iterator find(const K &Key) {
            size_t index = Hash()(Key) % _table.size();
            Node *cur = _table[index];
            while (cur != nullptr) {
                if (KeyOfT()(cur->_Data) == Key) {
                    return iterator(cur, this);
                } else {
                    cur = cur->_next;
                }
            }
            return end();
        }

        bool erase(const K &Key) {
            size_t index = Hash()(Key) % _table.size();
            Node *cur = _table[index];
            Node *prev = nullptr;
            while (cur != nullptr) {
                if (KeyOfT()(cur->_Data) == Key) {
                    if (cur == _table[index]) {
                        _table[index] = cur->_next;
                    } else {
                        prev->_next = cur->_next;
                    }
                    delete cur;
                    --_n;
                    return true;
                } else {
                    prev = cur;
                    cur = cur->_next;
                }
            }
            return false;
        }

        inline unsigned long __stl_next_prime(unsigned long n) {
            static const int __stl_num_primes = 28;
            static const unsigned long __stl_prime_list[__stl_num_primes] = {
                    53, 97, 193, 389, 769,
                    1543, 3079, 6151, 12289, 24593,
                    49157, 98317, 196613, 393241, 786433,
                    1572869, 3145739, 6291469, 12582917, 25165843,
                    50331653, 100663319, 201326611, 402653189, 805306457,
                    1610612741, 3221225473, 4294967291
            };
            for (size_t i = 0; i < __stl_num_primes; ++i) {
                if (__stl_prime_list[i] > n) {
                    return __stl_prime_list[i];
                }
            }
            return __stl_prime_list[__stl_num_primes - 1];
        }


    private:
        std::vector<Node *> _table;
        size_t _n = 0;
    };
} //wyp

#endif //UNORDERED_MAP_UNORDERED_SET_HASHTABLE_H

