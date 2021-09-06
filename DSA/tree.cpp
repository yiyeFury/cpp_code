//
// Created by xie on 2021/8/22.
//

#include <iostream>
#include "tree.h"
using namespace std;


/* /////////////////////////////////////////////////////////////////////////////
 * BinaryTree
 */


BinaryTree::BinaryTree():size_(0)
{}

bool BinaryTree::Empty()
{
    return root_ == nullptr;
}


/* /////////////////////////////////////////////////////////////////////////////
 * BinarySearchTree
 */
BinarySearchTree::BinarySearchTree():BinaryTree()
{}

void BinarySearchTree::InorderTreeWalk(BinaryTreeNode *node)
{
    if (node != nullptr) {
        InorderTreeWalk(node->left);
        cout<<"   "<<node->key;
        InorderTreeWalk(node->right);
    }
}

BinaryTreeNode *BinarySearchTree::Search(BinaryTreeNode *node, int kk)
{
    if (node == nullptr) return nullptr;
    if (node->key == kk) return node;
    else if (kk < node->key) {
        return Search(node->left, kk);
    } else {
        return Search(node->right, kk);
    }
}

BinaryTreeNode *BinarySearchTree::Minimum(BinaryTreeNode *node)
{
    while (node != nullptr)
        node = node->left;
    return node;
}

BinaryTreeNode *BinarySearchTree::Maximum(BinaryTreeNode *node)
{
    while (node != nullptr) {
        node = node->right;
    }
    return node;
}

BinaryTreeNode *BinarySearchTree::Successor(BinaryTreeNode *node)
{
    BinaryTreeNode *x = node;
    if (x->right != nullptr) {
        return x->right;
    }
    
    BinaryTreeNode *y=node->parent;
    
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}


void BinarySearchTree::Insert(BinaryTreeNode *node)
{
    BinaryTreeNode *y= nullptr;
    BinaryTreeNode *x = root_;
    
    while (x != nullptr) {  // x==nullptr 时停止
        y = x;  // 此处 y 记录 x 的父节点
        if (node->key < x->key) x = x->left;
        else x = x->right;
    }
    
    node->parent = y;
    if (y== nullptr) {
        root_ = node;
    } else if (node->key < y->key) {
        y->left = node;
    } else y->right = node;
    
}

void BinarySearchTree::Transplant(BinaryTreeNode *u, BinaryTreeNode *v)
{
    /*
     * replaces one subtree as a child of its parent with another subtree
     */
    if (u->parent == nullptr) {
        root_ = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else u->parent->right = v;
    
    if (v != nullptr) v->parent = u->parent;
}


void BinarySearchTree::Delete(BinaryTreeNode *node)
{
    if (node->left == nullptr) {
        Transplant(node, node->right);
    } else if (node->right == nullptr) {
        Transplant(node, node->left);
    } else {
        BinaryTreeNode *y = Minimum(node->right);
        if (y->parent != node) {
            Transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        Transplant(node, y);
        y->left = node->left;
        y->left = y;
    }
}
