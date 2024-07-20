#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class String
{
public:
    String() 
        : n(0)
        , capacity(16)
        , str(new char[16])
    {
        str[0] = '\0';
    }

    String(const char* s) 
        : n(strlen(s))
        , capacity(n * 2)
        , str(new char[capacity])
    {
        strcpy(str, s);
    }

    String(const String& other) 
        : n(other.n)
        , capacity(other.capacity)
        , str(new char[capacity])
    {
        strcpy(str, other.str);
    }

    ~String()
    {
        delete[] str;
    }

    const char* c_str() const
    {
        return str;
    }

    void clear()
    {
        if (str != NULL)
        {
            delete[] str;
        }
        n = 0;
        capacity = 16;
        str = new char[capacity];
        str[0] = '\0';
    }

    String& operator+=(char c)
    {
        if (n + 1 >= capacity)
        {
            int size = capacity * 2;
            if (size < 0)
            {                       // Too many elements
                size = 1 << 30;  // Good luck allocating 2 ^ 30 elements
            }
            capacity = size;
            char* newStr = new char[capacity];
            strcpy(newStr, str);
            delete[] str;
            str = newStr;
        }
        str[n++] = c;  // Append c to the end of str
        str[n] = '\0'; // Null terminate the string
        return *this;
    }

    int getSize() const { return n; }
    int getcapacity() const { return capacity; }

    //// Your Implementation.
    const char& operator[](int index) const
    {
        return str[index];
    }

    friend ostream& operator<<(ostream& out, const String& s)
    {
        out << s.str << endl;
        return out;
    }

    friend istream& operator>>(istream& in, String& s)
    {
        s.clear();
        char ch = in.get();
        while (!isspace(ch) && !in.eof())
        {
            s += ch;
            ch = in.get();
        }
        return in;
    }

private:
    int n; // Length of the string
    int capacity; // Capacity of the buffer
    char* str; // Buffer to store the string
};

class StringJoiner
{
public:
    StringJoiner(char c = ' ') 
        : c(c) 
    {}

    String operator()(const String& a, const String& b) const
    {
        int n1 = a.getSize(), n2 = b.getSize();
        char* s = new char[n1 + n2 + 2];
        for (int i = 0; i < n1; ++i)
        {
            s[i] = a[i];
        }
        s[n1] = c;
        for (int i = 0; i < n2; ++i)
        {
            s[i + n1 + 1] = b[i];
        }
        s[n1 + n2 + 1] = '\0';

        String ret(s);
        delete[] s;
        return ret;
    }

private:
    char c;
};