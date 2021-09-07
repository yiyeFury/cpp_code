//
// Created by xie on 2021/7/31.
//

#ifndef CPP_CODE_TREE_H
#define CPP_CODE_TREE_H

using namespace std;

template<typename T1, typename T2>
struct BinaryTreeNode {
    BinaryTreeNode *left = nullptr;
    BinaryTreeNode *right = nullptr;
    BinaryTreeNode *parent = nullptr;
    T1 key;
    T2 data;
};

typedef BinaryTreeNode<int, int> BTNodeInt;
template<typename T1, typename T2> using BTNode = BinaryTreeNode<T1, T2>;

template<typename T1, typename T2>
class BinaryTree
{
public:
    BinaryTreeNode<T1, T2> *root_ = nullptr;
    int size_;
    int capacity_;
public:
    BinaryTree();
    ~BinaryTree();

public:
    bool Empty();
    
};


template<typename T1, typename T2>
class BinarySearchTree: public BinaryTree<T1, T2>
{
public:
    BinarySearchTree();
    ~BinarySearchTree();
public:
    void InorderTreeWalk(BinaryTreeNode<T1, T2> *node);
    BinaryTreeNode<T1, T2> *Search(BinaryTreeNode<T1, T2> *node, int kk);
    BinaryTreeNode<T1, T2> *Minimum(BinaryTreeNode<T1, T2> *node);
    BinaryTreeNode<T1, T2> *Maximum(BinaryTreeNode<T1, T2> *node);
    BinaryTreeNode<T1, T2> *Successor(BinaryTreeNode<T1, T2> *node);
    
    void Insert(BinaryTreeNode<T1, T2> *node);
    
    void Transplant(BinaryTreeNode<T1, T2> *u, BinaryTreeNode<T1, T2> *v);
    void Delete(BinaryTreeNode<T1, T2> *node);
};

/* /////////////////////////////////////////////////////////////////////////////
 * BinaryTree
 */

template<typename T1, typename T2>
BinaryTree<T1, T2>::BinaryTree():size_(0) {}

template<typename T1, typename T2>
BinaryTree<T1, T2>::~BinaryTree() {}

template<typename T1, typename T2>
bool BinaryTree<T1, T2>::Empty()
{
    return root_ == nullptr;
}


/* /////////////////////////////////////////////////////////////////////////////
 * BinarySearchTree
 */

template<typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree():BinaryTree<T1, T2>::BinaryTree()
{}

template<typename T1, typename T2>
BinarySearchTree<T1, T2>::~BinarySearchTree() {}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::InorderTreeWalk(BinaryTreeNode<T1, T2> *node)
{
    if (node != nullptr) {
        InorderTreeWalk(node->left);
        cout<<"   "<<node->key;
        InorderTreeWalk(node->right);
    }
}

template<typename T1, typename T2>
BinaryTreeNode<T1, T2> *BinarySearchTree<T1, T2>::Search(BinaryTreeNode<T1, T2> *node, int kk)
{
    if (node == nullptr) return nullptr;
    if (node->key == kk) return node;
    else if (kk < node->key) {
        return Search(node->left, kk);
    } else {
        return Search(node->right, kk);
    }
}

template<typename T1, typename T2>
BinaryTreeNode<T1, T2> *BinarySearchTree<T1, T2>::Minimum(BinaryTreeNode<T1, T2> *node)
{
    while (node != nullptr)
        node = node->left;
    return node;
}

template<typename T1, typename T2>
BinaryTreeNode<T1, T2> *BinarySearchTree<T1, T2>::Maximum(BinaryTreeNode<T1, T2> *node)
{
    while (node != nullptr) {
        node = node->right;
    }
    return node;
}

template<typename T1, typename T2>
BinaryTreeNode<T1, T2> *BinarySearchTree<T1, T2>::Successor(BinaryTreeNode<T1, T2> *node)
{
    BinaryTreeNode<T1, T2> *x = node;
    if (x->right != nullptr) {
        return x->right;
    }
    
    BinaryTreeNode<T1, T2> *y=node->parent;
    
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::Insert(BinaryTreeNode<T1, T2> *node)
{
    BinaryTreeNode<T1, T2> *y= nullptr;
    BinaryTreeNode<T1, T2> *x = BinaryTree<T1, T2>::root_;
    
    while (x != nullptr) {  // x==nullptr 时停止
        y = x;  // 此处 y 记录 x 的父节点
        if (node->key < x->key) x = x->left;
        else x = x->right;
    }
    
    node->parent = y;  // node 作为 y 的子节点
    if (y== nullptr) {
        BinaryTree<T1, T2>::root_ = node;
    } else if (node->key < y->key) {
        y->left = node;
    } else y->right = node;
    
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::Transplant(BinaryTreeNode<T1, T2> *u, BinaryTreeNode<T1, T2> *v)
{
    /*
     * replaces one subtree as a child of its parent with another subtree
     */
    if (u->parent == nullptr) {
        BinaryTree<T1, T2>::root_ = v;
    } else if (u == u->parent->left) {  // 左子树
        u->parent->left = v;
    } else u->parent->right = v;  // 右子树
    
    if (v != nullptr) v->parent = u->parent;
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::Delete(BinaryTreeNode<T1, T2> *node)
{
    if (node->left == nullptr) {
        Transplant(node, node->right);
    } else if (node->right == nullptr) {
        Transplant(node, node->left);
    } else {
        BinaryTreeNode<T1, T2> *y = Minimum(node->right);
        if (y->parent != node) {
            Transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        Transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
    }
}

#endif //CPP_CODE_TREE_H
