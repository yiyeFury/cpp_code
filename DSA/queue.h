//
// Created by xie on 2021/7/13.
//

#ifndef CPP_CODE_QUEUE_H
#define CPP_CODE_QUEUE_H
#include <vector>
using namespace std;


template<class T>
class Queue
{
public:
    int head_ = 0;  // 首元素位置下标
    int tail_ = 0;  // 尾元素后一位位置下标
    int size_ = 0;  // 队列中 当前存储的 元素数量
    int length_;  // 队列的长度，即队列中 最多能存储的 元素 数量
    T fill_value_;
    vector<T> data_;

public:
    Queue();
    Queue(int, T);
    ~Queue();

public:
    bool Empty();
    bool Full();
    void Enqueue(T);
    T Dequeue();
};

template<class T>
Queue<T>::Queue(): length_(10), fill_value_(T(-1)), data_(length_, fill_value_)
{

}

template<class T>
Queue<T>::Queue(int len, T val): length_(len), fill_value_(val)
{
    data_(length_, fill_value_);
}

template<class T>
Queue<T>::~Queue()
{

}

template<class T>
bool Queue<T>::Empty()
{
    return size_ == 0;
}

template<class T>
bool Queue<T>::Full() {
    return size_ == length_;
}

template<class T>
void Queue<T>::Enqueue(T val)
{
    if (tail_ == length_) {
        cout<<"tail reach the end";
        return;
    }
    size_++;
    data_[tail_++]=val;
}

template<class T>
T Queue<T>::Dequeue() {
    if (Empty()) {
        string s1 = "error: Queue is empty";
        cout<<endl<<s1<<endl;
        return fill_value_;
    }
    size_--;

    T val = data_[head_];
    data_[head_++]=fill_value_;
    return val;
}


template<class T>
class Deque: public Queue<T>
{
public:
    Deque();
    Deque(int, T);
    ~Deque();

public:
    void EnqueueHead(T);
    void EnqueueTail(T);

    T DequeueHead();
    T DequeueTail();


};

template<class T>
Deque<T>::Deque(): Queue<T>() {

}

template<class T>
Deque<T>::Deque(int len, T val): Queue<T>(len, val) {

}

template<class T>
Deque<T>::~Deque() {

}

template<class T>
void Deque<T>::EnqueueHead(T val) {
    if (Queue<T>::head_ == 0) {
     string erro_info = "Can not Enqueue from head";
     cout<<erro_info<<endl;
        return;
    }
    
    Queue<T>::size_++;
    Queue<T>::data_[--Queue<T>::head_] = val;
}

template<class T>
void Deque<T>::EnqueueTail(T val) {
    Queue<T>::Enqueue(val);
}

template<class T>
T Deque<T>::DequeueHead() {
    T val = Queue<T>::Dequeue();
    return val;
}

template<class T>
T Deque<T>::DequeueTail() {
    if (Queue<T>::Empty()) {
        return Queue<T>::fill_value_;
    }
    
    T val = Queue<T>::data_[--Queue<T>::tail_];
    Queue<T>::size_--;
    Queue<T>::data_[Queue<T>::tail_] = Queue<T>::fill_value_;
    return val;
}


#endif //CPP_CODE_QUEUE_H
