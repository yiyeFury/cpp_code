//
// Created by xie on 2021/7/11.
//

#ifndef CPP_CODE_STACK_H
#define CPP_CODE_STACK_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;


template<typename T>
class Stack {
public:
    // int top_ = -1;
    int size_=0;  // 当前元素数量
    int capacity_;  // 栈中可容纳数量
    T *data_= nullptr;

public:
    Stack();
    Stack(int);
    ~Stack();
    
public:
    void Print();
    bool Empty();
    bool Full();
    void Push(T val);
    T Pop();
};

template<typename T>
Stack<T>::Stack(): capacity_(10)
{
    data_ = new T [capacity_];
}

template<typename T>
Stack<T>::Stack(int c): capacity_(c)
{
    data_ = new T [capacity_];
}

template<typename T>
Stack<T>::~Stack()
{
    delete [] data_;
    data_ = nullptr;
}

template<typename T>
void Stack<T>::Print()
{
    for(int ii=0;ii<size_;ii++) {
        cout<<"     "<<*(data_+ii);
    }
    cout<<endl<<endl;
}

template<typename T>
bool Stack<T>::Empty()
{
    return (size_ == 0) ? true : false;
}

template<typename T>
bool Stack<T>::Full() {
    return size_ == capacity_;
}


template<typename T>
void Stack<T>::Push(T val)
{
    if (Full()) {
        throw runtime_error("stack overflow");
    }
    // *(data_ + size_) = val;
    data_[size_] = val;
    size_ += 1;
}

template<typename T>
T Stack<T>::Pop()
{
    if (Empty()) {
        throw runtime_error("stack underflow");
    }
    
    size_ -= 1;
    T val = data_[size_];
    return val;
}


#endif //CPP_CODE_STACK_H
