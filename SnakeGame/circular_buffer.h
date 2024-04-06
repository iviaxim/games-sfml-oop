#pragma once

#include <vector>

namespace utils
{

	template<class T>
	class CircularBuffer {
	public:
		CircularBuffer(int maxSize)
			: backIndex(0)
			, headIndex(0)
		{
			reserve(maxSize);
		}

		size_t size() const;

		bool full() const;

		void pop();

		void push(const T& item);

		void clear();

		void reserve(size_t size);

		const T& operator [] (size_t index) const;

		T& operator [] (size_t index);

	private:
		inline int realIndex_(int index) const { return (backIndex + index) % items_.size(); }

		std::vector<T> items_;
		size_t	backIndex;
		size_t	headIndex;
	};

	template<class T>
	size_t CircularBuffer<T>::size() const
	{
		return (headIndex - backIndex + items_.size()) % items_.size();
	}

	template<class T>
	bool CircularBuffer<T>::full() const
	{
		return size() == (items_.size() - 1);
	}

	template<class T>
	void CircularBuffer<T>::pop()
	{
		if (size() != 0)
			backIndex = ++backIndex % items_.size();
	}

	template<class T>
	void CircularBuffer<T>::push(const T& item)
	{
		if (full()) pop();

		items_[headIndex] = item;
		headIndex = ++headIndex % items_.size();
	}

	template<class T>
	void CircularBuffer<T>::clear()
	{
		backIndex = headIndex = 0;
	}

	template<class T>
	void CircularBuffer<T>::reserve(size_t size)
	{
		clear();
		items_.resize(size + 1);
	}

	template<class T>
	const T& CircularBuffer<T>::operator [] (size_t index) const
	{
		return items_[realIndex_(index)];
	}

	template<class T>
	T& CircularBuffer<T>::operator [] (size_t index)
	{
		return items_[realIndex_(index)];
	}

}
