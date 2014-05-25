#include "stdafx.h"
#include"InformationPoint.h"
#include <iostream>
using namespace std;

//������
InformationPoint::InformationPoint(){

}

InformationPoint::InformationPoint(bool init){
	initFlag = init;
}

//add �Լ�
void InformationPoint::addPoint(int ID,float x, float y, float z, float red, float green, float blue, float size){
	
	numberOfPoint++;//���� ����
	lastIndex++;	//����� �ε��� ����
	//lastIndex = numberOfPoint+2;
	
	setVectorSize(lastIndex+1);//���� �Ҵ�  2 ��ŭ ���� �Ҵ� -> 0,1
	int i = 0;
	/*
	for(i=0; i <= lastIndex; i++){
		cout<<"��� :"<<pointID[i]<<endl;
	}
	*/
	

	pointID[lastIndex] = ID;	//ID�ο�
	
	pointX[lastIndex] = x;		//��ǥ�� �ο�
	pointY[lastIndex] = y;
	pointZ[lastIndex] = z;
	

	pointColorRed[lastIndex] = red;		//���� �ο�
	pointColorGreen[lastIndex] = green;
	pointColorBlue[lastIndex] = blue;

	pointSize[lastIndex] = size;		//��ũ�� �ο�
	
}

void InformationPoint::deleteRecentPoint(void){

	numberOfPoint--;//���� ����
	lastIndex--;	//����� �ε��� ����
	setVectorSize(lastIndex+1);//resize �ؼ� ������ ������ ��������
}
//delete �Լ�

void InformationPoint::deletePoint(int ID){

	int i ;

	for(i = 0; i <= lastIndex ; i++){
		if(pointID[i] == ID){		//ã������ ���� �ִٸ�
			pointID[i] = -1;		//-1�� �ٲ�. ���߿� ���� �� �� ���� ���ϸ� �׸�
			pointSize[i] = 0;	//ũ�⸦ 0���� �Ͽ� ������ �ʵ��� ��

		}
	}

}

//Set �Լ�

void InformationPoint::setVectorSize(int size){

	//������ ����
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


//get �Լ� 

	//ID �� ����
int InformationPoint::getPointID(int index){
	return pointID[index];
}
int InformationPoint::getNumberOfPoint(void){
	return numberOfPoint;
}
int InformationPoint::getLastIndex(void){
	return lastIndex;
}

////////��ǥ ����///////////


	//x��ǥ ����
float InformationPoint::getPointX(int index){
		return pointX[index];

}
	//y��ǥ ����
float InformationPoint::getPointY(int index){

	return pointY[index];
}
	//z��ǥ ����
float InformationPoint::getPointZ(int index){

	return pointZ[index];
}
	//x,y,z �迭�� ����
float* InformationPoint::getPointXYZ(int index){
	
	pointXYZ[0] = pointX[index];
	pointXYZ[1] = pointY[index];
	pointXYZ[2] = pointZ[index];

	return pointXYZ;
}

////////������////////

	//���� ���� ����
float InformationPoint::getPointColorRed(int index){
	
	return pointColorRed[index]; 
}
	//�ʷ� ������
float InformationPoint::getPointColorGreen(int index){

	return pointColorGreen[index];
}
	//�Ķ� ���� ����
float InformationPoint::getPointColorBlue(int index){

	return pointColorBlue[index];
}
	//���� �迭�� ����
float* InformationPoint::getPointColor(int index){

	pointColorRGB[0] = pointColorRed[index];
	pointColorRGB[1] = pointColorGreen[index];
	pointColorRGB[2] = pointColorBlue[index];
		
	return pointColorRGB;
}
float InformationPoint::getPointSize(int index){
	return pointSize[index];
}