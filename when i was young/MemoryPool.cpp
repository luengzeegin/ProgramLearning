#include <vector>

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