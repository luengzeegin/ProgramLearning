{
	// new 带参创造类的多个对象
	// length 数组长度(对象个数)
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
}

{
	// 根据值 / 子串构造类（可以是派生关系）
	// map / factory 模式，其实两种是一个东西，只是IFactory对应class Factory : public IFactory
	map<string, function<shared_ptr<T>()>>;
	注册function -> [=/&]() {return make_shared<T>()};
}

