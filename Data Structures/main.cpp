#include "map.h"
#include "N_ary_tree.h"
#include <iostream>

int main() {
    Ntree<string> myTree(1);
    myTree.insertUnder("hello");
    myTree.insertUnder("world", "hello");
    myTree.insertUnder("why", "hello");
    vector<string> myVector = myTree.findChildren("why");
    for(string child : myVector) {
        cout << child << endl;
    }
    cout << myTree.exists("why") << endl;
    return 0;
}