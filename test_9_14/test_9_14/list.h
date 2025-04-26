#pragma once
#pragma once
#include <array>
#include <iostream>

class SqList {
    static const int max_size = 1024;
    std::array<int, max_size> data;
    size_t length;

public:
    SqList();  // 构造函数：默认为空表

    SqList(int a[], size_t n);  // 构造函数：拷贝数组a[]到顺序表

    SqList(const SqList& sq);  // 构造函数：复制顺序表sq

    size_t size() const;  // 获得顺序表的长度

    bool empty() const;  // 判断是否为空表

    void clear();  // 清空

    int& operator[](size_t i);  // 运算符重载，sq[i]获得sq的第i个元素

    int& back();  // 获得最后一个元素

    void insert(size_t i, int e);  // 在sq[i]的前面插入一个元素e

    void erase(size_t i);  // 删除元素sq[i]

    void push_back(int e);  // 在最后一个元素后添加元素e

    void push_front(int e);  // 在第一个元素前添加元素e

    int pop_back();  // 删除最后一个元素，并返回这个值

    int pop_front();  // 删除第一个元素，并返回这个值

    void print() {
        for (size_t i = 0; i < length; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};
