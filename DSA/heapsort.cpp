//
// Created by xie on 2021/8/25.
//

#include "heapsort.h"

int Parent(int ii)
{
    // ii >= 1
    int idx_parent(0);  // 树的根节点是A[0]
    if (ii > 0) iParent = (++ii) / 2 - 1;
    return idx_parent;
}

int Left(int ii)
{
    // 计算左子树的下标
    return 2 * ii + 1;
}

int Right(int ii)
{
    // 计算右子树的下标
    return 2 * ii + 2;
}


