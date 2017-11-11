template <typename T>
class Array2D
{
public:
	explicit Array2D(std::size_t row, std::size_t col)
		:m_pdata(new T[row * col]), m_nrow(row), m_ncol(col)
	{
	}
	Array2D(const Array2D& src)
		:m_pdata(new T[src.m_nrow * src.m_ncol]), m_nrow(src.m_nrow), m_ncol(src.nmcol)
	{
		std::copy(src.m_pdata, src.m_pdata + m_nrow * m_ncol, m_pdata);
	}
	Array2D(Array2D && src)
		:m_pdata(new T[src.m_nrow * src.m_ncol]), m_nrow(src.m_nrow), m_ncol(src.nmcol)
	{
		delete []src.m_pdata;
	}
	~Array2D()
	{
		delete[] m_pdata;
	}
	Array2D operator= (const Array2D& rhs) = delete;
	T* operator[] (std::size_t index) noexcept
	{
		return m_pdata + m_ncol * index;
	}
private:
	T* m_pdata;
	std::size_t m_nrow;
	std::size_t m_ncol;
};