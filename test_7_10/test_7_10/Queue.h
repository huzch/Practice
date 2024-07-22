#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template<class T>
class Queue
{
public:
    Queue()
        : front_node(nullptr)
        , back_node(nullptr)
        , node_num(0)
    {}

    Queue(const Queue<T>& q)
        : front_node(nullptr)
        , back_node(nullptr)
        , node_num(0)
    {
        auto cur = q.front_node;
        while (cur)
        {
            push(cur->element);
            cur = cur->next;
        }
    }

    ~Queue()
    {
        auto cur = front_node;
        while (cur)
        {
            auto next = cur->next;
            delete cur;
            cur = next;
        }
        node_num = 0;
    }

    bool empty() const
    {
        return node_num == 0;
    }

    int size() const
    {
        return node_num;
    }

    T front() const
    {
        return front_node->element;
    }

    T back() const
    {
        return back_node->element;
    }

    void push(T element)
    {
        if (front_node == nullptr && back_node == nullptr)
        {
            front_node = back_node = new Node(element);
        }
        else
        {
            back_node->next = new Node(element);
            back_node = back_node->next;
        }
        ++node_num;
    }

    void pop()
    {
        if (front_node)
        {
            auto del = front_node;
            front_node = front_node->next;
            delete del;
            --node_num;
        }
    }

    void swap(Queue<T>& q)
    {
        std::swap(front_node, q.front_node);
        std::swap(back_node, q.back_node);
        std::swap(node_num, q.node_num);
    }

private:
    struct Node
    {
        T element;
        Node* next;
        Node(T ele, Node* n = nullptr)
        {
            element = ele;
            next = n;
        }
    };
    Node* front_node;
    Node* back_node;
    int node_num;
};