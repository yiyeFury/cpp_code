//
// Created by xie on 2022/1/19.
//

#include <bitset>
#include "noaa_avhrr.h"

#include <iostream>
using namespace std;

const int bit_size_ch = 10;
const int bit_size_word = 32;

void Bit32Split(long int val, long int (&val_int)[3])
{
    bitset<bit_size_word> bit_val(val);
    bitset<bit_size_ch> tmp_bit;

    // cout<<bit_val<<endl;
    int ii, jj;
    for (ii = 2; ii >= 0; ii--) {
        for (jj = 0; jj < bit_size_ch; jj++) {
            tmp_bit[jj] = bit_val[ii * 10 + jj];
        }
        val_int[2-ii] = tmp_bit.to_ulong();
    }
}

void EarthDataSplit(int *earth_data, const int num_word,
                    float *channel_data, const int num_obs, const int num_channel)
{
    int ii, jj;
    int obs_cnt = 0;
    long int obs_val[3], word_val;
    int ch_obs_idx, ch_idx;

    // words 1 ~ 3413
    for (ii = 0; ii < num_word - 1; ii++) {
        word_val = *(earth_data + ii);
        Bit32Split(word_val, obs_val);

        for (jj = 0; jj < 3; jj++) {
            ch_obs_idx = obs_cnt / num_channel;
            ch_idx = obs_cnt % num_channel;

            *(channel_data + ch_obs_idx * num_channel + ch_idx) = float(obs_val[jj]);
            obs_cnt++;
        }
    }

    // word 3414
    int obs_idx = 2047;
    int word_idx = 3413;
    ch_idx = 4;
    bitset<bit_size_word> bit_val(*(earth_data + word_idx));
    bitset<bit_size_ch> tmp_bit;

    for (ii=0;ii<10;ii++) {
        tmp_bit[ii] = bit_val[ii+20];
    }
    *(channel_data + obs_idx * num_channel + ch_idx) = tmp_bit.to_ulong();

}


// int main()
// {
//
//     // const int num_words = 3414;
//     // const int num_obs=2048;
//     // const int num_channel=5;
//     //
//     // int earth_data[num_words];
//     // int channel_data[num_obs*num_channel];
//     //
//     // int ii, jj;
//     //
//     // for (ii=0;ii<num_words;ii++) {
//     //     earth_data[ii] = ii*10;
//     // }
//     //
//     // earth_data_split(earth_data, num_words,
//     //                  channel_data, 2048, 5);
//     //
//     // for (ii=0;ii<num_obs;ii++) {
//     //     for (jj=0;jj<num_channel;jj++) {
//     //         cout<<"    "<<channel_data[ii * num_channel + jj];
//     //     }
//     //     cout<<endl;
//     // }
//
//     int val = 33333333333;
//
//     long int val_int[3];
//
//     Bit32Split(val, val_int);
//
//     for(int ii=0;ii<3;ii++) {
//         cout<<val_int[ii]<<endl;
//     }
//
//
//     // system("pause");
//     return 0;
// }

