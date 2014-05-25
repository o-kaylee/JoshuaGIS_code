#include "stdafx.h"
#include"InformationPoint.h"
#include <iostream>
using namespace std;

//생성자
InformationPoint::InformationPoint(){

}

InformationPoint::InformationPoint(bool init){
	initFlag = init;
}

//add 함수
void InformationPoint::addPoint(int ID,float x, float y, float z, float red, float green, float blue, float size){
	
	numberOfPoint++;//숫자 증가
	lastIndex++;	//저장될 인덱스 증가
	//lastIndex = numberOfPoint+2;
	
	setVectorSize(lastIndex+1);//공간 할당  2 만큼 공간 할당 -> 0,1
	int i = 0;
	/*
	for(i=0; i <= lastIndex; i++){
		cout<<"출력 :"<<pointID[i]<<endl;
	}
	*/
	

	pointID[lastIndex] = ID;	//ID부여
	
	pointX[lastIndex] = x;		//좌표값 부여
	pointY[lastIndex] = y;
	pointZ[lastIndex] = z;
	

	pointColorRed[lastIndex] = red;		//색상값 부여
	pointColorGreen[lastIndex] = green;
	pointColorBlue[lastIndex] = blue;

	pointSize[lastIndex] = size;		//점크기 부여
	
}

void InformationPoint::deleteRecentPoint(void){

	numberOfPoint--;//숫자 감소
	lastIndex--;	//저장될 인덱스 감소
	setVectorSize(lastIndex+1);//resize 해서 마지막 정보들 날려버림
}
//delete 함수

void InformationPoint::deletePoint(int ID){

	int i ;

	for(i = 0; i <= lastIndex ; i++){
		if(pointID[i] == ID){		//찾으려는 것이 있다면
			pointID[i] = -1;		//-1로 바꿈. 나중에 저장 할 때 저장 안하면 그만
			pointSize[i] = 0;	//크기를 0으로 하여 보이지 않도록 함

		}
	}

}

//Set 함수

void InformationPoint::setVectorSize(int size){

	//사이즈 조정
	pointID.resize(size);
	pointX.resize(size);
	pointY.resize(size);
	pointZ.resize(size);

	pointColorRed.resize(size);
	pointColorGreen.resize(size);
	pointColorBlue.resize(size);

	pointSize.resize(size);
}
void InformationPoint::setPointID(int index,int ID){
	
	pointID[index] = ID;
}
void InformationPoint::setPointXYZ(int index, float x, float y, float z){
	
	pointX[index] = x;
	pointY[index] = y;
	pointZ[index] = z;
}
void InformationPoint::setPointColor(int index, float red, float green, float blue){

	pointColorRed[index] = red;
	pointColorGreen[index] = green;
	pointColorBlue[index] = blue;
}
void InformationPoint::setPointSize(int index, float size){
	pointSize[index] = size;
}
void InformationPoint::setPointNumberOfTempPointAttribute(int number){
	tempPointAttribute.resize(number);
}
void InformationPoint::setNumberOfPoint(int number){
		numberOfPoint = number;
}
void InformationPoint::setLastIndex(int number){
		lastIndex = number;
}


//get 함수 

	//ID 값 리턴
int InformationPoint::getPointID(int index){
	return pointID[index];
}
int InformationPoint::getNumberOfPoint(void){
	return numberOfPoint;
}
int InformationPoint::getLastIndex(void){
	return lastIndex;
}

////////좌표 리턴///////////


	//x좌표 리턴
float InformationPoint::getPointX(int index){
		return pointX[index];

}
	//y좌표 리턴
float InformationPoint::getPointY(int index){

	return pointY[index];
}
	//z좌표 리턴
float InformationPoint::getPointZ(int index){

	return pointZ[index];
}
	//x,y,z 배열로 리턴
float* InformationPoint::getPointXYZ(int index){
	
	pointXYZ[0] = pointX[index];
	pointXYZ[1] = pointY[index];
	pointXYZ[2] = pointZ[index];

	return pointXYZ;
}

////////색상리턴////////

	//빨강 색상 리턴
float InformationPoint::getPointColorRed(int index){
	
	return pointColorRed[index]; 
}
	//초록 색상리턴
float InformationPoint::getPointColorGreen(int index){

	return pointColorGreen[index];
}
	//파랑 색상 리턴
float InformationPoint::getPointColorBlue(int index){

	return pointColorBlue[index];
}
	//색상 배열로 리턴
float* InformationPoint::getPointColor(int index){

	pointColorRGB[0] = pointColorRed[index];
	pointColorRGB[1] = pointColorGreen[index];
	pointColorRGB[2] = pointColorBlue[index];
		
	return pointColorRGB;
}
float InformationPoint::getPointSize(int index){
	return pointSize[index];
}