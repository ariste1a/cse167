#include "Group.h"

Group::Group()
{
}


Group::~Group()
{
	children.clear();
}

void Group::draw(Matrix4 C)
{
	for (Node* child : children)
	{
		child->draw(C);
	}
}

void Group::addChild(Node* n)
{
	children.push_back(n);
}

Node* Group::removeChild(int n)
{
	Node * node = children[n];
	children.erase(children.begin() + n);
	/*for (int i = 0; i < children.size; i++)
	{
		if (children[i]->n)
	}*/
	
	return node;

}
