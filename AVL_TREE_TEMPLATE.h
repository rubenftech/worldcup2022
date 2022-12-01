//
// Created by Ruben on 30/11/2022.
//

#ifndef MIVNEWET1_AVL_H
#define MIVNEWET1_AVL_H

#include <iostream>
using namespace std;


template<class T, class S>
class AVL{
    private:
        class Node{
            T key;
            S data;
            Node* left, right;
        };
        Node* root;
        int size;

    public:
    AVL(): root(NULL), size(0){}

    ~AVL(){
        clear();
    }


    void insert(T key, S data){
        root = insertFunc(root, key, data);
        size++;
    }

    Node* insertFunc(Node* node, T key,S data)
    {
        if (node == nullptr) {
            node = new Node;
            node->key = key;
            node->data = data;
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }
        else if (key < node->key)
        {
            node->left = insertFunc(node->left, key,data);
            node = balance(node);
        } else if (node->key <= key) {
            node->right = insertFunc(node->right, key, data);
            node = balance(node);
        } return node;
    }


    Node* find(T key)
    {
        return findFunc(root,key);
    }

    Node* findFunc(Node* node,T &key) const
    {
        if (node == nullptr){
            return nullptr;
        }
        if(node->key == key){
            return node;
        }
        else if (node->key < key){
            return findFunc(node->right, key);
        }
        else {
            return findFunc(node->left,key);
        }
    }


    void remove (T key){
        root = removeFunc(root, key);
        size--;
    }

    Node* removeFunc(Node* node, T key){
        Node* tmp;

        if (node == nullptr){ //not found
            return nullptr;
        }
        else if (key < node->key){
            node->left = removeFunc(node->left, key);
        }

        else if (node->key < key){
            node->right = removeFunc(node->right, key);
        }

        else if (node->left && node->right) {      // if element has two children
            tmp = findMin(node->right);
            node->key = tmp->key;
            node->data=tmp->data;
            node->right = removeFunc(node->right, node->key);
        }

        else {                                  // if element has 0/1 child
            tmp = node;
            if (node->left == nullptr){
                node = node->right;
            }
            else if (node->right == nullptr){
                node = node->left;
            }
            delete tmp;
        }
        if (node == nullptr) return node;

        node = balance(node); // We now have to balance the tree
        return node;
    }



    void clear(){
        clearFunc (root);
        root = NULL;
        size = 0;
    }

    void clearFunc(Node* node) {
        if (node != nullptr) {
            clearFunc(node->left);
            clearFunc(node->right);
            delete node;
        }
    }


    void inorderFunc(Node* node){
        if (node == NULL){
            return;
        }
        inorderFunc(node->left);
        cout << node->data << "  ";
        inorderFunc(node->right);

    }


    T getData(Node* node) const
    {
        return node->data;
    }

    int get_size(){
        return size;
    }

    Node* findMin(Node* node) const{
        if(node == nullptr) {
            return nullptr;
        }
        else if(node->left == nullptr)
            return node;
        else
            return findMin(node->left);
    }


// balancing
    Node* balance (Node* node) {
        int factor = getBalanceFactor(node);
        if (factor > 1) {
            if (getBalanceFactor(node->left) > 0) {
                node = ll_rotation(node);
            }
            else {
                node = lr_rotation(node);
            }
        } else if (factor < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node = rl_rotation(node);
            }
            else {
                node = rr_rotation(node);
            }
        }
        return node;
    }

    int height(Node* node) const{
        int h =0;
        if (node != nullptr){
            int l_height = height(node->left);
            int r_height = height(node->right);
            int max_height = (l_height > r_height) ? l_height : r_height;
            h = max_height + 1;
        }
        return h;
    }

    int getBalanceFactor(Node* node){
        int l_height = height(node->left);
        int r_height = height(node->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }


    Node * rr_rotation(Node* father){
        Node* node;
        node = father->right;
        father->right = node->left;
        node->left = father;
        return node;
    }

    Node * rl_rotation(Node *father){
        Node* node;
        node = father->right;
        father->right = ll_rotate(node);
        return rr_rotation(father);
    }

    Node * lr_rotation(Node* father){
        Node* node;
        node = father->left;
        father->left = rr_rotate(node);
        return ll_rotation(father);
    }

    Node * ll_rotation(Node *parent){
        Node* node;
        node = parent->left;
        parent->left = node->right;
        node->right = parent;
        return node;
    }



};













#endif //MIVNEWET1_AVL_H
