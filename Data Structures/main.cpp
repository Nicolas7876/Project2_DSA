#include "map.h"
#include "N_ary_tree.h"
#include <iostream>

int main() {
    Ntree<string> myTree;
    myTree.insertUnder("first Node", "world", "action");
    myTree.insertUnder("second Node", "world", "action");
    cout << myTree.exists("third Node", "action") << endl;
    cout << myTree.findData("second Node", "action") << endl;
    Map<string> myMap;
    myMap.insert("hello", "world");
    myMap.find("hello");
    myMap.find("wassup");
    return 0;
}