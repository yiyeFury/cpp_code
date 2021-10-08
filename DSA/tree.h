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
class RedBlackTree: public BinarySearchTree<T>
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
    
    void Transplant(RedBlackTreeNode<T> *u, RedBlackTreeNode<T> *v);
    void DeleteFixup(RedBlackTreeNode<T> *x);
    void Delete(RedBlackTreeNode<T> *z);
};

/* /////////////////////////////////////////////////////////////////////////////////////////////////
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


/* /////////////////////////////////////////////////////////////////////////////////////////////////
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

/* /////////////////////////////////////////////////////////////////////////////////////////////////
 * RedBlackTree
 */
template<typename T>
RedBlackTree<T>::RedBlackTree(BinaryTreeNode<T> *node): BinarySearchTree<T>::BinarySearchTree(), sentinel_(node)
{}

template<typename T>
RedBlackTree<T>::~RedBlackTree() {}

template<typename T>
void RedBlackTree<T>::LeftRotate(RedBlackTreeNode<T> *x)
{
    RedBlackTreeNode<T> *y = x->right_;  // set y
    x->right_ = y->left_;  // turn y's left subtree into x's right subtree
    
    if (y->left_ != sentinel_) {
        y->left_->parent_ = x;
    }
    
    y->parent_ = x->parent_;  // link x's parent to y
    if (x->parent_ == sentinel_) {
        root_ = y;
    } else if (x == x->parent_->left_) {
        x->parent_->left_ = y;
    } else x->parent_->right_ = y;
    
    y->left_ = x;  // put node on y's left
    x->parent_ = y;
}

template<typename T>
void RedBlackTree<T>::RightRotate(RedBlackTreeNode<T> *y)
{
    RedBlackTreeNode<T> *x = y->left_;  // set x
    y->left_ = x->right_;
    x->parent_ = y->parent_;
    
    if (y->parent_ == sentinel_) {
        root_ = x;
    } else if (y == y->parent_->left_) {
        y->parent_->left_ = x;
    } else y->parent_->right_ = x;
    
    x->left_ = y;
    y->parent_ = x;
    
}

template<typename T>
void RedBlackTree<T>::InsertFixup(RedBlackTreeNode<T> *node)
{
    RedBlackTreeNode<T> *y;
    while (node->parent_->color_ == 'r') {
        if (node->parent_ == node->parent_->parent_->left_) {
            y = node->parent_->parent_->right_;
            if (y->color_ == 'r') {  // case 1: z's uncle y is red
                node->parent_->color_ = 'b';
                y->color_ = 'b';
                node->parent_->parent_->color_ = 'r';
                node = node->parent_->parent_;
            } else {
                if (node == node->parent_->right_) {
                    // case 2: z's uncle y is black and z is a right child
                    // transform case 2 into case 3
                    node = node->parent_;
                    LeftRotate(node);
                }
                // case 3: z's uncle y is black and z is a left child
                node->parent_.color_ = 'b';
                node->parent_->parent_.color_ = 'r';
                RightRotate(node->parent_->parent_);
            }
        } else {
            //
            // todo:
            y = node->parent_->parent_->left_;
            if (y->color_ == 'r') {
                node->parent_->color_ = 'b';
                y->color_ = 'b';
                node->parent_->parent_->color_ = 'r';
                node = node->parent_->parent_;
            } else {
                if (node == node->parent_->left_) {
                    node = node->parent_;
                    RightRotate(node);
                }
                node->parent_.color_ = 'b';
                node->parent_->parent_.color_ = 'r';
                LeftRotate(node);
            }
        }
    
    }
    root_->color_ = 'b';
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


template<typename T>
void RedBlackTree<T>::Transplant(RedBlackTreeNode<T> *u, RedBlackTreeNode<T> *v)
{
    if (u->parent_ == sentinel_) root_ = v;
    else if (u == u->parent_->left_) u->parent_->left_ = v;
    else u->parent_->right_ = v;
    v->parent_ = u->parent_;
}

template<class T>
void RedBlackTree<T>::DeleteFixup(RedBlackTreeNode<T> *x)
{
    RedBlackTreeNode<T> *w;
    while (x != root_ && x->color_ == 'b') {
        if (x == x->parent_->left_) {
            w = x->parent_->right_;
            if (w->color_ == 'r') {  // case 1
                w->color_ = 'b';
                x->parent_->color_ = 'r';
                LeftRotate(x->parent_);
                w = x->parent_->right_;
            }
            
            if ((w->left_->color_ == 'b') && (w->right_->color_ == 'b')) {  // case 2
                w->color_ = 'r';
                x = x->parent_;
            } else {
                if (w->right_->color_ == 'b') {  // case 3
                    w->left_->color_ = 'b';
                    w->color_ = 'r';
                    RightRotate(w);
                    w = x->parent_->right_;
                }
                
                // case 4
                w->color_ = x->parent_->color_;
                x->parent_->color_ = 'b';
                w->right_->color_ = 'b';
                LeftRotate(x->parent_);
                x = root_;
            }
            
        } else {
            w = x->parent_->left_;
            if (w->color_ == 'r') {  // case 1
                w->color_ = 'b';
                x->parent_->color_ = 'r';
                RightRotate(x->parent_);
                w = x->parent_->left_;
            }
    
            if ((w->right_->color_ == 'b') && (w->left_->color_ == 'b')) {  // case 2
                w->color_ = 'r';
                x = x->parent_;
            } else {
                if (w->left_->color_ == 'b') {  // case 3
                    w->right_->color_ = 'b';
                    w->color_ = 'r';
                    LeftRotate(w);
                    w = x->parent_->left_;
                }
        
                // case 4
                w->color_ = x->parent_->color_;
                x->parent_->color_ = 'b';
                w->left_->color_ = 'b';
                RightRotate(x->parent_);
                x = root_;
            }
        }
    }
    x->color_ = 'b';
    
}

template<typename T>
void RedBlackTree<T>::Delete(RedBlackTreeNode<T> *z)
{
    RedBlackTreeNode<T> *y, *x;
    y = z;
    char y_original_color = y->color_;
    
    if (z->left_ == sentinel_) {
        x = z->right_;
        Transplant(z, z->right_);
    } else if (z->right_ == sentinel_) {
        x = z->left_;
        Transplant(z, z->left_);
    } else {
        y = BinarySearchTree<T>::Minimum(z->right_);
        y_original_color = y->color_;
        x = y->right_;
        
        if (y->parent_ == z) {
            x->parent_ = y;
        } else {
            Transplant(y, y->right_);
            y->right_ = z->right_;
            y->right_->parent_ = y;
        }
        
        Transplant(z, y);
        y->left_ = z->left_;
        y->left_->parent_ = y;
        y->color_ = z->color_;
    }
    
    if (y_original_color == 'b') {
        DeleteFixup(x);
    }
}

#endif //CPP_CODE_TREE_H
