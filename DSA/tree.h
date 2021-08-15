//
// Created by xie on 2021/7/31.
//

#ifndef CPP_CODE_TREE_H
#define CPP_CODE_TREE_H

typedef struct BinaryTreeNode {
    BinaryNode *left = nullptr;
    BinaryNode *right = nullptr;
    BinaryNode *parent = nullptr;
    int key;
    int data;
}BinaryNode;

class Tree
{
public:
    Node *root_ = nullptr;
    int size_;
    int capacity_;
public:
    Tree();
    ~Tree();
};


#endif //CPP_CODE_TREE_H
