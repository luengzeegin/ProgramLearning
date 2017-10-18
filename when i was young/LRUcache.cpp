#include <list>
#include <unordered_map>
#include <assert.h>

using namespace std;

template<typename KEY_T,typename VAL_T>
class LRUcache
{
public:
	LRUcache(size_t cache_size) : _cache_size(cache_size)
	{
	}

	void set(const KEY_T &key, const VAL_T &val)
	{
		auto key_it = _item_map.find(key);
		if (key_it != _item_map.end())
		{
			_item_list.erase(it->second);
			_item_map.erase(it);
		}
		_item_list.push_front(make_pair(key, value));
		_item_map.insert(make_pair(key, _item_list.begin()));
		if (_item_list.size() > _cache_size)
		{
			adjust();
		}
	}

	bool isExist(const KEY_T &key) const
	{
		return (_item_map.count(key) > 0);
	}

	void get(const KEY_T &key)
	{
		assert(isExist(key));
		auto key_it = _item_map.find(key);
		_item_list.splice(_item_list.begin()), _item_list, it->second);
		return it->second;
	}

private:
	list<pair<KEY_T, VAL_T>> _item_list;
	unordered_map<KEY_T, decltype(item_list.begin())> _item_map;
	size_t _cache_size;
	void adjust()
	{
		do
		{
			auto last_it = _item_list.end();
			--last_it;
			_item_map.erase(last_it->first);
			_item_list.pop_back();
		} while (_item_list.size() > _cache_size);
	}
};