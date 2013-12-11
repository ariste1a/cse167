#pragma once
#include "Node.h"

class Group :
	public Node
{

public:
	Group();
	~Group();
	void draw(Matrix4) override;
	void addChild(Node*);
	Node* removeChild(int);
};

