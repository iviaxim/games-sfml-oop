#pragma once

#include <vector>

namespace utils
{

	template<class T>
	class CiclicBuffer {
	public:
		CiclicBuffer(int maxSize)
			: b_(0)
			, e_(0) {
			reserve(maxSize);
		}
		virtual ~CiclicBuffer() {}

		//T	at(int index) const { return items_[realIndex_(index)]; }

		size_t	size() const { return (e_ - b_ + maxSize_) % maxSize_; }
		bool	full() const { return size() == (maxSize_ - 1); }
		//bool	empty() const { return b_ == e_; }

		void	pop() {
			// если есть, что доставать
			if (b_ != e_)
				b_ = (++b_ % maxSize_);
		}
		void	push(const T& item) {
			// если очередь заполнена, то достаём старый элемент
			if (full()) pop();

			items_[e_] = item;
			e_ = ++e_ % maxSize_;
		}

		void	clear() { b_ = e_ = 0; }
		void	reserve(size_t size) {
			clear();
			maxSize_ = size + 1;
			items_.resize(maxSize_);
		}

		const T& operator [] (size_t index) const { return items_[realIndex_(index)]; }
		T& operator [] (size_t index) { return items_[realIndex_(index)]; }

	private:
		inline	int	realIndex_(int index) const { return (b_ + index) % maxSize_; }

		size_t	maxSize_;
		std::vector<T> items_;
		size_t	b_;
		size_t	e_;
	};

}
