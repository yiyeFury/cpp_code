//
// Created by xie on 2021/7/14.
//

#ifndef CPP_CODE_LINKED_LIST_H
#define CPP_CODE_LINKED_LIST_H

typedef struct DoublyLinkedNode {
    int key;
    int data;
    DoublyLinkedNode *next= nullptr;
    DoublyLinkedNode *prev= nullptr;
}DoublyLinkedNode;

class DoublyLinkedList
{
public:
    DoublyLinkedNode* head_;
    DoublyLinkedNode* tail_;
    int size_;  // 链表当前元素的数量
    int length_;  // 链表的长度，即最多能存储的数量
    
public:
    DoublyLinkedList();
    DoublyLinkedList(int);
    ~DoublyLinkedList();
public:
    bool Empty();
    bool Full();
    
    void InsertHead(DoublyLinkedNode *tmp_node);
    void Insert(DoublyLinkedNode *prev_node, DoublyLinkedNode *tmp_Node);
    void Delete(DoublyLinkedNode *node);
    
    DoublyLinkedNode *Search(int k);

};



#endif //CPP_CODE_LINKED_LIST_H
