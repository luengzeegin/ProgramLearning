#include <iostream>
#include <assert.h>

#define WALK_LENGTH 64;

using namespace std;

template<typename T>
class Myvector
{
public:
	Myvector()
		:_array(nullptr), _vec_size(0), _vec_capacity(0)
	{
	}

	Myvector(const T* arr, size_t size)
		:_array(nullptr), _vec_size(0), _vec_capacity(0)
	{
		while (size--)
		{
			push_back(t);
		}
	}

	Myvector(const Myvector<T>& other)
		:_array(nullptr), _vec_size(0), _vec_capacity(0)
	{
		*this = other;
	}

	Myvector<T> operator= (const Myvector<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		clear();
		_vec_size = rhs.size();
		_vec_capacity = rhs.capacity();
		_array = new T[_vec_capacity];
		for (size_t idx = 0; idx < _vec_size; ++idx)
		{
			array[idx] = rhs[idx];
		}
		return *this;
	}

	~Myvector()
	{
		clean();
	}

	/* member functions below*/

	T& operator[] (size_t pos)
	{
		assert(pos < _vec_size);
		return array[pos];
	}

	size_t size() const
	{
		reurn _vec_size;
	}

	size_t capacity() const
	{
		return _vec_capacity;
	}

	bool empty() const
	{
		return _vec_size == 0;
	}

	void push_back(const T& element)
	{
		insert_after(_vec_size - 1, element);
	}

	void push_front(const T& element)
	{
		insert_before(0, element);
	}

	void insert_after(size_t pos, const T& element)
	{
		insert_before(pos + 1, element);
	}

	void insert_before(size_t pos, const T& element)
	{
		if (_vec_size == _vec_capacity)
		{
			T* old_array = array;
			_vec_capacity += WALK_LENGTH;
			_array = allocator(_vec_capacity);
			for (size_t idx = 0; idx < _vec_size; ++idx)
			{
				_array[idx] = old_array[idx];
			}
			deallocator(old_array);
		}
		for (size_t idx = _vec_size++; idx > pos; --idx)
		{
			_array[idx] = _array[idx - 1];
		}
		_array[pos] = element;
	}

	void earse(size_t pos)
	{
		assert(pos < _vec_size);
		--_vec_size;
		for (size_t idx = pos; idx < _vec_size; ++idx)
		{
			_array[idx] = _array[idx + 1];
		}
	}

	void clear()
	{
		deallocator(_array);
		_array = nullptr;
		_vec_size = 0;
		_vec_capacity = 0;
	}

private:
	T* allocator(size_t vec_size)
	{
		return new T[vec_size];
	}

	deallocator(T* array)
	{
		if (array != nullptr)
		{
			delete[] array;
		}
	}
private:
	T*		_array;
	size_t	_vec_size;
	size_t	_vec_capacity;
};