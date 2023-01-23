#ifndef ACTION_HPP
#define ACTION_HPP

#include <functional>
#include <vector>

template <typename T>
class Action
{
private:

	std::vector<std::function<void(T)>> actions;

public:

	Action<T>()
	{

	}

	void Clear()
	{
		actions.clear();
	}

	Action<T>& operator+=(std::function<void(T)> other)
	{
		actions.push_back(other);
		return *this;
	}

	void operator()(T arg)
	{
		for (int i = 0; i < actions.size(); i++)
		{
			actions[i](arg);
		}
	}
};

template <typename T1, typename T2>
class Action2
{
private:

	std::vector<std::function<void(T1, T2)>> actions;

public:

	Action2<T1, T2>()
	{

	}

	void Clear()
	{
		actions.clear();
	}

	Action2<T1, T2>& operator+=(std::function<void(T1, T2)> other)
	{
		actions.push_back(other);
		return *this;
	}

	void operator()(T1 arg1, T2 arg2)
	{
		for (int i = 0; i < actions.size(); i++)
		{
			actions[i](arg1, arg2);
		}
	}
};

template <typename T1, typename T2, typename T3>
class Action3
{
private:

	std::vector<std::function<void(T1, T2, T3)>> actions;

public:

	Action3<T1, T2, T3>()
	{

	}

	void Clear()
	{
		actions.clear();
	}

	Action3<T1, T2, T3>& operator+=(std::function<void(T1, T2, T3)> other)
	{
		actions.push_back(other);
		return *this;
	}

	void operator()(T1 arg1, T2 arg2, T3 arg3)
	{
		for (int i = 0; i < actions.size(); i++)
		{
			actions[i](arg1, arg2, arg3);
		}
	}
};

template <typename T1, typename T2, typename T3, typename T4>
class Action4
{
private:

	std::vector<std::function<void(T1, T2, T3, T4)>> actions;

public:

	Action4<T1, T2, T3, T4>()
	{

	}

	void Clear()
	{
		actions.clear();
	}

	Action4<T1, T2, T3, T4>& operator+=(std::function<void(T1, T2, T3, T4)> other)
	{
		actions.push_back(other);
		return *this;
	}

	void operator()(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
	{
		for (int i = 0; i < actions.size(); i++)
		{
			actions[i](arg1, arg2, arg3, arg4);
		}
	}
};

#endif 
