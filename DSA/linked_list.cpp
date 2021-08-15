//
// Created by xie on 2021/7/31.
//

#include "linked_list.h"
#include <iostream>

using namespace std;

DoublyLinkedList::DoublyLinkedList(): head_(nullptr), tail_(nullptr), size_(0), capacity_(10)
{

}

DoublyLinkedList::DoublyLinkedList(int len): head_(nullptr), tail_(nullptr), size_(0), capacity_(len)
{

}

DoublyLinkedList::~DoublyLinkedList() {}


bool DoublyLinkedList::Empty()
{
    return size_ == 0;
}


bool DoublyLinkedList::Full()
{
    return size_ == capacity_;
}


void DoublyLinkedList::InsertHead(DoublyLinkedNode *tmp_node)
{
    // 在 head 前插入节点；即新插入的节点作为 head
    if (Full()) return;
    else if (Empty()) {
        head_ = tmp_node;
        head_ -> prev = nullptr;
    
        tail_ = tmp_node;
        tail_ -> next = nullptr;
    } else {
        DoublyLinkedNode *old_head = head_;
        // 前端连接
        head_ = tmp_node;
        head_ -> prev = nullptr;
        
        // 后端连接
        tmp_node -> next = old_head;
        old_head -> prev = head_;
    }
    size_++;
    
}

void DoublyLinkedList::Insert(DoublyLinkedNode *prev_node, DoublyLinkedNode *tmp_node)
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
        DoublyLinkedNode *old_next = prev_node->next;
        
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


void DoublyLinkedList::Delete(DoublyLinkedNode *tmp_node)
{
    if (Empty()) {
        return;
    }
    
    DoublyLinkedNode *old_prev, *old_next;
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


DoublyLinkedNode *DoublyLinkedList::Search(int k)
{
    // 给定 key 值，搜索 所在节点
    if (Empty()) {
        return nullptr;
    }
    
    DoublyLinkedNode *tmp_node = head_;
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

void DoublyLinkedList::Print()
{
    if (Empty()) {
        cout<<"Linked list is empty."<<endl;
        return;
    }
    DoublyLinkedNode *tmp_node;
    tmp_node = head_;
    for (int ii=0;ii<size_;ii++) {
        cout<<"   "<<tmp_node->key;
        tmp_node = tmp_node->next;
    }
    
}


// int main()
// {
//     cout << "\nStart\n\n";
//
//     cout << "\n\nend\n" << endl;
//     // system("pause");
//     return 0;
// }
