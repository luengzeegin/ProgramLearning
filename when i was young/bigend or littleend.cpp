#include <iostream>

using namespace std;

// ´óÐ¡¶Ë×ª»»
inline uint32_t Transfrom(uint32_t origin)
{
	return (((origin & 0xFF000000) >> 24)
		| ((origin & 0xFF0000) >> 8)
		| ((origin & 0xFF00) << 8)
		| ((origin & 0xFF) << 24)
		);
}

bool IsLittleEnd()
{
	static uint32_t a = 0x10000000;
	char b[1] = { a };
	if (!b[0])
	{
		return true;
	}
	else
	{
		return false;
	}
}

union Big_or_little
{
	uint32_t a;
	char b[4];
};

int main()
{
	Big_or_little p;
	cout << "input a hex num" << endl;
	cin >> hex >> p.a;
	uint32_t b1 = static_cast<int> (p.b[0]);
	uint32_t b2 = static_cast<int> (p.b[1]);
	uint32_t b3 = static_cast<int> (p.b[2]);
	uint32_t b4 = static_cast<int> (p.b[3]);
	cout << hex << b1 << endl;
	cout << hex << b2 << endl;
	cout << hex << b3 << endl;
	cout << hex << b4 << endl;
	cout << boolalpha << IsLittleEnd() << endl;
	getchar();
	getchar();
}
