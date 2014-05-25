
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

	void setVertexNormalVector(Face* facePointer,NaktaVertex* vertexPointer);	//정점의 노멀벡터를 설정
};

#endif