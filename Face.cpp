#include "stdafx.h"
#include "Face.h"


//소멸자

Face::~Face(){

}


//초기화
Face::Face(){
	
}

Face::Face(int size){
	
	//점 index 를 가지는 벡터 크기 초기화.
	point1.resize(size);
	point2.resize(size);
	point3.resize(size);

	//노멀벡터 정보를 가지는 벡터 크기 초기화.
	normalVectorX.resize(size);
	normalVectorY.resize(size);
	normalVectorZ.resize(size);

	//면의 갯수 초기화
	numOfFace = size;
}


//면의 갯수 증가
void Face::setNumOfFace(int number){

	numOfFace = number;
}

//면의 갯수 리턴
int Face::getNumOfFace(){
	return numOfFace;
}


//해당 면의 정점정보 입력
void Face::setPointInfo(int faceIndex, int pointOne, int pointTwo, int pointThree){
	
	//몇번째 vertex 와 연결되어 있는지에 대한 정보 입력
	point1[faceIndex] = pointOne;
	point2[faceIndex] = pointTwo;
	point3[faceIndex] = pointThree;

}

//해당 면의 노멀벡터 정보 입력
void Face::setNormalVector(int faceIndex, float x, float y, float z){
	
	//면의 노멀벡터값 설정
	normalVectorX[faceIndex] = x;
	normalVectorY[faceIndex] = y;
	normalVectorZ[faceIndex] = z;
}

//해당 면의 해당 x또는 y또는 z축의 정점 인덱스. 이렇게 점 1,2,3 을 따로 함수로 만든 이유는 속도 향상을 위해서임.
int Face::getPoint1(int faceIndex){
	
	return point1[faceIndex];
}

int Face::getPoint2(int faceIndex){

	return point2[faceIndex];
}

int Face::getPoint3(int faceIndex){

	return point3[faceIndex];
}


//해당 면의 해당축의 좌표 얻어옴. 이렇게 점 x,y,z 을 따로 함수로 만든 이유는 속도 향상을 위해서임.
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
	//점 index 를 가지는 벡터 크기 초기화.
	point1.resize(size);
	point2.resize(size);
	point3.resize(size);

	//노멀벡터 정보를 가지는 벡터 크기 초기화.
	normalVectorX.resize(size);
	normalVectorY.resize(size);
	normalVectorZ.resize(size);

	//면의 갯수 초기화
	numOfFace = size;

}