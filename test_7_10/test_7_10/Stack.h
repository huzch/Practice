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

    void push(T val)     //����Ԫ����ջ
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

    void pop()                    //��ջ��Ԫ�س�ջ
    {
        if (!isEmpty())
        {
            auto next = top->_next;
            delete top;
            top = next;
        }
    }

    T getTop() const     //����ջ��Ԫ��
    {
        return top->_val;
    }

    bool isEmpty() const          //�ж�ջ�Ƿ�Ϊ��
    {
        return top == nullptr;
    }

private:
    struct Node
    {
        T _val; // ����д�ŵ�Ԫ��
        Node* _next;	         // ָ����һ����ָ��

        Node(const T& val = T())
            : _val(val)
            , _next(nullptr)
        {}
    };
    Node* top;         // ջ��
};