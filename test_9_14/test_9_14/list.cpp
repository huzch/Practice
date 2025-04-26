#include "list.h"

SqList::SqList()  // 构造函数：默认为空表
    : length(0)
{}

SqList::SqList(int a[], size_t n)  // 构造函数：拷贝数组a[]到顺序表
    : length(n)
{
    for (int i = 0; i < length; ++i)
    {
        data[i] = a[i];
    }
}

SqList::SqList(const SqList& sq)  // 构造函数：复制顺序表sq
    : length(sq.length)
{
    for (int i = 0; i < length; ++i)
    {
        data[i] = sq.data[i];
    }
}

size_t SqList::size() const  // 获得顺序表的长度
{
    return length;
}

bool SqList::empty() const  // 判断是否为空表
{
    return length == 0;
}

void SqList::clear()  // 清空
{
    length = 0;
}

int& SqList::operator[](size_t i)  // 运算符重载，sq[i]获得sq的第i个元素
{
    return data[i];
}

int& SqList::back()  // 获得最后一个元素
{
    return data[length - 1];
}

void SqList::insert(size_t i, int e)  // 在sq[i]的前面插入一个元素e
{
    if (length == max_size) return;

    int pos = length;
    while (pos != i)
    {
        data[pos] = data[pos - 1];
        --pos;
    }
    data[pos] = e;
    ++length;
}

void SqList::erase(size_t i)  // 删除元素sq[i]
{
    if (length == 0) return;

    int pos = i + 1;
    while (pos != length)
    {
        data[pos - 1] = data[pos];
        ++pos;
    }
    --length;
}

void SqList::push_back(int e)  // 在最后一个元素后添加元素e
{
    SqList::insert(length, e);
}

void SqList::push_front(int e)  // 在第一个元素前添加元素e
{
    SqList::insert(0, e);
}

int SqList::pop_back()  // 删除最后一个元素，并返回这个值
{
    int e = data[length - 1];
    SqList::erase(length - 1);
    return e;
}

int SqList::pop_front()  // 删除第一个元素，并返回这个值
{
    int e = data[0];
    SqList::erase(0);
    return e;
}