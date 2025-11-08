#pragma once
#include <vector>
#include <iostream>
using namespace std;

template<typename Data>
class Ntree {
    int n;
    
    struct Node {
        Data data;
        vector<Node*> children;
        int connections;

        Node(Data data_) {
            data = data_;
            connections = 0;
        }
    };

    Node* root;
    //Public Access functions
    void insertHelper(Data data_, Data info, Node* node) {
        Node* myNode = new Node(data_);
        if(root == nullptr) {
            root = myNode;
            cout << "Inserted Root" << endl;
            return;
        }
        if(node->connections >= n) {
            cout << "Node Full" << endl;
            return;
        }
        if(node->data == info) {
            node->children.push_back(myNode);
            node->connections += 1;
            cout << "Inserted" << endl;
            return;
        }
        else {
            cout << "Not inserted" << endl;
            return;
        }
    }

    void deleteHelper(Node* node) {
        if(node != nullptr) {
            for(Node* child : node->children) {
               deleteHelper(child); 
            }
            node = nullptr;
        }
    }

    Node* findNode(Data key, Node* node) {
        Node* myNode;
        if(node == nullptr) {
            return nullptr;
        }
        if(node->data == key) {
            return node;
        }
        else {
            for(Node* child : node->children) {
                myNode = findNode(key, child);
                if (myNode != nullptr) {
                    return myNode;
                }
            }
        }
        return nullptr;
    }

    public:
    Ntree(int data) {
        n = data;
        root = nullptr;
    }

    void insertUnder(Data data_, Data info = "N/A") {
        insertHelper(data_, info, root);
    }

    bool exists(Data data) {
        Node* myNode = findNode(data, root);
        if(myNode == nullptr) {
            cout << "Node Not found" << endl;
            return false;
        }
        else {
            return true;
        }
    }

    vector<Data> findChildren(Data data) {
        Node* myNode = findNode(data, root);
        vector<Data> myData;
        if(myNode == nullptr) {
            cout << "Node Not Found" << endl;
            return {};
        }
        for(Node* child : myNode->children) {
            myData.push_back(child->data);
        } 
        if(myData == vector<Data> {}) {
            cout << "No Children" << endl;
        }
        return myData;
    }
};
