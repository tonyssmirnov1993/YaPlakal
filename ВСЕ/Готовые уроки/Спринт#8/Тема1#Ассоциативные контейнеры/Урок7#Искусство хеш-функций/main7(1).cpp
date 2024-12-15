#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
 
using namespace std;
 
template <typename Hash>
int FindCollisions(const Hash& hasher, istream& text) {
    string str;
    int collisions = 0;
 
    unordered_map<size_t, unordered_set<string>> coll_hash;
 
    while(text >> str) {
        const auto hash_ = hasher(str);
 
        if (const auto helper = coll_hash.find(hash_); 
            helper != coll_hash.end()) {
 
            collisions += helper->second.insert(str).second;
 
        } else {
            coll_hash[hash_].insert(str);
        }
    }
    return collisions;
}
 
// Это плохой хешер. Его можно использовать для тестирования.
// Подумайте, в чём его недостаток
struct HasherDummy {
    size_t operator() (const string& str) const {
        size_t res = 0;
        for (char c : str) {
            res += static_cast<size_t>(c);
        }
        return res;
    }
};
 
struct DummyHash {
    size_t operator()(const string&) const {
        return 42;
    }
};
 
int main() {
    DummyHash dummy_hash;
    hash<string> good_hash;
 
    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(dummy_hash, stream) << endl;
    }
    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(good_hash, stream) << endl;
    }
} 