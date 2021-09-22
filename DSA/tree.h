//
// Created by xie on 2021/7/31.
//

#ifndef CPP_CODE_TREE_H
#define CPP_CODE_TREE_H

using namespace std;

template<typename T>
struct BinaryTreeNode {
    BinaryTreeNode *left_ = nullptr;
    BinaryTreeNode *right_ = nullptr;
    BinaryTreeNode *parent_ = nullptr;
    T key_;
};

typedef BinaryTreeNode<int> BTNodeInt;
template<typename T1> using BTNode = BinaryTreeNode<T1>;


template<typename T>
struct RedBlackTreeNode: BinaryTreeNode<T>
{
    char color_ = 'b';  // r for red and b for black
    RedBlackTreeNode *left_ = nullptr;
    RedBlackTreeNode *right_ = nullptr;
    RedBlackTreeNode *parent_ = nullptr;
    
};

template<typename T>
class BinaryTree
{
public:
    BinaryTreeNode<T> *root_ = nullptr;
    int size_;
    int capacity_;
public:
    BinaryTree();
    ~BinaryTree();

public:
    bool Empty();
    
};


template<typename T>
class BinarySearchTree: public BinaryTree<T>
{
public:
    BinarySearchTree();
    ~BinarySearchTree();
public:
    void InorderTreeWalk(BinaryTreeNode<T> *node);
    BinaryTreeNode<T> *Search(BinaryTreeNode<T> *node, int kk);
    BinaryTreeNode<T> *Minimum(BinaryTreeNode<T> *node);
    BinaryTreeNode<T> *Maximum(BinaryTreeNode<T> *node);
    BinaryTreeNode<T> *Successor(BinaryTreeNode<T> *node);
    
    void Insert(BinaryTreeNode<T> *node);
    
    void Transplant(BinaryTreeNode<T> *u, BinaryTreeNode<T> *v);
    void Delete(BinaryTreeNode<T> *node);
};

template<typename T>
class RedBlackTree
{
public:
    RedBlackTreeNode<T> *root_;
    RedBlackTreeNode<T> *sentinel_;

public:
    RedBlackTree(BinaryTreeNode<T> *node);
    ~RedBlackTree();

public:
    void LeftRotate(RedBlackTreeNode<T> *node);
    void RightRotate(RedBlackTreeNode<T> *node);
    
    void InsertFixup(RedBlackTreeNode<T> *node);
    void Insert(RedBlackTreeNode<T> *node);
};

/* /////////////////////////////////////////////////////////////////////////////
 * BinaryTree
 */

template<typename T>
BinaryTree<T>::BinaryTree():size_(0) {}

template<typename T>
BinaryTree<T>::~BinaryTree() {}

template<typename T>
bool BinaryTree<T>::Empty()
{
    return root_ == nullptr;
}


/* /////////////////////////////////////////////////////////////////////////////
 * BinarySearchTree
 */

template<typename T>
BinarySearchTree<T>::BinarySearchTree():BinaryTree<T>::BinaryTree()
{}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {}

template<typename T>
void BinarySearchTree<T>::InorderTreeWalk(BinaryTreeNode<T> *node)
{
    if (node != nullptr) {
        InorderTreeWalk(node->left_);
        cout<<"   "<<node->key_;
        InorderTreeWalk(node->right_);
    }
}

template<typename T>
BinaryTreeNode<T> *BinarySearchTree<T>::Search(BinaryTreeNode<T> *node, int kk)
{
    if (node == nullptr) return nullptr;
    if (node->key_ == kk) return node;
    else if (kk < node->key_) {
        return Search(node->left_, kk);
    } else {
        return Search(node->right_, kk);
    }
}

template<typename T>
BinaryTreeNode<T> *BinarySearchTree<T>::Minimum(BinaryTreeNode<T> *node)
{
    while (node != nullptr)
        node = node->left_;
    return node;
}

template<typename T>
BinaryTreeNode<T> *BinarySearchTree<T>::Maximum(BinaryTreeNode<T> *node)
{
    while (node != nullptr) {
        node = node->right_;
    }
    return node;
}

template<typename T>
BinaryTreeNode<T> *BinarySearchTree<T>::Successor(BinaryTreeNode<T> *node)
{
    BinaryTreeNode<T> *x = node;
    if (x->right_ != nullptr) {
        return x->right_;
    }
    
    BinaryTreeNode<T> *y=node->parent_;
    
    while (y != nullptr && x == y->right_) {
        x = y;
        y = y->parent_;
    }
    return y;
}

template<typename T>
void BinarySearchTree<T>::Insert(BinaryTreeNode<T> *node)
{
    BinaryTreeNode<T> *y= nullptr;
    BinaryTreeNode<T> *x = BinaryTree<T>::root_;
    
    while (x != nullptr) {  // x==nullptr 时停止
        y = x;  // 此处 y 记录 x 的父节点
        if (node->key_ < x->key_) x = x->left_;
        else x = x->right_;
    }
    
    node->parent_ = y;  // node 作为 y 的子节点
    if (y== nullptr) {
        BinaryTree<T>::root_ = node;
    } else if (node->key_ < y->key_) {
        y->left_ = node;
    } else y->right_ = node;
    
}

template<typename T>
void BinarySearchTree<T>::Transplant(BinaryTreeNode<T> *u, BinaryTreeNode<T> *v)
{
    /*
     * replaces one subtree as a child of its parent_ with another subtree
     */
    if (u->parent_ == nullptr) {
        BinaryTree<T>::root_ = v;
    } else if (u == u->parent_->left_) {  // 左子树
        u->parent_->left_ = v;
    } else u->parent_->right_ = v;  // 右子树
    
    if (v != nullptr) v->parent_ = u->parent_;
}

template<typename T>
void BinarySearchTree<T>::Delete(BinaryTreeNode<T> *node)
{
    if (node->left_ == nullptr) {
        Transplant(node, node->right_);
    } else if (node->right_ == nullptr) {
        Transplant(node, node->left_);
    } else {
        BinaryTreeNode<T> *y = Minimum(node->right_);
        if (y->parent_ != node) {
            Transplant(y, y->right_);
            y->right_ = node->right_;
            y->right_->parent_ = y;
        }
        Transplant(node, y);
        y->left_ = node->left_;
        y->left_->parent_ = y;
    }
}

/* /////////////////////////////////////////////////////////////////////////////
 * RedBlackTree
 */
template<typename T>
RedBlackTree<T>::RedBlackTree(BinaryTreeNode<T> *node): sentinel_(node) {}

template<typename T>
RedBlackTree<T>::~RedBlackTree() {}

template<typename T>
void RedBlackTree<T>::LeftRotate(RedBlackTreeNode<T> *node)
{
    RedBlackTreeNode<T> *y = node->right_;  // set y
    node->right_ = y->left_;  // turn y's left subtree into x's right subtree
    
    if (y->left_ != sentinel_) {
        y->left_->parent_ = node;
    }
    
    y->parent_ = node->parent_;  // link x's parent to y
    if (node->parent_ == sentinel_) {
        root_ = y;
    } else if (node == node->parent_->left_) {
        node->parent_->left_ = y;
    } else node->parent_->right_ = y;
    
    y->left_ = node;  // put node on y's left
    node->parent_ = y;
}

template<typename T>
void RedBlackTree<T>::RightRotate(RedBlackTreeNode<T> *node)
{
    RedBlackTreeNode<T> x = node->left_;  // set x
    node->left_ = x.right_;
    x.parent_ = node->parent_;
    
    if (node->parent_ == sentinel_) {
        root_ = x;
    } else if (node == node->parent_->left_) {
        node->parent_->left_ = x;
    } else node->parent_->right_ = x;
    
    x.left_ = node;
    node->parent_ = x;
    
}

template<typename T>
void RedBlackTree<T>::InsertFixup(RedBlackTreeNode<T> *node)
{
    RedBlackTreeNode<T> *y;
    while (node->parent_->color_ == 'r') {
        if (node->parent_ == node->parent_->parent_->left_) {
            y = node->parent_->parent_->right_;
            if (y->color_ == 'r') {
                node->parent_->color_ = 'b';
                y->color_ = 'b';
                node->parent_->parent_->color_ = 'r';
                node = node->parent_->parent_;
            } else {
                if (node == node->parent_->right_) {
                    node = node->parent_;
                    LeftRotate(node);
                }
                node->parent_.color_ = 'b';
                node->parent_->parent_.color_ = 'r';
                RightRotate(node->parent_->parent_);
            }
        } else {
            // todo:
            y = node->parent_->parent_->left_;
            if (y->color_ == 'r') {
                node->parent_->color_ = 'b';
                y->color_ = 'b';
                node->parent_->parent_->color_ = 'r';
                node = node->parent_->parent_;
            } else {
                if (node == node->parent_->right_) {
                    node = node->parent_;
                    LeftRotate(node);
                }
                node->parent_.color_ = 'b';
                node->parent_->parent_.color_ = 'r';
                RightRotate(node);
            }
        }
    
    }
}

template<typename T>
void RedBlackTree<T>::Insert(RedBlackTreeNode<T> *node)
{
    RedBlackTreeNode<T> *y = sentinel_, *x = root_;
    
    // 寻找 待插入点的父结点
    while (x != sentinel_) {
        y = x;
        if (node->key_ < x->key_) x = x->left_;
        else x = x->right_;
    }
    node->parent_ = y;
    
    if (y == sentinel_) root_ = node;
    else if (node->key_ < y->key_) y->left_ = node;
    else y->right_ = node;
    
    node->left_ = sentinel_;
    node->right_ = sentinel_;
    node->color_ = 'r';
    
    InsertFixup(node);
}

#endif //CPP_CODE_TREE_H
