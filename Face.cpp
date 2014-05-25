#include "stdafx.h"
#include "Face.h"


//�Ҹ���

Face::~Face(){

}


//�ʱ�ȭ
Face::Face(){
	
}

Face::Face(int size){
	
	//�� index �� ������ ���� ũ�� �ʱ�ȭ.
	point1.resize(size);
	point2.resize(size);
	point3.resize(size);

	//��ֺ��� ������ ������ ���� ũ�� �ʱ�ȭ.
	normalVectorX.resize(size);
	normalVectorY.resize(size);
	normalVectorZ.resize(size);

	//���� ���� �ʱ�ȭ
	numOfFace = size;
}


//���� ���� ����
void Face::setNumOfFace(int number){

	numOfFace = number;
}

//���� ���� ����
int Face::getNumOfFace(){
	return numOfFace;
}


//�ش� ���� �������� �Է�
void Face::setPointInfo(int faceIndex, int pointOne, int pointTwo, int pointThree){
	
	//���° vertex �� ����Ǿ� �ִ����� ���� ���� �Է�
	point1[faceIndex] = pointOne;
	point2[faceIndex] = pointTwo;
	point3[faceIndex] = pointThree;

}

//�ش� ���� ��ֺ��� ���� �Է�
void Face::setNormalVector(int faceIndex, float x, float y, float z){
	
	//���� ��ֺ��Ͱ� ����
	normalVectorX[faceIndex] = x;
	normalVectorY[faceIndex] = y;
	normalVectorZ[faceIndex] = z;
}

//�ش� ���� �ش� x�Ǵ� y�Ǵ� z���� ���� �ε���. �̷��� �� 1,2,3 �� ���� �Լ��� ���� ������ �ӵ� ����� ���ؼ���.
int Face::getPoint1(int faceIndex){
	
	return point1[faceIndex];
}

int Face::getPoint2(int faceIndex){

	return point2[faceIndex];
}

int Face::getPoint3(int faceIndex){

	return point3[faceIndex];
}


//�ش� ���� �ش����� ��ǥ ����. �̷��� �� x,y,z �� ���� �Լ��� ���� ������ �ӵ� ����� ���ؼ���.
float Face::getNormalVectorX(int faceIndex){

	return normalVectorX[faceIndex];
}

float Face::getNormalVectorY(int faceIndex){

	return normalVectorY[faceIndex];
}
float Face::getNormalVectorZ(int faceIndex){

	return normalVectorZ[faceIndex];
}
void Face::init(int size){
	//�� index �� ������ ���� ũ�� �ʱ�ȭ.
	point1.resize(size);
	point2.resize(size);
	point3.resize(size);

	//��ֺ��� ������ ������ ���� ũ�� �ʱ�ȭ.
	normalVectorX.resize(size);
	normalVectorY.resize(size);
	normalVectorZ.resize(size);

	//���� ���� �ʱ�ȭ
	numOfFace = size;

}