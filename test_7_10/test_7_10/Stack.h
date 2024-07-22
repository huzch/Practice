#pragma once
#include<iostream>
using namespace std;

template <class T>
class Stack
{
public:
    Stack()
        : top(nullptr)
    {}

    ~Stack()
    {
        auto cur = top;
        while (cur)
        {
            auto next = cur->_next;
            delete cur;
            cur = next;
        }
    }

    void push(T val)     //将新元素入栈
    {
        if (isEmpty())
        {
            top = new Node(val);
        }
        else
        {
            auto node = new Node(val);
            node->_next = top;
            top = node;
        }
    }

    void pop()                    //将栈顶元素出栈
    {
        if (!isEmpty())
        {
            auto next = top->_next;
            delete top;
            top = next;
        }
    }

    T getTop() const     //返回栈顶元素
    {
        return top->_val;
    }

    bool isEmpty() const          //判断栈是否为空
    {
        return top == nullptr;
    }

private:
    struct Node
    {
        T _val; // 结点中存放的元素
        Node* _next;	         // 指向下一结点的指针

        Node(const T& val = T())
            : _val(val)
            , _next(nullptr)
        {}
    };
    Node* top;         // 栈顶
};