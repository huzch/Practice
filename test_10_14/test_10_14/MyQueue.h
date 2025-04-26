#pragma once

template <typename T>
struct QueueNode
{
    T _val;
    QueueNode<T>* _next;

    QueueNode(const T& val)
        : _val(val)
        , _next(nullptr)
    {}
};

template <typename T>
class Queue
{
    typedef QueueNode<T> Node;
public:
    Queue()   // construct an empty queue
        : _size(0)
    {}

    Queue(const Queue& q)  //拷贝构造函数
        : _size(q._size)
    {
        Node* Guard = new Node(-1);
        _tail = Guard;
        Node* cur = q._head;
        while (cur)
        {
            _tail->_next = new Node(cur->_val);
            cur = cur->_next;
            _tail = _tail->_next;
        }

        _head = Guard->_next;
        delete Guard;
    }

    ~Queue()
    {
        Node* cur = _head;
        while (cur)
        {
            Node* del = cur;
            cur = cur->_next;
            delete del;
        }
    }

    const Queue& operator = (const Queue& q) //操作符重载
    {
        if (this != &q)
        {
            _size = q._size;

            Node* Guard = new Node(-1);
            _tail = Guard;
            Node* cur = q._head;
            while (cur)
            {
                _tail->_next = new Node(cur->_val);
                cur = cur->_next;
                _tail = _tail->_next;
            }

            _head = Guard->_next;
            delete Guard;
        }
        return *this;
    }

    bool empty() const
    {
        return _size == 0;
    }

    int size() const
    {
        return _size;
    }

    bool push(const T& x)	//正常入队则返回true，若无空闲内存则返回false
    {
        if (_tail)
        {
            _tail->_next = new Node(x);
            _tail = _tail->_next;
        }
        else
        {
            _head = _tail = new Node(x);
        }
        ++_size;
        return true;
    }

    bool pop()	//正常出队则返回true，队内无元素则返回false
    {
        if (empty()) return false;

        Node* del = _head;
        _head = _head->_next;
        delete del;
        --_size;

        if (!_head) _tail = nullptr;
        return true;
    }

    const T& front() const
    {
        return _head->_val;
    }
private:
    Node* _head, * _tail;
    int _size;
};