#include "list.h"

SqList::SqList()  // ���캯����Ĭ��Ϊ�ձ�
    : length(0)
{}

SqList::SqList(int a[], size_t n)  // ���캯������������a[]��˳���
    : length(n)
{
    for (int i = 0; i < length; ++i)
    {
        data[i] = a[i];
    }
}

SqList::SqList(const SqList& sq)  // ���캯��������˳���sq
    : length(sq.length)
{
    for (int i = 0; i < length; ++i)
    {
        data[i] = sq.data[i];
    }
}

size_t SqList::size() const  // ���˳���ĳ���
{
    return length;
}

bool SqList::empty() const  // �ж��Ƿ�Ϊ�ձ�
{
    return length == 0;
}

void SqList::clear()  // ���
{
    length = 0;
}

int& SqList::operator[](size_t i)  // ��������أ�sq[i]���sq�ĵ�i��Ԫ��
{
    return data[i];
}

int& SqList::back()  // ������һ��Ԫ��
{
    return data[length - 1];
}

void SqList::insert(size_t i, int e)  // ��sq[i]��ǰ�����һ��Ԫ��e
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

void SqList::erase(size_t i)  // ɾ��Ԫ��sq[i]
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

void SqList::push_back(int e)  // �����һ��Ԫ�غ����Ԫ��e
{
    SqList::insert(length, e);
}

void SqList::push_front(int e)  // �ڵ�һ��Ԫ��ǰ���Ԫ��e
{
    SqList::insert(0, e);
}

int SqList::pop_back()  // ɾ�����һ��Ԫ�أ����������ֵ
{
    int e = data[length - 1];
    SqList::erase(length - 1);
    return e;
}

int SqList::pop_front()  // ɾ����һ��Ԫ�أ����������ֵ
{
    int e = data[0];
    SqList::erase(0);
    return e;
}