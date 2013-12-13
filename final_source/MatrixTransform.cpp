#include "MatrixTransform.h"

using namespace std;

MatrixTransform::MatrixTransform(Matrix4 M)
{
	this->M = M;
}


MatrixTransform::~MatrixTransform()
{
}

void MatrixTransform::draw(Matrix4 C)
{
	//C.translate(0.5, 0.5, 0.5);// C.multiply(M);
	Matrix4 C_new = C.multiply(M);

	//C_new.print();

	//cout << children.size() << endl;
	for (Node* child : children)
	{
		//cout << "drawing" << endl;
		child->draw(C_new);
	}
}

void MatrixTransform::setM(Matrix4 m)
{
	M = m;
}

Matrix4 MatrixTransform::getM(){
	return M;
}