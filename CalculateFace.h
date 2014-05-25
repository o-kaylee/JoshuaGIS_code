
#include <math.h>

#include "Face.h"
#include "NaktaVertex.h"


#ifndef _CALCULATE_FACE_
#define _CALCULATE_FACE_


class CalculateFace{

private: 
	bool initFlag;

public:
	CalculateFace();
	CalculateFace(bool flag);
	~CalculateFace();
	void vertexToFace(Face* facePointer);
	void setFaceNormalVector(Face* facePointer, NaktaVertex* vertexPointer);
};


#endif