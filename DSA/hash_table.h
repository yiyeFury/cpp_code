//
// Created by xie on 2021/7/26.
//

#ifndef CPP_CODE_HASH_TABLE_H
#define CPP_CODE_HASH_TABLE_H


typedef  struct {
    int key;
    char value;
}Node;

class DirectAddressTable
{
public:
    const int kTableSize_;
    Node *node_[10];
public:
    DirectAddressTable();
    DirectAddressTable(int len);
    ~DirectAddressTable();

public:
    Node *Search();
    void Insert(Node *n);
    void Delete(Node n);
    
};


#endif //CPP_CODE_HASH_TABLE_H
