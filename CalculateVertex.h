
#include <math.h>
#include "NaktaVertex.h"
#include "Face.h"

#ifndef _CALCULATE_VERTEX_
#define _CALCULATE_VERTEX_

class CalculateVertex{

	bool initFlag;

public:
	CalculateVertex();
	CalculateVertex(bool flag);
	~CalculateVertex();

	void setVertexNormalVector(Face* facePointer,NaktaVertex* vertexPointer);	//������ ��ֺ��͸� ����
};

#endif