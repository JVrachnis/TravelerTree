#ifndef TREENODE_H_
#define TREENODE_H_
#include "TreeFlight.h"
#include "Tree.h"
class TreeNode
{
	friend class Tree;
public:
	TreeNode(const TreeFlight &);
private:
	TreeFlight data; //τα δεδομενα
	TreeNode *rightPtr; // αριστερό node στο Tree
	TreeNode *leftPtr; // δεξί node στο Tree
};
TreeNode::TreeNode(const TreeFlight &info)
	:data(info), rightPtr(0), leftPtr(0) // constructor
{

}
#endif