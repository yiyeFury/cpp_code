//
// Created by xie on 2021/6/16.
//

#ifndef CPP_CODE_DIP_H
#define CPP_CODE_DIP_H

#endif //CPP_CODE_DIP_H


// Morphological Image Processing
template<typename T1, int M, int N>
void reflection(const T1 (&src_se)[M][N], T1 (&dst_se)[M][N], int row, int col)
{
    // 四个角点下标
    int top_row=0, bottom_row = M-1;
    int left_col = 0, right_col = N-1;

    // 计算 下标偏移
    int row_shift, col_shift;
    row_shift = (bottom_row - row)-(row - top_row) + row;
    col_shift = (right_col-col)-(col-left_col) + col;

    int dst_row, dst_col;
    for (int rr=0;rr<M;rr++) {
        for (int cc=0;cc<N;cc++) {
            dst_row = -1*(rr-row) + row_shift;
            dst_col = -1*(cc-col) + col_shift;
            dst_se[dst_row][dst_col] = src_se[rr][cc];
        }
    }

}
