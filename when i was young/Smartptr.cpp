template<typename SmartPointer,typename Type>
class RefCount
{
	friend SmartPointer;
public:
	RefCount(Type* p)
		:_ptr(p) , _count(1)
	{
		static_assert(p != nullptr);
	}

	~RefCount()
	{
		delete _ptr;
	}
	
private:
	size_t _count;
	Type* _ptr;
};

template<typename Type>
class SmartPtr
{
public:
	SmartPtr(Type* p)
		:_smartptr(new RefCount<SmartPtr,Type>(p))
	{
		static_assert(p != nullptr);
	}

	SmartPtr(const SmartPtr& orig) :_smartptr(orig._smartptr)
	{
		++_smartptr->_count;
	}

	SmartPtr& operator=(const SmartPtr& rhs)
	{
		++rhs._smartptr->_count;
		if (--_smartptr->_count == 0)
		{
			delete _smartptr;
		}
		_smartptr = rhs._smartptr;
		return *this;
	}

	~SmartPtr()
	{
		if (--_smartptr->_count == 0)
		{
			delete _smartptr;
		}
	}
private:
	RefCount<SmartPtr, Type>* _smartptr;
};