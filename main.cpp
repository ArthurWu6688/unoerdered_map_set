#include "unordered_set.h"
#include "unordered_map.h"
#include "bitset.h"

void test_unordered_set() {
    wyp::unordered_set<int> us;
    us.insert(13);
    us.insert(3);
    us.insert(23);
    us.insert(5);
    us.insert(5);
    us.insert(6);
    us.insert(15);
    us.insert(223342);
    us.insert(22);

    wyp::unordered_set<int>::iterator it = us.begin();
    while (it != us.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    for (auto e: us) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

void test_unordered_map() {
    wyp::unordered_map<std::string, int> m;
    std::string arr[] = {"Æ»¹û", "Î÷¹Ï", "Ïã½¶", "²İİ®",
                         "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Æ»¹û",
                         "Î÷¹Ï", "Æ»¹û", "Ïã½¶", "Æ»¹û",
                         "Ïã½¶"};
    for (auto &e: arr) {
        m[e]++;
    }

//    for (auto e: m) {
//        std::cout << e.first << ":" << e.second << " ";
//    }
//    std::cout << std::endl;

    wyp::unordered_map<std::string, int>::iterator it = m.begin();
    while (it != m.end()) {
        std::cout << (*it).first << ":" << (*it).second << " ";
        ++it;
    }
    std::cout << std::endl;
}

void test_bitset() {
    wyp::bitset<0xffffffff> bs;
    bs.set(10);
    bs.set(20);
    bs.set(3000);
    std::cout << bs.test(10) << std::endl;
    std::cout << bs.test(20) << std::endl;
    std::cout << bs.test(3000) << std::endl;
    std::cout << bs.test(666) << std::endl;
    std::cout << bs.test(777) << std::endl;
    bs.reset(20);
    bs.set(666);
    std::cout << bs.test(10) << std::endl;
    std::cout << bs.test(20) << std::endl;
    std::cout << bs.test(3000) << std::endl;
    std::cout << bs.test(666) << std::endl;
    std::cout << bs.test(777) << std::endl;
}

int main() {
    test_unordered_set();
    test_unordered_map();
    test_bitset();

    return 0;
}
