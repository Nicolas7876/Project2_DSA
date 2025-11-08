#pragma once
#include "RBTree.h"
using namespace std;

template<typename Value>
class Map {
    RedBlackTree<Value> tree;

    public:
    Map() {}
    
    ~Map() {
        tree.deleteTree();
    }

    void insert(string key, Value value) {
        tree.insert(key, value);
    }

    void removeKey(string key) {
        tree.remove(key);
    }

    bool empty() {
        return tree.isEmpty();
    }

    string at(string key) {
        if(tree.findNode(key) == nullptr) {
            return "NULL";
        }
        else {
            return tree.findNode(key)->value;
        }
    }
};