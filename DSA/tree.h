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
    void InorderTreeWalk(BinaryTreeNode *node);
    BinaryTreeNode* Search(BinaryTreeNode *node, int kk);
    BinaryTreeNode *Minimum(BinaryTreeNode *node);
    BinaryTreeNode *Maximum(BinaryTreeNode *node);
    void Insert(BinaryTreeNode *node);
};


#endif //CPP_CODE_TREE_H
