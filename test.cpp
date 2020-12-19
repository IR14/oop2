#include "test.h"

#include <string>
#include <cassert>
#include <iostream>

using namespace std;

void Test() {
    hashmap<string> def;

    assert(def.empty());

    string token1("abc"), token2("bca"), token3("aa");
    def << token1;

    assert(def.size() == 1);

    def << token1 << token1;

    assert(def[token1] == 3);

    for (unsigned i = 0; i < 5; ++i) {
        def << token2 << token2;
        def << token3;
    }

    assert(def.size() == 3);
    assert(def.has(token2));

    def.erase(token1);

    assert(def.size() == 2);
    assert(!def.has(token1));

    def.erase("a");
    assert(def.size() == 2);

    auto copy = def;

    assert(copy == def);

    copy << token2;

    assert(copy != def);

    copy.clear();
    hashmap<string> empty;

    assert(copy == empty);

    def.print("file1.txt");
    copy.read("file1.txt");

    assert(def == copy);
    assert(def.min() == token3);
    assert(def.max() == token2);

    cerr << "Test passed.";
}
