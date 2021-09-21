//
// Created by xie on 2021/8/22.
//

#include <iostream>
#include "tree.h"
using namespace std;

/* /////////////////////////////////////////////////////////////////////////////
 * test
 */
//
int main()
{
    // BinarySearchTree<int> bst1;
    // BTNode<int> n1,n2, n3, n4, n5;
    // n1.key_ = 10;
    // n2.key_ = 1;
    // n3.key_ = 5;
    // n4.key_ = 2;
    // n5.key_ = 3;
    //
    // bst1.Insert(&n1);
    // bst1.Insert(&n2);
    // bst1.Insert(&n3);
    // bst1.Insert(&n4);
    // bst1.Insert(&n5);
    //
    // bst1.Delete(&n3);
    // bst1.InorderTreeWalk(bst1.root_);

    RedBlackTreeNode<int> *rbt_p1, *rbt_p2, rbt1, rbt2;
    rbt1.color_ = 'r';
    rbt1.key_ = 22;
    rbt_p1 = &rbt1;
    rbt_p2 = &rbt2;
    
    rbt_p2->parent_ = rbt_p1;
    
    cout<<rbt_p2->parent_->color_<<endl;
    cout<<rbt_p2->parent_->key_<<endl;

}
