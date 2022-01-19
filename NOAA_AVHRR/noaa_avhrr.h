//
// Created by xie on 2022/1/19.
//

#ifndef CPP_CODE_NOAA_AVHRR_H
#define CPP_CODE_NOAA_AVHRR_H

void Bit32Split(long int val, long int (&val_int)[3]);

void EarthDataSplit(int *earth_data, const int num_words,
                    float *channel_data, const int num_obs = 2048, const int num_channel = 5);


#endif //CPP_CODE_NOAA_AVHRR_H
