// c++11
class SingleTon
{
public:
	static SingleTon& getInstance()
	{
		static SingleTon* instance;
		return instance;
	}

	SingleTon(const SingleTon& rhs) = delete;
	SingleTon& operator=(const SingleTon& rhs) = delete;
	
private:
	SingleTon();
};

//c++03
// SingleTon_03* SingleTon_03::instance = nullptr;
class SingleTon_03
{
public:
	static SingleTon_03& getInstance()
	{

		if (instance == nullptr)
		{
			lock();
			if (instance == nullptr)
			{
				SingleTon_03* tmp = new SingleTon_03;
				MemoryBarrier();
				instance = tmp;
			}
		}
		return *instance;
	}

private:
	SingleTon_03();
	SingleTon_03(const SingleTon_03& rhs);
	SingleTon_03& operator=(const SingleTon_03& rhs);
	static SingleTon_03* instance;
};