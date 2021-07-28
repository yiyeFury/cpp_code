//
// Created by admin on 2021/7/23.
//

#include "successive_correction.h"
#include "common.h"

using namespace std;

float WeightFunction(float R, float r)
{
    /*
     * 经验权重函数
     */
    float w;
    double R2 = pow(R, 2);
    double r2 = pow(r, 2);
    
    // w = max(0.0, (R2-r2)/(R2+r2));
    w = (R2-r2)/(R2+r2);
    return w;
}


// int main()
// {
//     // void SuccessiveCorrection(const float (&bkg_data)[M][N], const float (&obs_data)[M][N],
//     //                           float (&dst_data)[M][N],
//     //                           const float (&lats)[M], const float (&lons)[N],
//     //                           const float search_radius, const float fill_value=NAN);
//
//     const int kROW=4, kCOLUMN=5;
//
//     float bkg_data[kROW][kCOLUMN];
//     float obs_data[kROW][kCOLUMN];
//     float dst_data[kROW][kCOLUMN];
//
//     float lats[kROW] = {10.0, 9.0, 8.0, 7.0};
//     float lons[kCOLUMN] = {21.0, 22.0, 23.0, 24.0, 25.0};
//     float search_radius = 200.0;
//     float influence_radius = 500.0;
//
//     float val = 1.0;
//
//     for (int ii=0;ii<kROW;ii++) {
//         for (int jj=0;jj<kCOLUMN;jj++) {
//             bkg_data[ii][jj] = val;
//             obs_data[ii][jj] = val+1.0;
//             dst_data[ii][jj] = 100.0;
//
//         }
//     }
//
//     SuccessiveCorrection(bkg_data, obs_data, dst_data,
//                          lats, lons,
//                          search_radius, influence_radius);
//
//     cout<<"\nbackground data\n";
//     PrintArray(bkg_data);
//
//     cout<<"\n\nobservation data\n";
//     PrintArray(obs_data);
//
//     cout<<"\n\nresult\n";
//     PrintArray(dst_data);
//
//     double d1 = GreatCircleDistance(180.0, 45.0, 181.0, 46.0, 6378.137);
//     cout<<"\ntest: "<<d1<<endl;
//
//     return 0;
// }