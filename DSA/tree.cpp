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

void BinaryTree::InorderTreeWalk(BinaryTreeNode *node)
{
    if (node != nullptr) {
        InorderTreeWalk(node->left);
        cout<<"   "<<node->key;
        InorderTreeWalk(node->right);
    }
}

BinaryTreeNode *BinaryTree::Search(BinaryTreeNode *node, int kk)
{
    if (node == nullptr) return nullptr;
    if (node->key == kk) return node;
    else if (kk < node->key) {
        return Search(node->left, kk);
    } else {
        return Search(node->right, kk);
    }
}

BinaryTreeNode *BinaryTree::Minimum(BinaryTreeNode *node)
{
    while (node != nullptr)
        node = node->left;
    return node;
}

BinaryTreeNode *BinaryTree::Maximum(BinaryTreeNode *node)
{
    while (node != nullptr) {
        node = node->right;
    }
    return node;
}

void BinaryTree::Insert(BinaryTreeNode *node)
{
    BinaryTreeNode *y= nullptr;
    BinaryTreeNode *x = root_;
    
    while (x != nullptr) {
        y = x;
        if (node->key < x->key) x = x->left;
        else x = x->right;
    }
}


/* /////////////////////////////////////////////////////////////////////////////
 * BinarySearchTree
 */
BinarySearchTree::BinarySearchTree():BinaryTree()
{}
