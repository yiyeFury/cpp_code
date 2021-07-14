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
    int length_;  // 队列的长度，即队列中能存储的 元素 数量
    int head_=-1;  // 首元素位置下标
    int tail_=0;  // 尾元素后一位位置下标
    
    vector<T> data_;

public:
    Queue();
    Queue(int);

public:
    bool Empty();
    bool Full();
    void Enqueue(T);
    T Dequeue();
};

template<class T>
Queue<T>::Queue(): length_(10), data_(length_)
{

}

template<class T>
Queue<T>::Queue(int len): length_(len)
{
    data_(length_);
}

template<class T>
bool Queue<T>::Empty()
{
    return (head_ < 0) || (head_==tail_);
}

template<class T>
bool Queue<T>::Full() {
    return tail_-head_==length_;
}

template<class T>
void Queue<T>::Enqueue(T val)
{
    if (tail_ == length_) {
        cout<<"tail reach the end";
        return;
    }
    tail_++;
    data_[tail_++]=val;
}

template<class T>
T Queue<T>::Dequeue() {
    if (Empty()) {
        string s1 = "Queue is empty";
        cout<<endl<<s1<<endl;
        return T(-1);
    }
    T val = data_[head_];
    data_[head_++]=0;
    return val;
}


#endif //CPP_CODE_QUEUE_H