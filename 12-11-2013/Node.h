#pragma once
#include <vector>
#include "Matrix4.h"

class Node
{
protected:
	Node* parent;
	std::vector<Node*> children;

public:
	Node();
	~Node();
	std::vector<Node*> getChildren();
	virtual void draw(Matrix4) = 0;


};

