#include <memory>
#include <utility>
#include <iostream>
class BinaryTree
{
public:
	struct node;
	using node_ptr = std::shared_ptr<node>;

	BinaryTree() : root() {}
	BinaryTree(const BinaryTree& src)
		:root(src.root->copy()) {}
	BinaryTree(BinaryTree&& src)
		:root(std::move(src.root->copy())) {}
	BinaryTree& operator= (BinaryTree rhs)
	{
		root.swap(rhs.root);
		return *this;
	}
	~BinaryTree();
	void MorrisPre(node_ptr root);
	void MorrisIn(node_ptr root);
	void MorrisPos(node_ptr root);
private:
	struct node
	{
		int val;
		node_ptr left;
		node_ptr right;

		node() {}
		node(const int data,
			node* left = nullptr, 
			node* right = nullptr)
			:val(data), left(left), right(right) {}
		//node(int&& data,				// int -> T
		//	node* left = nullptr,
		//	node* right = nullptr)
		//	: val(data),left(left),right(right) {}
		node* copy()
		{
			return !this ? nullptr : new node(0, left->copy(), right->copy());
		}
	};

private:
		node_ptr root;
		node_ptr reverseEdge(node_ptr from)
		{
			node_ptr pre = nullptr;
			node_ptr next = nullptr;
			while (from != nullptr)
			{
				next = from->right;
				from->right = pre;
				pre = from;
				from = next;
			}
			return pre;
		}
		void printEdge(node_ptr root)
		{
			node_ptr tail = reverseEdge(root);
			node_ptr cur = tail;
			while (cur != nullptr)
			{
				std::cout << cur->val << std::ends;
				cur = cur->right;
			}
			reverseEdge(tail);
		}

};

 void BinaryTree::MorrisPre(node_ptr root)
 {
	 if (root == nullptr)
	 {
		 return;
	 }
	 node_ptr cur1 = root;
	 node_ptr cur2 = nullptr;
	 while (cur1 != nullptr)
	 {
		 cur2 = cur1->left;
		 if (cur2 != nullptr)
		 {
			 while (cur2->right != nullptr && cur2->right != cur1)
			 {
				 cur2 = cur2->right;
			 }
			 if (cur2->right == nullptr)
			 {
				 cur2->right = cur1;
				 std::cout << cur1->val << std::ends;
				 cur1 = cur1->left;
				 continue;
			 }
			 else
			 {
				 cur2->right = nullptr;
			 }
		 }
		 else
		 {
			 std::cout << cur1->val << std::ends;
		 }
		 cur1 = cur1->right;
	 }	 
 }

 void BinaryTree::MorrisIn(node_ptr root)
 {
	 if (root == nullptr)
	 {
		 return;
	 }
	 node_ptr cur1 = root;
	 node_ptr cur2 = nullptr;
	 while (cur1 != nullptr)
	 {
		 cur2 = cur1->left;
		 if (cur2 != nullptr)
		 {
			 while (cur2->right != nullptr && cur2->right != cur1)
			 {
				 cur2 = cur2->right;
			 }
			 if (cur2->right == nullptr)
			 {
				 cur2->right = cur1;
				 cur1 = cur1->left;
				 continue;
			 }
			 else
			 {
				 cur2->right = nullptr;
			 }
		 }
		 std::cout << cur1->val << std::ends;
		 cur1 = cur1->left;
	 }
 }

 void BinaryTree::MorrisPos(node_ptr root)
 {
	 if (root == nullptr)
	 {
		 return;
	 }
	 node_ptr cur1 = root;
	 node_ptr cur2 = nullptr;
	 while (cur1 != nullptr)
	 {
		 cur2 = cur1->left;
		 if (cur2 != nullptr)
		 {
			 while (cur2->right != nullptr && cur2->right != cur1)
			 {
				 cur2 = cur2->right;
			 }
			 if (cur2->right == nullptr)
			 {
				 cur2->right = cur1;
				 cur1 = cur1->left;
				 continue;
			 }
			 if (cur2->right == cur1)
			 {
				 cur2->right = nullptr;
				 printEdge(cur1->left);
			 }
			 cur1 = cur1->right;
		 }
		 cur1 = cur1->right;
	 }
	 printEdge(root);
 }
