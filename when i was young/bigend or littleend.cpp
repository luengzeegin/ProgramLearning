#include <iostream>

using namespace std;

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
	getchar();
	getchar();
}