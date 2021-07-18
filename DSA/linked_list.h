//
// Created by xie on 2021/7/14.
//

#ifndef CPP_CODE_LINKED_LIST_H
#define CPP_CODE_LINKED_LIST_H

struct Node {
    int key;
    Node *next= nullptr;
    Node *prev= nullptr;
};

class LinkedList
{
public:
    Node* head_;
    Node* tail_;
    int size_;
    int length_;  //
    
public:
    LinkedList();
    LinkedList(int);
    ~LinkedList();
public:
    bool Empty();
    bool Full();
    void Insert(Node *prev_node, Node *tmp_Node);

};

LinkedList::LinkedList(): head_(NULL), tail_(NULL), size_(0), length_(10)
{

}

LinkedList::LinkedList(int len): head_(NULL), tail_(NULL), size_(0), length_(len)
{

}

LinkedList::~LinkedList() {}


void LinkedList::Insert(Node *prev_node, Node *tmp_Node)
{
    // 将 tmp_Node 插入到 prev_node 节点之后
    Node *old_next = prev_node->next;
    
}

#endif //CPP_CODE_LINKED_LIST_H
