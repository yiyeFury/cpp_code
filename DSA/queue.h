//
// Created by xie on 2021/7/13.
//

#ifndef CPP_CODE_QUEUE_H
#define CPP_CODE_QUEUE_H
#include <vector>
#include <iostream>
using namespace std;


template<class T>
class Queue
{
public:
    int head_ = 0;  // 首元素位置下标
    int tail_ = 0;  // 尾元素后一位位置下标
    int size_ = 0;  // 队列中 当前存储的 元素数量
    int capacity_;  // 队列的长度，即队列中 最多能存储的 元素 数量
    T *data_ = nullptr;

public:
    Queue();
    Queue(int);
    ~Queue();

public:
    void Print();
    bool Empty();
    bool Full();
    void Enqueue(T);
    T Dequeue();
};


template<class T>
class Deque: public Queue<T>
{
public:
    Deque();
    Deque(int);
    ~Deque();

public:
    void EnqueueHead(T);
    void EnqueueTail(T);
    
    T DequeueHead();
    T DequeueTail();
};

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////
 */
template<class T>
Queue<T>::Queue(): capacity_(10)
{
    data_ = new T [capacity_];
}

template<class T>
Queue<T>::Queue(int len): capacity_(len)
{
    data_ = new T [capacity_];
}

template<class T>
Queue<T>::~Queue()
{
    delete [] data_;
    data_ = nullptr;
}

template<class T>
void Queue<T>::Print()
{
    if (Empty()) {
        cout<<"Queue is empty\n";
        return;
    }
    int ii = 0;
    for(ii=head_;ii<tail_;ii++) {
        cout<<"     "<<data_[ii];
    }
    cout<<endl;
}


template<class T>
bool Queue<T>::Empty()
{
    return size_ == 0;
}

template<class T>
bool Queue<T>::Full() {
    return size_ == capacity_;
}

template<class T>
void Queue<T>::Enqueue(T val)
{
    if (Full()) {
        throw runtime_error("Queue overflow");
    }
    size_++;
    data_[tail_++]=val;
}

template<class T>
T Queue<T>::Dequeue() {
    if (Empty()) {
        throw runtime_error("Queue underflow");
    }
    size_--;
    T val = data_[head_++];
    return val;
}

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////
 */
template<class T>
Deque<T>::Deque(): Queue<T>() {

}

template<class T>
Deque<T>::Deque(int len): Queue<T>(len) {

}

template<class T>
Deque<T>::~Deque() {
}

template<class T>
void Deque<T>::EnqueueHead(T val) {
    if (Queue<T>::head_ == 0) {
        throw runtime_error("Deque head overflow");
    } else if (Queue<T>::Full()) {
        throw runtime_error("Deque overflow");
    }
    
    Queue<T>::size_++;
    Queue<T>::data_[--Queue<T>::head_] = val;
}

template<class T>
void Deque<T>::EnqueueTail(T val) {
    if (Queue<T>::tail_ == Queue<T>::capacity_) {
        throw runtime_error("Deque tail overflow");
    } else if (Deque<T>::Full()) {
        throw runtime_error("Deque overflow");
    }
    Queue<T>::Enqueue(val);
}

template<class T>
T Deque<T>::DequeueHead() {
    if (Queue<T>::Full()) {
        throw runtime_error("Deque underflow");
    }
    
    T val = Queue<T>::Dequeue();
    return val;
}

template<class T>
T Deque<T>::DequeueTail() {
    if (Queue<T>::Empty()) {
        throw runtime_error("Deque underflow");
    }
    
    T val = Queue<T>::data_[--Queue<T>::tail_];
    Queue<T>::size_--;
    // Queue<T>::data_[Queue<T>::tail_] = Queue<T>::fill_value_;
    return val;
}


#endif //CPP_CODE_QUEUE_H
