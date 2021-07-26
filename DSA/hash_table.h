//
// Created by xie on 2021/7/26.
//

#ifndef CPP_CODE_HASH_TABLE_H
#define CPP_CODE_HASH_TABLE_H


struct Node{
    char *key;
    char *value;
};

class HashTable
{
public:
    const int kHashSize_;
    Node *node_[10];
public:
    HashTable();
    HashTable(int len);
    ~HashTable();

public:
    Node Search();
    void Insert();
    void Delete();
    
};


#endif //CPP_CODE_HASH_TABLE_H
