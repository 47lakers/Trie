//
//  main.cpp
//  Trie
//
//  Created by Ira Xavier Porchia on 6/17/20.
//  Copyright © 2020 Ira Xavier Porchia. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

const int size = 26;

class node{
    friend class Trie;
private:
    node *_arr[size];
    bool _isLeaf;
public:
    node(){
        for(int i = 0; i < size; i++){
            _arr[i] = nullptr;
        }
        _isLeaf = false;
    }
};

class Trie{
private:
    node *_root;
public:
    Trie():
    _root(nullptr){}
    
    ~Trie(){
        delete _root;
        _root = nullptr;
    }
    void insert(string key);
    bool search(string key);
    bool isEmpty(node *root);
    node *remove(string key);
    node *removeUtil(node *root, string key, int depth);
};

void Trie::insert(string key){
    if(_root == nullptr){
        _root = new node();
    }
    node *p = _root;
    for(int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if(p->_arr[index] == nullptr){
            p->_arr[index] = new node();
        }
        p = p->_arr[index];
    }
    p->_isLeaf = true;
}

bool Trie::search(string key){
    if(_root == nullptr){
        cout << key << " is not found" << endl << endl;
        return false;
    }
    node *p = _root;
    for(int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if(p->_arr[index] == nullptr){
            cout << key << " is not found" << endl << endl;
            return false;
        }
        p = p->_arr[index];
    }
    cout << key << " is found" << endl << endl;
    return (p->_isLeaf);
}

node *Trie::remove(string key){
    return removeUtil(_root, key, 0);
}

//Returns true if root has no children, else it returns false
bool Trie::isEmpty(node* root){
    for(int i = 0; i < size; i++){
        if(root->_arr[i] != nullptr){
            return false;
        }
    }
    return true;
}

node* Trie::removeUtil(node *root, string key, int depth){
    //If tree is empty
    if(root == nullptr){
        cout << key << " is not in there" << endl << endl;
        return nullptr;
    }
    //If last character of key is being processed
    if(depth == key.size()){
        //This node is no more end of word after removal of given key
        if(root->_isLeaf){
            root->_isLeaf = false;
        }
        //if given is not prefix of any other word
        if(isEmpty(root)){
            delete root;
            root = nullptr;
        }
        return root;
    }
    //If not last character, recur for the child obtained using ASCII value
    int index = key[depth] - 'a';
    root->_arr[index] = removeUtil(root->_arr[index], key, depth + 1);
    //If root does not have any child, and its the end of another word
    if(isEmpty(root) && root->_isLeaf == false){
        delete root;
        root = nullptr;
    }
    return root;
}

int main(int argc, const char * argv[]) {
    Trie tree;
    tree.insert("hello");
    tree.insert("bye");
    tree.insert("he");
    tree.insert("helle");
    
    tree.search("hello");
    tree.search("bye");
    tree.search("ten");
    
    tree.remove("hello");
    
    tree.search("hello");
    
    tree.search("helle");
    
    cout << 'i' - 'a' << endl << endl;
    
    return 0;
}
