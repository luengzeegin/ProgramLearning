// new ���δ�����Ķ������
// length ���鳤��(�������)
Foo *foo = reinterpret_cast<Foo*>(new char[length * sizeof(Foo)]);
for (size_t idx = 0; idx < length; ++idx)
{
	new(foo + idx)Foo(ival);
}

//delete
for (size_t idx = 0; idx < length; ++idx)
{
	foo[idx]->~Foo();
}
delete foo;