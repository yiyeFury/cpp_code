//
// Created by xie on 2021/3/6.
//

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

#include "file_io.h"

using namespace std;


void ReadAhiHsd(string src_file)
{
    ifstream file_input;
    file_input.open(src_file, ios::in | ios::binary);
    if (!file_input) {
        cout << "fail to read file" << endl;
    }


    unsigned short int header_block_number1;
    file_input.read((char *) &header_block_number1, 1);
    cout << "header_block_number1: " << header_block_number1 <<endl;

    unsigned short int block_length1;
    // file_input.seekg(1);
    file_input.read((char *) &block_length1, 2);
    cout << "block_length: " << block_length1 << endl;

    unsigned short int total_number_header_blocks;
    file_input.read((char *) &total_number_header_blocks, 2);
    cout << "total_number_header_blocks: " << total_number_header_blocks <<endl;

    unsigned short int byte_order;
    file_input.read((char *) &byte_order, 1);
    cout << "byte_order: " << byte_order <<endl;

    char satellite_name[16];
    file_input.seekg(6);
    file_input.read((char *) &satellite_name, 16);
    cout << "satellite_name: " << satellite_name <<endl;

    // Processing center name
    char processing_center_name[16];
    file_input.seekg(22);
    file_input.read((char *) &processing_center_name, 16);
    cout << "processing_center_name: " << processing_center_name <<endl;

    // Observation area
    char observation_area[4];
    // file_input.seekg(37);
    file_input.seekg(38);
    file_input.read((char *) &observation_area, 4);
    // string ss = observation_area;
    // cout <<ss<<endl;
    cout << "observation_area: " << observation_area << endl;

    for (auto ii: observation_area) {
        cout << ii;
    }
    cout <<endl;

    // Total header length
    unsigned int total_header_length;
    file_input.seekg(70);
    file_input.read((char *) &total_header_length, 4);

    cout << "total_header_length: " << total_header_length <<endl;

    unsigned int total_data_length;
    file_input.read((char *) &total_data_length, 4);
    cout << "total_data_length: " << total_data_length <<endl;



    file_input.close();

}


void ReadAVHRR(string src_file)
{
    ifstream file_input;
    file_input.open(src_file, ios::in | ios::binary);
    if (!file_input) {
        cout << "fail to read file" << endl;
    }

    char nes_number[6];
    char class_number[8];
    char order_year[4];

    file_input.seekg(0);
    file_input.read((char *) &nes_number, 6);
    cout << nes_number<<endl;

    for (auto ii : nes_number) {
        cout << ii <<endl;
    }

    // file_input.seekg(6);
    // file_input.read((char *) &class_number, 8);
    // cout << class_number<<endl;
    //
    // file_input.seekg(14);
    // file_input.read((char *) &order_year, 4);
    // cout << order_year <<endl;

}

// int main()
// {
//     // NOAA
//     // string src_file="E:\\work\\work_data\\NOAA_AVHRR\\NOAA-19\\NSS.HRPT.NP.D20197.S0014.E0023.B5892929.WI";
//     // ReadAVHRR(src_file);
//
//     // Himawari
//     string src_file = "C:\\Users\\xie\\Desktop\\HS_H08_20200715_0100_B01_FLDK_R10_S0410.DAT";
//     ReadAhiHsd(src_file);
//
//     return 0;
// }


