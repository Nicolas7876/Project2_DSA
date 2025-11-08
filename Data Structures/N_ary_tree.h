#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Ntree {
    
    struct Node {
        string key;
        T value;
        vector<Node*> children;

        Node(string key_, T value_) {
            key = key_;
            value = value_;
        }

        Node(string key_) {
            key = key_;
        }
    };

    Node* root;

    void insertHelper(string key, T value, string genre) {
        Node* myNode;
        bool foundGenre = false;
        for(Node* child : root->children) {
            if(child->key == genre) {
                foundGenre = true;
                myNode = child;
            }
        }
        if(foundGenre == false) {
            Node* tempNode1 = new Node(genre, value);
            root->children.push_back(tempNode1);
            cout << "Added " << genre << " genre" << endl;
            Node* tempNode2 = new Node(key, value);
            tempNode1->children.push_back(tempNode2);
            cout << "Added " << key << " to " << genre << " genre" << endl;
            return;
        }
        else {
            Node* tempNode = new Node(key, value);
            myNode->children.push_back(tempNode);
            cout << "Added " << key << " to " << genre << " genre" << endl;
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
    // 
    Node* findNode(string key, string genre, Node* node) {
        Node* myNode;
        bool foundGenre = false;
        for(Node* child : node->children) {
            if (child->key == genre) {
                foundGenre = true;
                myNode = child;
                continue;
            }
        }
        if(!foundGenre) {
            return nullptr;
        }
        for(Node* child : myNode->children) {
            if(child->key == key) {
                return child;
            }
        }
        return nullptr;
    }

    //Public Access functions
    public:
    Ntree() {
        root = new Node("root");
    }

    void insertUnder(string key, T value, string genre) {
        insertHelper(key, value, genre);
    }

    bool exists(string key, string genre) {
        Node* myNode = findNode(key, genre, root);
        if(myNode == nullptr) {
            return false;
        }
        return true;
    }

    vector<string> findChildren(string genre) {
        vector<string> myVector = {};
        for(Node* child : root->children) {
            if(child->key == genre) {
                for(Node* game : child->children) {
                    myVector.push_back(game->key);
                }
            }
        }
        return myVector;
    }
    
    T& findData(string key, string genre) {
        Node* myNode = findNode(key, genre, root);
        if(myNode == nullptr) {
            cout << "Node not found" << endl;
            return root->value;
        }
        return myNode->value;
    }
};
