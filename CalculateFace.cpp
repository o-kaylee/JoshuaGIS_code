#include "stdafx.h"
#include "CalculateFace.h"

//9899���� ��...

//198 * row �� +197 �ϸ� ������ index ����.. 9899�� ������ �ε��� �̹Ƿ�, ũ��� 9900����.

//������
CalculateFace::CalculateFace(){

}
CalculateFace::CalculateFace(bool flag){
	initFlag  = flag;
}

//�Ҹ���
CalculateFace::~CalculateFace(){

}

//vertex ������ ������ face ������ ����
void CalculateFace::vertexToFace(Face* facePointer){

		int i, j, row;



		cout<<"[CalculateFace::vertexToFace] Loading"<<endl;

		//    |��
		//    ---     ��� �ﰢ��

		row = 0;

		for(j = 0; j < 4900 ; j+= 100){
			for(i = 0; i < 99 ; i++){
				facePointer->setPointInfo((198*row)+(i*2),i+j,i+j+1,i+j+100);
			}
			row++;
		}

		//   ---
		//   �� |   ��� �ﰢ��   
		row = 0;
		for(j = 100; j < 5000 ; j+= 100){
			for(i = 0; i < 99 ; i++){
				facePointer->setPointInfo((198*row)+1+(i*2),i+j,i+j-99,i+j+1);
			}
			row++;
		}
		

		//cout<<"[CalculateFace::vertexToFace] Finished!"<<endl;

}


//���� ���� �� ��ֶ����� �Ͽ� Face(��)�� �������� ���� �Է��ϴ� ��
void CalculateFace::setFaceNormalVector(Face* facePointer, NaktaVertex* vertexPointer){

	int i=0;
	//���� ����
	int numOfFace = facePointer->getNumOfFace();

	//��������
	float x,y,z;
	//���� ũ��
	float vectorSize;

	//�� 1, ��2, ��3 �� x,y,z
	float x1, y1, z1;
	float x2, y2, z2;
	float x3, y3, z3;

	//�� 1,2,3 �� �̿��� ����.
		//v1:  �� 1-> ��2 ����
	float v1x, v1y, v1z;
		//v2: �� 1 -> ��3 ����
	float v2x, v2y, v2z;


	//���� ��� �� ��ֶ�����, �׸��� ��������

	
		cout<<"[CalculateFace::setFaceNormalVector] Loading"<<endl;


	for(i = 0 ; i < numOfFace ; i++){
		//��1
		x1 =  vertexPointer->getVertexX(facePointer->getPoint1(i));
		y1 =  vertexPointer->getVertexY(facePointer->getPoint1(i));
		z1 =  vertexPointer->getVertexZ(facePointer->getPoint1(i));
		//��2
		x2 =  vertexPointer->getVertexX(facePointer->getPoint2(i));
		y2 =  vertexPointer->getVertexY(facePointer->getPoint2(i));
		z2 =  vertexPointer->getVertexZ(facePointer->getPoint2(i));
		//��3
		x3 =  vertexPointer->getVertexX(facePointer->getPoint3(i));
		y3 =  vertexPointer->getVertexY(facePointer->getPoint3(i));
		z3 =  vertexPointer->getVertexZ(facePointer->getPoint3(i));
	
		//v1 ���Ѵ�   p2 - p1
		v1x = x2 - x1;
		v1y = y2 - y1;
		v1z = z2 - z1;
		//v2 ���Ѵ�  p3 - p1
		v2x = x3 - x1;
		v2y = y3 - z1;
		v2z = z3 - z1;

		//���� ���Ѵ�
		x = v1y*v2z - v1z*v2y;
		y = v1z*v2x - v1x*v2z;
		z = v1x*v2y - v1y*v2x;

		//��ֶ����� �Ѵ�
		vectorSize = sqrt(x*x +y*y+z*z);
		x /= vectorSize;
		y /= vectorSize;
		z /= vectorSize;

		//���� �Է�
		facePointer->setNormalVector(i,x,y,z);
	}

	
		cout<<"[CalculateFace::setFaceNormalVector] Finished!"<<endl;

}