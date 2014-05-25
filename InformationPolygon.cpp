#include "stdafx.h"
#include "InformationPolygon.h"


InformationPolygon::InformationPolygon(){

}
InformationPolygon::InformationPolygon(bool init){
	initFlag = init;
}
void InformationPolygon::createPolygon(int ID, float x, float y, float z, float red, float green, float blue, float size){
	
	numberOfPolygon++;	//���� �� ����
	lastIndex ++;	//������ �ε����� �ϳ� ����
	setVectorSize(lastIndex+1);	//������ ��ŭ �ٽ� ������ ������

	polygonID[lastIndex] = ID;		//ID �� �־���
	
								//�������� �־���
	polygonColorGreen[lastIndex] = red;
	polygonColorGreen[lastIndex] = green;
	polygonColorGreen[lastIndex] = blue;
		
	polygonSize[lastIndex] = size;	//����� �־���

	polygonClass[lastIndex].setNumberOfPolygonPoints(1);	//���ο� ���ԵǴ� �� ���� 1�� ����
	polygonClass[lastIndex].setPolygonVectorSize(polygonClass[lastIndex].getNumberOfPolygonPoints());// ���ο� ���ԵǴ� �� ���� ��ŭ ���� ũ�⸦ ���������� 
	//lineClass[lastIndex].setVectorSize(1) �� ������ �ᱹ �̰Ŷ� ����.
	polygonClass[lastIndex].setPolygonPointXYZ(0,x,y,z);	//�ش� ������ x,y,z �� �־���

}
void InformationPolygon::addPolygon(int index,float x, float y, float z){	//�� �Լ��� ���� creatLine �� �̾, ������ �ϼ��ϱ� ���� ���δ�. ��, create  �� �Ŀ� ���̴� �Լ��ν�, �� �Լ� �ܵ����� ������ �ʴ´�. ���� �ᱹ ���⼭ index �� lastIndex+1 �� ���� ���̴�. �ٸ� Ȥ�ø𸣱� ������ �̷��� ����� ���� ��.
																	//���⼭ index�� ����� ���ο� �ش� ���� �߰������� �����ִ� �����󺸸� �ȴ�.

	polygonClass[index].setNumberOfPolygonPoints(polygonClass[index].getNumberOfPolygonPoints()+1);	//���ο� ���� �� ���� �ϳ� ����
	polygonClass[index].setPolygonVectorSize(polygonClass[index].getNumberOfPolygonPoints());	//�� �ϳ� ����������, �׸�ŭ ���� ��� ũ������������
	polygonClass[index].setPolygonPointXYZ(polygonClass[index].getNumberOfPolygonPoints()-1,x,y,z);	//array�̹Ƿ� -1�� ���־� �ε����� �ùٸ��� ������ �Ѵ�.
}

//delete �Լ�

void InformationPolygon::deletePolygon(int ID){

	int i ;

	for(i = 0; i <= lastIndex ; i++){	//������ �ε��� ����
		if(polygonID[i] == ID){		//ã������ ���� �ִٸ�
			polygonID[i] = -1;		//-1�� �ٲ�. ���߿� ���� �� �� ���� ���ϸ� �׸�
			polygonSize[i] = 0;	//ũ�⸦ 0���� �Ͽ� ������ �ʵ��� ��... ������ �̰� ���ص� ��. �׷��ٶ� ID�� -1 �ΰ� ��ŵ�ϸ� �Ǳ� ����. �ٸ�, ������ ���� ���
								//������ ID�� ���� -1 ���� �����Ϸ��� if ���� ���� ��.. ���� ���� �׷��ֵ� ����� ���� �Ⱥ��̵��� �ϴ°�. ��, ũ�Ⱑ 0�� ������ �غ��� �˵�.. 

		}
	}

}


//set �Լ�
void InformationPolygon::setVectorSize(int size){
	//���� ũ�� ����
	polygonID.resize(size);
	polygonClass.resize(size);				
	polygonColorRed.resize(size);
	polygonColorGreen.resize(size);
	polygonColorBlue.resize(size); 
	polygonSize.resize(size);
}
void InformationPolygon::setPolygonID(int index,int ID){
	polygonID[index] = ID;	
}

void InformationPolygon::setPolygonColor(int index, float red, float green, float blue){
	polygonColorRed[index] = red;
	polygonColorGreen[index] = green;
	polygonColorBlue[index] = blue;
}
void InformationPolygon::setPolygonSize(int index, float size){
	polygonSize[index] = size;
}

void InformationPolygon::setNumberOfPolygon(int number){
	numberOfPolygon = number;
}
void InformationPolygon::setLastIndex(int number){
		lastIndex = number;
}

//get �Լ�  (-1, -2 �� 2���� ����� �����ϱ⿡ ����)
int InformationPolygon::getPolygonID(int index){
	return polygonID[index];
}
int InformationPolygon::getNumberOfPolygon(void){
	return numberOfPolygon;
}
int InformationPolygon::getLastIndex(void){
	return lastIndex;
}
	//Line �� ���� -1
float InformationPolygon::getPolygonColorRed(int index){
	return polygonColorRed[index];
}
float InformationPolygon::getPolygonColorGreen(int index){
	return polygonColorGreen[index];
}
float InformationPolygon::getPolygonColorBlue(int index){
	return polygonColorBlue[index];
}
float* InformationPolygon::getPolygonColor(int index){
	polygonColorRGB[0] =  polygonColorRed[index];
	polygonColorRGB[1] =  polygonColorGreen[index];
	polygonColorRGB[2] =  polygonColorBlue[index];
	return polygonColorRGB;
}
float InformationPolygon::getPolygonSize(int index){
	return polygonSize[index];
}