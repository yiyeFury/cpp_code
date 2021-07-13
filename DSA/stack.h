//
// Created by xie on 2021/7/11.
//

#ifndef CPP_CODE_STACK_H
#define CPP_CODE_STACK_H


template<typename T>
class Stack {
public:
    int top_=0;  // 当前元素数量
    int capacity_;  // 栈中可容纳数量
    vector<T> data_;

public:
    Stack();
    Stack(int);
    
public:
    bool Empty();
    bool Full();
    void Push(T val);
    T Pop();

};

template<typename T>
Stack<T>::Stack(): capacity_(10)
{

}

template<typename T>
Stack<T>::Stack(int c): capacity_(c)
{

}

template<typename T>
bool Stack<T>::Empty()
{
    return (top_ == 0) ? true : false;
}

template<typename T>
bool Stack<T>::Full() {
    return top_ == capacity_;
}


template<typename T>
void Stack<T>::Push(T val)
{
    if (Full()) {
        string s1 = "Stack is full";
        cout<<endl<<s1<<endl;
        return;
    }
    data_.push_back(val);
    top_ += 1;
}

template<typename T>
T Stack<T>::Pop()
{
    if (top_ == 0) {
        cout<<"underflow"<<endl;
        return -999;
    }
    T val = data_[top_-1];
    data_.pop_back();
    top_ -= 1;
    return val;
}


#endif //CPP_CODE_STACK_H
