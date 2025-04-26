#pragma once

template<class T>
class Stack
{
public:
	void Push(const T& v)
	{
		_st.push_back(v);
	}

	void Pop()
	{
		_st.pop_back();
	}

	T Top()
	{
		return _st.back();
	}

	bool Empty()
	{
		return _st.empty();
	}
private:
	vector<T> _st;
};