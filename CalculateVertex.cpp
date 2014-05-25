#include "stdafx.h"
#include "CalculateVertex.h"



CalculateVertex::CalculateVertex(){

}
CalculateVertex::CalculateVertex(bool flag){

	initFlag = flag;
}
CalculateVertex::~CalculateVertex(){

}

void CalculateVertex::setVertexNormalVector(Face* facePointer,NaktaVertex* vertexPointer){

	int i, numOfFace, numOfVertex;
	float x,y,z;
	int count;
	float fCount, normalizer;
	int vertexIndex1,vertexIndex2,vertexIndex3;
	
	
	numOfFace  = facePointer->getNumOfFace();

	//면의 해당 점에 1,2,3 에서
	//1에도 더하고 증가, 2에도 더하고 증가, 3에도 더하고 증가..


	cout<<"[CalculateVertex::setVertexNormalVector]faceVector->vertexVector..."<<endl;

	for(i = 0; i < numOfFace ; i++){

		//면의 1번쨰 점
		vertexIndex1 = facePointer->getPoint1(i);

		//예전값
		x = vertexPointer->getVertexNormalVectorX(vertexIndex1);
		y = vertexPointer->getVertexNormalVectorY(vertexIndex1);
		z = vertexPointer->getVertexNormalVectorZ(vertexIndex1);
		count = vertexPointer->getVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex1);

		//갱신		
		vertexPointer->setVertexNormalVector(vertexIndex1,x+facePointer->getNormalVectorX(i),y+facePointer->getNormalVectorY(i),z+facePointer->getNormalVectorZ(i));
		vertexPointer->setVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex1,count+1);
		
		//면의 2번째 점
		vertexIndex2 = facePointer->getPoint2(i);

		//예전값
		x = vertexPointer->getVertexNormalVectorX(vertexIndex2);
		y = vertexPointer->getVertexNormalVectorY(vertexIndex2);
		z = vertexPointer->getVertexNormalVectorZ(vertexIndex2);
		count = vertexPointer->getVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex2);

		//갱신		
		vertexPointer->setVertexNormalVector(vertexIndex2,x+facePointer->getNormalVectorX(i),y+facePointer->getNormalVectorY(i),z+facePointer->getNormalVectorZ(i));
		vertexPointer->setVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex2,count+1);

		//면의 3번째 점
		vertexIndex3 = facePointer->getPoint3(i);

		//예전값
		x = vertexPointer->getVertexNormalVectorX(vertexIndex3);
		y = vertexPointer->getVertexNormalVectorY(vertexIndex3);
		z = vertexPointer->getVertexNormalVectorZ(vertexIndex3);
		count = vertexPointer->getVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex3);
	
		//갱신		
		vertexPointer->setVertexNormalVector(vertexIndex3,x+facePointer->getNormalVectorX(i),y+facePointer->getNormalVectorY(i),z+facePointer->getNormalVectorZ(i));
		vertexPointer->setVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex3,count+1);

	}

		cout<<"[CalculateVertex::setVertexNormalVector]faceVector->vertexVector finished!"<<endl;

	numOfVertex = vertexPointer->getNumOfVertex();


	cout<<"[CalculateVertex::setVertexNormalVector] normalizing...."<<endl;

	//평균값 넣어주고, 노멀라이즈
	for(i = 0; i < numOfVertex; i ++){
		//현재값
		x = vertexPointer->getVertexNormalVectorX(i);
		y = vertexPointer->getVertexNormalVectorY(i);
		z = vertexPointer->getVertexNormalVectorZ(i);
		count = vertexPointer->getVertexNormalVectorNumberOfRelatedFaceVector(i);
		
		fCount = (float)count;

		//평균값으로 바꾸고
		x /= fCount;
		y /= fCount;
		z /= fCount;

		//노멀라이즈
		normalizer = sqrt(x*x+y*y+z*z);	
		x /= normalizer;
		y /= normalizer;
		z /= normalizer;
		
		vertexPointer->setVertexNormalVector(i,x,y,z);	//최종값으로 갱신

	}

	cout<<"[ CalculateVertex::setVertexNormalVector] normalizing finished! "<<endl;

}