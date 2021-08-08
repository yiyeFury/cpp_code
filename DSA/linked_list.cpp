//
// Created by xie on 2021/7/31.
//

#include "linked_list.h"

DoublyLinkedList::DoublyLinkedList(): head_(nullptr), tail_(nullptr), size_(0), length_(10)
{

}

DoublyLinkedList::DoublyLinkedList(int len): head_(nullptr), tail_(nullptr), size_(0), length_(len)
{

}

DoublyLinkedList::~DoublyLinkedList() {}


bool DoublyLinkedList::Empty()
{
    return size_ == 0;
}

bool DoublyLinkedList::Full()
{
    return size_ == length_;
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
    
    tmp_node->prev = nullptr;
    tmp_node->next = nullptr;
    
    old_prev -> next = old_next;
    old_next -> prev = old_prev;
    size_--;
}


DoublyLinkedNode *DoublyLinkedList::Search(int k)
{
    // 给定 key 值，搜索 所在节点
    if (Empty()) {
        return nullptr;
    }
    
    DoublyLinkedNode *tmp_node = head_;
    while (tmp_node != tail_ && tmp_node->key != k) {
        tmp_node = tmp_node->next;
    }
    return tmp_node;
}
