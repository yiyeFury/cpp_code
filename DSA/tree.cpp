//
// Created by xie on 2021/8/22.
//

#include <iostream>
#include "tree.h"
using namespace std;

/* /////////////////////////////////////////////////////////////////////////////
 * test
 */

int main()
{
    BinarySearchTree<int, int> bst1;
    BTNode<int, int> n1,n2, n3, n4, n5;
    n1.key = 10;
    n2.key = 1;
    n3.key = 5;
    n4.key = 2;
    n5.key = 3;

    bst1.Insert(&n1);
    bst1.Insert(&n2);
    bst1.Insert(&n3);
    bst1.Insert(&n4);
    bst1.Insert(&n5);

    bst1.Delete(&n3);
    bst1.InorderTreeWalk(bst1.root_);
}
