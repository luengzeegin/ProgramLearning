#include <vector>
#include <stack>
#include <set>
#include <memory>


#ifdef __MEMPOOL__

using BYTE = unsigned char;
using std::vector;

class MemPool
{
public:
	explicit MemPool(int ItemSize, int MemBlockSize = 2048)
		: _MemBlockSize(MemBlockSize),
		_ItemSize(ItemSize),
		_mem_Block_Header(nullptr),
		_free_Node_Header(nullptr)
	{
	}
	void* malloc()
	{
		if (_mem_Block_Header == nullptr)
		{
			const int ItemCnt = _MemBlockSize / _ItemSize;
			_MemBlock* new_Block = new _MemBlock;
			new_Block->free_chain[0].prev = nullptr;
			for (int idx = 1; idx < ItemCnt; ++idx)
			{
				new_Block->free_chain[idx].prev = &new_Block->free_chain[idx - 1];
			}
			new_Block->free_chain.shrink_to_fit();
			_free_Node_Header = &new_Block->free_chain[ItemCnt - 1];
			new_Block->prev = _mem_Block_Header;
		}
		void* free_node = reinterpret_cast<void *>(_free_Node_Header);
		_free_Node_Header = _free_Node_Header->prev;
		return free_node;
	}
	void free(void* p)
	{
		_FreeNode* node = reinterpret_cast<_FreeNode*> (p);
		node->prev = _free_Node_Header;
		_free_Node_Header = node;
	}
private:
	const int _MemBlockSize;
	const int _ItemSize;

	struct _FreeNode
	{
		_FreeNode* prev;
		vector<BYTE> data;
	};

	struct _MemBlock
	{
		_MemBlock* prev;
		vector<_FreeNode> free_chain;
	};

	_MemBlock* _mem_Block_Header;
	_FreeNode* _free_Node_Header;
};
#endif // __MEMPOOL__


#ifdef __OBJPOOL_H

constexpr uint32_t DEFAULT_ELENUM_PER_SLICE = 1024;
#define NEWOBJ(T)	new(ObjPool::Create())	T

template<typename Obj>
class ObjPool
{
public:
	Obj* CreateObj()
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj();
		}
		return nullptr;
	}

	template<typename PT1>
	Obj* CreateObj(PT1& param1)
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj(param1);
		}
		return nullptr;
	}

	template<typename PT1, typename PT2>
	Obj* CreateObj(PT1& param1, PT2& param2)
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj(param1, param2);
		}
		return nullptr;
	}

	template<typename PT1, typename PT2, typename PT3>
	Obj* CreateObj(PT1& param1, PT2& param2, PT3& param3)
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj(param1, param2, param3);
		}
		return nullptr;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4>
	Obj* CreateObj(PT1& param1, PT2& param2, PT3& param3, PT4& param4)
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj(param1, param2, param3, param4);
		}
		return nullptr;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4, typename PT5>
	Obj* CreateObj(PT1& param1, PT2& param2, PT3& param3, PT4& param4, PT5& param5)
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj(param1, param2, param3, param4, param5);
		}
		return nullptr;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6>
	Obj* CreateObj(PT1& param1, PT2& param2, PT3& param3, PT4& param4, PT5& param5, PT6& param6)
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj(param1, param2, param3, param4, param5, param6);
		}
		return nullptr;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6, typename PT7>
	Obj* CreateObj(PT1& param1, PT2& param2, PT3& param3, PT4& param4, PT5& param5, PT6& param6, PT7& param7)
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj(param1, param2, param3, param4, param5, param6, param7);
		}
		return nullptr;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6, typename PT7, typename PT8>
	Obj* CreateObj(PT1& param1, PT2& param2, PT3& param3, PT4& param4, PT5& param5, PT6& param6, PT7& param7, PT8& param8)
	{
		if (void* pMem = Create())
		{
			return new(pMem)Obj(param1, param2, param3, param4, param5, param6);
		}
		return nullptr;
	}

	bool Destroy(Obj* obj)
	{
		typename std::set<Obj*>::iterator itr = m_setUsingBlocks.find(obj);
		if (itr != m_setUsingBlocks.end())
		{
			(*itr)->~Obj();
			m_staBlocks.push(*itr);
			m_setUsingBlocks.erase(itr);
			return ture;
		}
		else
		{
			return false;
		}
	}

protected:
	ObjPool(uint32_t numPerSlice = DEFAULT_ELENUM_PER_SLICE)
		: m_nNumPerSlice(numPerSlice)
		, m_nSliceSize(sizeof(Obj) * numPerSlice)
		, vecSlices(m_vecSlices)
		, staBlocks(m_staBlocks)
		, setUsingBlocks(m_setUsingBlocks)
	{
		Enlarge();
	}

	virtual ~ObjPool()
	{
		Reset();
	}

	Obj* Create()
	{
		if (!m_staBlocks.size())
		{
			if (!Enlarge())
			{
				return nullptr;
			}
		}

		Obj* pNewBlock = m_staBlocks.top();
		m_staBlocks.pop();
		m_setUsingBlocks.insert(pNewBlock);
		return pNewBlock;
	}

	void Reset()
	{
		if (m_vecSlices.empty())
		{
			return;
		}

		for (auto usingBlock : m_setUsingBlocks)
		{
			usingBlock->~Obj();
		}

		for (auto slice : m_vecSlices)
		{
			free(slice);
		}

		m_vecSlices.clear();
		while (!m_staBlocks.empty())
		{
			m_staBlocks.pop();
		}
		m_setUsingBlocks.clear();
	}

private:
	bool Enlarge()
	{
		if (void* slice = malloc(m_nSliceSize))
		{
			m_vecSlices.push_back(slice);
			Obj* itr = reinterpret_cast<Obj*>(slice);
			for (size_t idx = 0; idx < m_nNumPerSlice; ++idx)
			{
				m_staBlocks.push(itr + idx);
			}
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	const	uint32_t		m_nNumPerSlice;		// 内存片中对象数量
	const	uint32_t		m_nSliceSize;		// 内存片大小
	std::vector<void*>		m_vecSlices;		// 内存片
	std::stack<Obj*>		m_staBlocks;		// 内存块
	std::set<Obj*>			m_setUsingBlocks;	// 使用中的内存块

protected:
	const	std::vector<void*>&		vecSlices;		// 内存片
	const	std::stack<Obj*>&		staBlocks;		// 内存块
	const	std::set<Obj*>&			setUsingBlocks;	// 使用中的内存块
};

#endif // __OBJPOOL_H
