//
// Created by Ruben on 30/11/2022.
//

#ifndef MIVNEWET1_AVL_H
#define MIVNEWET1_AVL_H

#include <iostream>
using namespace std;

template<class T, class S>
class Node{
public:
    T key;
    S data;
    Node* left;
    Node* right;
};

template<class T, class S>
class AVL{
    public:
    Node<T,S>* root;
    int size;


    AVL(): root(NULL), size(0) {} //c'tor

    ~AVL(){ clearTree(); } //d'tor


    void insert(T key, S data){
        root = insertFunc(root, key, data);
        size++;
    } //insert the node in his place in the AVL tree, keeping it balanced

    Node<T,S>* insertFunc(Node<T,S>* node, T key,S data){
        if (node == nullptr) {
            node = new Node<T,S>;
            node->key = key;
            node->data = data;
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }
        else if (key < node->key){
            node->left = insertFunc(node->left, key,data);
            node = balance(node);
        } else if (node->key < key||node->key == key) {
            node->right = insertFunc(node->right, key, data);
            node = balance(node);
        } return node;
    }


    Node<T,S>* find(T key){
        return findFunc(root,key);
    } // Find a node according to his key

    Node<T,S>* findFunc(Node<T,S>* node,T &key) const{
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
    }//recursive helper find function


    void remove (T key){
        root = removeFunc(root, key);
        size--;
    } // remove a node accroding to his key

    Node<T,S>* removeFunc(Node<T,S>* node, T key){
        Node<T,S>* tmp;

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
    } //recursive helper remove function


    void clearTree(){
        clearTreeFunc (root);
        root = NULL;
        size = 0;
    }//remove all nodes without deleting the data

    void clearTreeFunc(Node<T,S>* node) {
        if (node != nullptr) {
            clearTreeFunc(node->left);
            clearTreeFunc(node->right);
            delete node;
        }
    }//recursive helper clear function

    void clearDataAndTree(){
        clearDataAndTreeFunc(root);
        root = nullptr;
        size=0;
    }//remove all nodes deleting the data

    void clearDataAndTreeFunc (Node<T,S>* node){
        if(node != nullptr){
            clearDataAndTreeFunc(node->left);
            clearDataAndTreeFunc(node->right);
            delete node->data;
            delete node;
        }
    }// recursive helper clear tree and data


    void inorderFunc(Node<T,S>* node){
        if (node == NULL){
            return;
        }
        inorderFunc(node->left);
        cout << node->data << "  ";
        inorderFunc(node->right);

    }//print node's data with in-order traversal

    void AVL_to_array_inorder(S *arr, int* i){
        AVL_to_array_inorder_helper(root,arr,i);
    }

    void AVL_to_array_inorder_helper(Node<T,S>* firstNode,S *arr, int* i){
        if(firstNode== nullptr){
            return;
        }
        AVL_to_array_inorder_helper(firstNode->left,arr,i);
        arr[*i]=firstNode->data;
        (*i)++;
        AVL_to_array_inorder_helper(firstNode->right,arr,i);
    }



    void array_to_AVL_inorder(T* arrKey,S *arrData, int i){
        array_to_AVL_inorder_helper(root,arrKey,arrData,i);
    }

    void array_to_AVL_inorder_helper(Node<T,S>* firstNode,T * arrKey,S *arrData, int i){
        if(i==0){
            return;
        }
        firstNode = new Node<T,S>;
        firstNode->key = arrKey[(i+1)/2];
        firstNode->data = arrData[(i+1)/2];
        firstNode->left = nullptr;
        firstNode->right = nullptr;
        array_to_AVL_inorder_helper(firstNode->left,arrKey,arrData,((i+1)/2)-1);
        array_to_AVL_inorder_helper(firstNode->right, arrKey+((i+1)/2), arrData+((i+1)/2), i-((i+1)/2));
    }



    S getData(Node<T,S>* node) const{
        return node->data;
    }

    int get_size(){
        return size;
    }

    Node<T,S>* findMin(Node<T,S>* node) const{
        if(node == nullptr) {
            return nullptr;
        }
        else if(node->left == nullptr){
            return node;
        }
        else{
            return findMin(node->left);
        }
    }

    Node<T,S>* findMax(Node<T,S>* node) const{
        if(node == nullptr) {
            return nullptr;
        }
        else if(node->right == nullptr)
            return node;
        else
            return findMax(node->right);
    }
    
    S dataOfTheMax() const{
        return findMax(root)->data;
    }
/**************************************************************************************/

    
    S getPreviousInorder(T key) const{
//        if(key == nullptr){
//            return nullptr;
//        }
        Node<T,S>* nearestBefore = root;
        Node<T,S>* trackNode = root;
        while(trackNode->key != key){
            if (trackNode->key < key){
                if(trackNode->key > nearestBefore->key){
                    nearestBefore->key = trackNode->key;
                }
                trackNode = trackNode->right;
            }
            else{
                trackNode = trackNode->left;
            }
            if(trackNode == nullptr){
                return nullptr;
            }
        }
        trackNode = trackNode->left;
        while (trackNode->right){
            trackNode = trackNode->right;
        }
        if (nearestBefore->key < trackNode->key){
            return trackNode->data;
        }
        else{
            return nearestBefore->data;
        }
    }

    S getNextInorder(T key)const{
//        if(key == nullptr){
//            return nullptr;
//        }
        Node<T,S>* nearestNext = root;
        Node<T,S>* trackNode = root;
        while(trackNode->key != key){
            if (trackNode->key < key){
                trackNode = trackNode->right;
            }
            else{
                if(trackNode->key < nearestNext->key){
                    nearestNext->key = trackNode->key;
                }
                trackNode = trackNode->left;
            }
            if(trackNode==nullptr){
                return nullptr;
            }
        }
        trackNode = trackNode->right;
        while (trackNode->left){
            trackNode = trackNode->right;
        }
        if (nearestNext->key > trackNode->key){
            return trackNode->data;
        }
        else{
            return nearestNext->data;
        }
    }



/* functions that help to keep the tree balanced */

    Node<T,S>* balance (Node<T,S>* node) {
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

    int height(Node<T,S>* node) const{
        int h =0;
        if (node != nullptr){
            int l_height = height(node->left);
            int r_height = height(node->right);
            int max_height = (l_height > r_height) ? l_height : r_height;
            h = max_height + 1;
        }
        return h;
    }

    int getBalanceFactor(Node<T,S>* node){
        return height(node->left)-height(node->right);
    }


    Node<T,S> * rr_rotation(Node<T,S>* father){
        Node<T,S>* node;
        node = father->right;
        father->right = node->left;
        node->left = father;
        return node;
    }

    Node<T,S> * rl_rotation(Node<T,S> *father){
        Node<T,S>* node;
        node = father->right;
        father->right = ll_rotation(node);
        return rr_rotation(father);
    }

    Node<T,S> * lr_rotation(Node<T,S>* father){
        Node<T,S>* node;
        node = father->left;
        father->left = rr_rotation(node);
        return ll_rotation(father);
    }

    Node<T,S> * ll_rotation(Node<T,S> *parent){
        Node<T,S>* node;
        node = parent->left;
        parent->left = node->right;
        node->right = parent;
        return node;
    }

};



#endif //MIVNEWET1_AVL_H
