//
// Created by xie on 2021/7/14.
//

#ifndef CPP_CODE_LINKED_LIST_H
#define CPP_CODE_LINKED_LIST_H

#include <iostream>

using namespace std;

template<class T1, class T2>
struct DoublyLinkedNode {
    T1 key;
    T2 data;
    DoublyLinkedNode *next= nullptr;
    DoublyLinkedNode *prev= nullptr;
};


template<class T1, class T2>
class DoublyLinkedList
{
public:
    DoublyLinkedNode<T1, T2>* head_= nullptr;
    DoublyLinkedNode<T1, T2>* tail_= nullptr;
    int size_=0;  // 链表当前元素的数量
    int capacity_;  // 链表的长度，即最多能存储的数量
    
public:
    DoublyLinkedList();
    DoublyLinkedList(int);
    ~DoublyLinkedList();
public:
    bool Empty();
    bool Full();
    void Print();
    
    void InsertHead(DoublyLinkedNode<T1, T2> *tmp_node);
    void Insert(DoublyLinkedNode<T1, T2> *prev_node, DoublyLinkedNode<T1, T2> *tmp_Node);
    void Delete(DoublyLinkedNode<T1, T2> *node);
    
    DoublyLinkedNode<T1, T2> *Search(int k);

};

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////
 * DoublyLinkedList
 */
template<typename T1, typename T2>
DoublyLinkedList<T1, T2>::DoublyLinkedList(): size_(0), capacity_(10)
{

}

template<class T1, class T2>
DoublyLinkedList<T1, T2>::DoublyLinkedList(int len): size_(0), capacity_(len)
{

}

template<class T1, class T2>
DoublyLinkedList<T1, T2>::~DoublyLinkedList() {}

template<class T1, class T2>
bool DoublyLinkedList<T1, T2>::Empty()
{
    return size_ == 0;
}

template<class T1, class T2>
bool DoublyLinkedList<T1, T2>::Full()
{
    return size_ == capacity_;
}

template<class T1, class T2>
void DoublyLinkedList<T1, T2>::InsertHead(DoublyLinkedNode<T1, T2> *tmp_node)
{
    // 在 head 前插入节点；即新插入的节点作为 head
    if (Full()) return;
    else if (Empty()) {
        head_ = tmp_node;
        head_ -> prev = nullptr;
        
        tail_ = tmp_node;
        tail_ -> next = nullptr;
    } else {
        DoublyLinkedNode<T1, T2> *old_head = head_;
        // 前端连接
        head_ = tmp_node;
        head_ -> prev = nullptr;
        
        // 后端连接
        tmp_node -> next = old_head;
        old_head -> prev = head_;
    }
    size_++;
    
}

template<class T1, class T2>
void DoublyLinkedList<T1, T2>::Insert(DoublyLinkedNode<T1, T2> *prev_node, DoublyLinkedNode<T1, T2> *tmp_node)
{
    // 将 tmp_Node 插入到 prev_node 节点之后
    if (Full()) {  // 链表已满
        return;
    }else if (Empty()) {  // 链表为空
        head_ = tmp_node;
        head_ -> prev = nullptr;
        
        tail_ = tmp_node;
        tail_ -> next = nullptr;
        
    } else {
        DoublyLinkedNode<T1, T2> *old_next = prev_node->next;
        
        // 前向拼接
        prev_node->next = tmp_node;
        tmp_node ->prev = prev_node;
        
        // 后向拼接
        tmp_node -> next = old_next;
        
        // 当前节点，是否为 尾结点
        if (prev_node==tail_) {
            tail_ = tmp_node;
        } else {
            old_next -> prev = tmp_node;
        }
    }
    size_++;
}

template<class T1, class T2>
void DoublyLinkedList<T1, T2>::Delete(DoublyLinkedNode<T1, T2> *tmp_node)
{
    if (Empty()) {
        return;
    }
    
    DoublyLinkedNode<T1, T2> *old_prev, *old_next;
    old_prev = tmp_node->prev;
    old_next = tmp_node -> next;
    // 要删除的节点为 head
    if (tmp_node == head_) {
        head_ = tmp_node->next;
    } else {
        old_prev -> next = old_next;
    }
    
    // 要删除的节点为 tail
    if (tmp_node == tail_) {
        tail_ = tmp_node -> prev;
    } else {
        old_next -> prev = old_prev;
    }
    
    tmp_node->prev = nullptr;
    tmp_node->next = nullptr;
    size_--;
}

template<class T1, class T2>
DoublyLinkedNode<T1, T2> *DoublyLinkedList<T1, T2>::Search(int k)
{
    // 给定 key 值，搜索 所在节点
    if (Empty()) {
        return nullptr;
    }
    
    DoublyLinkedNode<T1, T2> *tmp_node = head_;
    int ii = 0;
    for(;ii<size_;ii++) {
        if (tmp_node -> key == k) {
            return tmp_node;
        }
        tmp_node = tmp_node -> next;
    }
    // while (tmp_node != tail_ && tmp_node->key != k) {
    //     tmp_node = tmp_node->next;
    // }
    return nullptr;
}

template<class T1, class T2>
void DoublyLinkedList<T1, T2>::Print()
{
    if (Empty()) {
        cout<<"Linked list is empty."<<endl;
        return;
    }
    DoublyLinkedNode<T1, T2> *tmp_node;
    tmp_node = head_;
    for (int ii=0;ii<size_;ii++) {
        cout<<"   "<<tmp_node->key;
        tmp_node = tmp_node->next;
    }
    
}



#endif //CPP_CODE_LINKED_LIST_H
