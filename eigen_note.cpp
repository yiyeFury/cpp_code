//
// Created by xie on 2021/8/4.
//

#include <iostream>
#include <Dense>

using namespace std;
using namespace Eigen;

// int main()
// {
//     cout << "\nStart\n\n";
//     int a=3, b=4;
//     Matrix<float, Dynamic, Dynamic> A(a, b);
//
//     int cnt = 0;
//     for (int ii=0;ii<a;ii++) {
//         for (int jj=0;jj<b;jj++) {
//             A(ii, jj) = ++cnt;
//         }
//     }
//
//     cout<<A;
//
//     Matrix<float, Dynamic, Dynamic> m1, m2, m3;
//     m1.setIdentity(3, 3);
//     cout<<m1<<endl;
//
//     m2.setOnes(3, 3);
//     cout<<m2<<endl;
//
//     m3 = m1+m2;
//     cout<<m3<<endl;
//
//
//     cout << "\n\nend\n" << endl;
//     // system("pause");
//     return 0;
// }