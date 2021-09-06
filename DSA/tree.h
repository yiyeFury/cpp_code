//
// Created by xie on 2021/7/31.
//

#ifndef CPP_CODE_TREE_H
#define CPP_CODE_TREE_H


typedef struct BinaryTreeNode {
    BinaryTreeNode *left = nullptr;
    BinaryTreeNode *right = nullptr;
    BinaryTreeNode *parent = nullptr;
    int key;
    int data;
}BinaryTreeNode;


class BinaryTree
{
public:
    BinaryTreeNode *root_ = nullptr;
    int size_;
    int capacity_;
public:
    BinaryTree();
    ~BinaryTree();

public:
    bool Empty();
    
};


class BinarySearchTree: public BinaryTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();
public:
    void InorderTreeWalk(BinaryTreeNode *node);
    BinaryTreeNode* Search(BinaryTreeNode *node, int kk);
    BinaryTreeNode *Minimum(BinaryTreeNode *node);
    BinaryTreeNode *Maximum(BinaryTreeNode *node);
    BinaryTreeNode *Successor(BinaryTreeNode *node);
    
    void Insert(BinaryTreeNode *node);
    
    void Transplant(BinaryTreeNode *u, BinaryTreeNode *v);
    void Delete(BinaryTreeNode *node);
};


#endif //CPP_CODE_TREE_H
