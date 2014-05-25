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

	//���� �ش� ���� 1,2,3 ����
	//1���� ���ϰ� ����, 2���� ���ϰ� ����, 3���� ���ϰ� ����..


	cout<<"[CalculateVertex::setVertexNormalVector]faceVector->vertexVector..."<<endl;

	for(i = 0; i < numOfFace ; i++){

		//���� 1���� ��
		vertexIndex1 = facePointer->getPoint1(i);

		//������
		x = vertexPointer->getVertexNormalVectorX(vertexIndex1);
		y = vertexPointer->getVertexNormalVectorY(vertexIndex1);
		z = vertexPointer->getVertexNormalVectorZ(vertexIndex1);
		count = vertexPointer->getVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex1);

		//����		
		vertexPointer->setVertexNormalVector(vertexIndex1,x+facePointer->getNormalVectorX(i),y+facePointer->getNormalVectorY(i),z+facePointer->getNormalVectorZ(i));
		vertexPointer->setVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex1,count+1);
		
		//���� 2��° ��
		vertexIndex2 = facePointer->getPoint2(i);

		//������
		x = vertexPointer->getVertexNormalVectorX(vertexIndex2);
		y = vertexPointer->getVertexNormalVectorY(vertexIndex2);
		z = vertexPointer->getVertexNormalVectorZ(vertexIndex2);
		count = vertexPointer->getVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex2);

		//����		
		vertexPointer->setVertexNormalVector(vertexIndex2,x+facePointer->getNormalVectorX(i),y+facePointer->getNormalVectorY(i),z+facePointer->getNormalVectorZ(i));
		vertexPointer->setVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex2,count+1);

		//���� 3��° ��
		vertexIndex3 = facePointer->getPoint3(i);

		//������
		x = vertexPointer->getVertexNormalVectorX(vertexIndex3);
		y = vertexPointer->getVertexNormalVectorY(vertexIndex3);
		z = vertexPointer->getVertexNormalVectorZ(vertexIndex3);
		count = vertexPointer->getVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex3);
	
		//����		
		vertexPointer->setVertexNormalVector(vertexIndex3,x+facePointer->getNormalVectorX(i),y+facePointer->getNormalVectorY(i),z+facePointer->getNormalVectorZ(i));
		vertexPointer->setVertexNormalVectorNumberOfRelatedFaceVector(vertexIndex3,count+1);

	}

		cout<<"[CalculateVertex::setVertexNormalVector]faceVector->vertexVector finished!"<<endl;

	numOfVertex = vertexPointer->getNumOfVertex();


	cout<<"[CalculateVertex::setVertexNormalVector] normalizing...."<<endl;

	//��հ� �־��ְ�, ��ֶ�����
	for(i = 0; i < numOfVertex; i ++){
		//���簪
		x = vertexPointer->getVertexNormalVectorX(i);
		y = vertexPointer->getVertexNormalVectorY(i);
		z = vertexPointer->getVertexNormalVectorZ(i);
		count = vertexPointer->getVertexNormalVectorNumberOfRelatedFaceVector(i);
		
		fCount = (float)count;

		//��հ����� �ٲٰ�
		x /= fCount;
		y /= fCount;
		z /= fCount;

		//��ֶ�����
		normalizer = sqrt(x*x+y*y+z*z);	
		x /= normalizer;
		y /= normalizer;
		z /= normalizer;
		
		vertexPointer->setVertexNormalVector(i,x,y,z);	//���������� ����

	}

	cout<<"[ CalculateVertex::setVertexNormalVector] normalizing finished! "<<endl;

}