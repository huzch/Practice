#pragma once
#pragma once
#include <array>
#include <iostream>

class SqList {
    static const int max_size = 1024;
    std::array<int, max_size> data;
    size_t length;

public:
    SqList();  // ���캯����Ĭ��Ϊ�ձ�

    SqList(int a[], size_t n);  // ���캯������������a[]��˳���

    SqList(const SqList& sq);  // ���캯��������˳���sq

    size_t size() const;  // ���˳���ĳ���

    bool empty() const;  // �ж��Ƿ�Ϊ�ձ�

    void clear();  // ���

    int& operator[](size_t i);  // ��������أ�sq[i]���sq�ĵ�i��Ԫ��

    int& back();  // ������һ��Ԫ��

    void insert(size_t i, int e);  // ��sq[i]��ǰ�����һ��Ԫ��e

    void erase(size_t i);  // ɾ��Ԫ��sq[i]

    void push_back(int e);  // �����һ��Ԫ�غ����Ԫ��e

    void push_front(int e);  // �ڵ�һ��Ԫ��ǰ���Ԫ��e

    int pop_back();  // ɾ�����һ��Ԫ�أ����������ֵ

    int pop_front();  // ɾ����һ��Ԫ�أ����������ֵ

    void print() {
        for (size_t i = 0; i < length; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};
