#include "unordered_set.h"
#include "unordered_map.h"

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

    for (auto e: m) {
        std::cout << e.first << ":" << e.second << " ";
    }
    std::cout << std::endl;
}

int main() {
    test_unordered_set();
    test_unordered_map();

    return 0;
}
