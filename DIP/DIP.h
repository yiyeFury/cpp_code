//
// Created by xie on 2021/6/16.
//

#ifndef CPP_CODE_DIP_H
#define CPP_CODE_DIP_H



#include <string>
#include <vector>

template<typename T1, int M, int N>
void ValueFilled(T1 (&src)[M][N], const T1 fill_value)
{
    for (int ii=0;ii < M;ii++) {
        for (int jj=0;jj<N;jj++) {
            src[ii][jj] = fill_value;
        }
    }
}


template<typename T1, int M, int N>
void CalculateOriginIndex(int (&row_index)[M][N], int (&column_index)[M][N], int origin_row, int origin_col)
{
    // 计算 各点 相对于原点的下标值
    int tmp_val;
    // 各点 行下标
    for (int ii=0;ii<M;ii++) {
        tmp_val = ii - origin_row;
        for (int jj=0;jj<N;jj++) {
            row_index[ii][jj] = tmp_val;
        }
    }

    // 各点 列下标
    for (int jj=0;jj<N;jj++) {
        tmp_val = jj - origin_col;
        for (int ii=0;ii<M;ii++) {
            column_index[ii][jj] =tmp_val;
        }
    }
}

template<typename T1, int src_rows, int src_cols, int dst_rows, int dst_cols>
void pad_image(T1 (&src)[src_rows][src_cols], T1 (&dst)[dst_rows][dst_cols],
               int top_row_add, int bottom_row_add,
               int left_column_add, int right_column_add,
               string method="zero")
{
    bool row_bool, column_bool;
    row_bool = dst_rows==src_rows+top_row_add+bottom_row_add;
    column_bool = dst_cols==src_cols+left_column_add+right_column_add;
    if (row_bool || column_bool) {
        string s="error number in row or column";
        cout<<s<<endl;
    }

    if (method == "zero") {
        T1 fill_value = T1(0);

        // top row
        for (int ii=0;ii < top_row_add;ii++)
            for (int jj=0;jj<dst_cols;jj++)
                dst[ii][jj] = fill_value;

        // bottom row
        for (int ii=src_rows+top_row_add;ii<dst_rows;ii++)
            for (int jj=0;jj<dst_cols;jj++)
                dst[ii][jj] = fill_value;

        // left column
        for (int ii=top_row_add;ii<top_row_add+src_rows;ii++)
            for (int jj=0;jj<left_column_add;jj++)
                dst[ii][jj] = fill_value;

        // right column
        for (int ii=top_row_add;ii<top_row_add+src_rows;ii++)
            for (int jj=left_column_add+src_cols;jj<dst_cols;jj++)
                dst[ii][jj] = fill_value;
    }else if (false) {
        cout<<"continue"<<endl;
    } else if (false) {
        cout<<"continue"<<endl;
    }

    // 复制原始数组
    for (int ii=0;ii<src_rows;ii++) {
        for (int jj=0;jj<src_cols;jj++) {
            dst[top_row_add+ii][left_column_add+jj] = src[ii][jj];
        }
    }
}

// Morphological Image Processing
template<typename T1, int M, int N>
void Reflection(const T1 (&src_se)[M][N], T1 (&dst_se)[M][N], int row, int col)
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

template<typename T1, typename T2, int rows, int columns, int se_rows, int se_columns>
void erosion(const T1 (&src)[rows][columns], T1 (&dst)[rows][columns],
             const T1 foreground_value, const T1 background_value,
             const T2 (&se)[se_rows][se_columns],
             const int se_origin_row, const int se_origin_column,
             const T2 se_foreground_value)
{
    // se: struct element
    // 行列填充
    int top_row_add, bottom_row_add, left_column_add, right_column_add;
    top_row_add = se_origin_row;
    bottom_row_add = se_rows - 1 - se_origin_row;
    left_column_add = se_origin_column;
    right_column_add = se_columns - se_origin_column;

    const int new_rows = rows + se_rows - 1;
    const int new_cols = columns + se_columns - 1;
    T1 src_copy[new_rows][new_cols];

    pad_image(src, src_copy,
              top_row_add, bottom_row_add,
              left_column_add, right_column_add,
              "zero");

    // 将struct element 中的各点位置，转换为以 指定点为中心
//    int se_origin_row_index[se_rows][se_columns], se_origin_column_index[se_rows][se_columns];
//    CalculateOriginIndex(se_origin_row_index, se_origin_column_index, se_origin_row, se_origin_column);

    // 提取 struct element 中的前景 元素下标
    vector<int> se_row_index, se_column_index;
    for (int ii=0;ii<se_rows;ii++) {
        for (int jj=0;jj<se_columns;jj++) {
            if (se[ii][jj] == se_foreground_value) {
                se_row_index.push_back(ii - se_origin_row);  // 将 各点位置 归化到 原点相对位置
                se_column_index.push_back(jj - se_origin_column);
            }
        }
    }

    // erosion
    bool flag;
    int tmp_row_index, tmp_column_index;
    for (int ii=top_row_add;ii<rows+top_row_add;ii++) {
        for (int jj=left_column_add;jj<columns+left_column_add;jj++) {
            flag = true;
            for (int kk=0;kk<se_row_index.size();kk++) {
                tmp_row_index = se_row_index[kk] + ii;
                tmp_column_index = se_column_index[kk] + jj;
                if (src_copy[tmp_row_index][tmp_column_index] != foreground_value) {
                    flag = false;
                    break;
                }
            }
            // 计算返回结果
            dst[ii-top_row_add][jj-left_column_add] = flag?foreground_value:background_value;
        }
    }
}

#endif //CPP_CODE_DIP_H