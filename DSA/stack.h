//
// Created by xie on 2021/7/11.
//

#ifndef CPP_CODE_STACK_H
#define CPP_CODE_STACK_H


template<typename T>
class Stack {
public:
    Stack();
    Stack(int, int);
    
    int top_=0;  // 当前元素数量
    int capacity_=10;  // 栈中可容纳数量
    // T data_[5];
    
    bool Empty();
    void Push(T val);
    T Pop();

};

template<typename T>
Stack<T>::Stack(): top_(0), capacity_(10)
{

}

template<typename T>
Stack<T>::Stack(int t, int c): top_(t), capacity_(c)
{

}

template<typename T>
bool Stack<T>::Empty()
{
    return (top_==0)?true:false;
}


#endif //CPP_CODE_STACK_H
