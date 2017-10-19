#include <string>
#include <utility>

class  Mystring
{
public:
	Mystring(const char* str = nullptr);
	~Mystring() noexcept;
	Mystring(const Mystring& rhs);
	Mystring(Mystring&& rhs) noexcept;
	Mystring& operator= (const Mystring&);
	Mystring operator+ (const Mystring&);
	bool operator== (const Mystring&);
	void swap(Mystring& rhs);
	size_t size() const;
	const char* c_str() const;
private:
	char* _data;
};


Mystring::Mystring(const char *str)
{
	if (str == nullptr)
	{
		_data = new char[1];
		*_data = '\0';
	}
	else
	{
		int length = strlen(str);
		_data = new char[length + 1];
		strcpy(_data, str);
	}
}

Mystring::Mystring(const Mystring& other)
	:_data(new char[other.size() + 1])
{
	strcpy(_data, other._data);
}

Mystring::Mystring(const Mystring& other) // delegate ctor
	: Mystring(other._data)
{
}

Mystring::Mystring(Mystring&& rhs) noexcept
	: _data(std::move(rhs._data))
{
	rhs._data = nullptr;
}

Mystring::~Mystring() noexcept
{
		delete[] _data;
}


Mystring& Mystring::operator= (const Mystring& rhs) 
{
	if (this != &rhs)
	{
		Mystring tmp(rhs);
		swap(tmp);
	}
	return *this;
}

// Mystring& operator= (Mystring rhs) c++11
//{
//	swap(tmp);
//	return *this;
//}


Mystring Mystring::operator+ (const Mystring& rhs)
{
	Mystring newString;
	if (rhs._data == nullptr)
	{
		newString = *this;
	}
	else if (_data == nullptr)
	{
		newString = rhs;
	}
	else
	{
		newString._data = new char[rhs.size() + this->size() + 1];
		strcpy(newString._data, _data);
		strcat(newString._data, rhs._data);
	}
	return newString;
}

bool Mystring::operator== (const Mystring& rhs)
{
	if (this->size() != rhs.size())
	{
		return false;
	}
	else
	{
		return strcmp(_data, rhs._data) ? false : true;
	}
}

void Mystring::swap(Mystring& rhs)
{
	std::swap(_data, rhs._data);
}

size_t Mystring::size() const
{
	return strlen(_data);
}

const char* Mystring::c_str() const
{
	return _data;
}