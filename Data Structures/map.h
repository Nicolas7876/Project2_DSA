#pragma once
#include "RBTree.h"
using namespace std;

template<typename Value>
class Map {
    RedBlackTree<Value> tree;
    Value garbage;

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

    Value find(string key) {
        if(tree.findNode(key) == nullptr) {
            cout << "Node not found" << endl;
            return garbage;
        }
        else {
            return tree.findNode(key)->value;
        }
    }

    vector<Value> createList() {
        vector<Value> myVector;
        tree.iterate(myVector, tree.root);
        return myVector;
    }
};