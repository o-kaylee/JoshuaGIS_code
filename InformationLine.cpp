#include "stdafx.h"
#include "InformationLine.h"


InformationLine::InformationLine(){

}
InformationLine::InformationLine(bool init){
	initFlag = init;
}
void InformationLine::createLine(int ID, float x, float y, float z, float red, float green, float blue, float size){
	
	numberOfLine++;	//���� �� ����
	lastIndex ++;	//������ �ε����� �ϳ� ����
	setVectorSize(lastIndex+1);	//������ ��ŭ �ٽ� ������ ������

	lineID[lastIndex] = ID;		//ID �� �־���
	
								//�������� �־���
	lineColorGreen[lastIndex] = red;
	lineColorGreen[lastIndex] = green;
	lineColorGreen[lastIndex] = blue;
		
	lineSize[lastIndex] = size;	//����� �־���

	lineClass[lastIndex].setNumberOfLinePoints(1);	//���ο� ���ԵǴ� �� ���� 1�� ����
	lineClass[lastIndex].setVectorSize(lineClass[lastIndex].getNumberOfLinePoints());// ���ο� ���ԵǴ� �� ���� ��ŭ ���� ũ�⸦ ���������� 
	//lineClass[lastIndex].setVectorSize(1) �� ������ �ᱹ �̰Ŷ� ����.
	lineClass[lastIndex].setPointXYZ(0,x,y,z);	//�ش� ������ x,y,z �� �־���

}
void InformationLine::addLine(int index,float x, float y, float z){	//�� �Լ��� ���� creatLine �� �̾, ������ �ϼ��ϱ� ���� ���δ�. ��, create  �� �Ŀ� ���̴� �Լ��ν�, �� �Լ� �ܵ����� ������ �ʴ´�. ���� �ᱹ ���⼭ index �� lastIndex+1 �� ���� ���̴�. �ٸ� Ȥ�ø𸣱� ������ �̷��� ����� ���� ��.
																	//���⼭ index�� ����� ���ο� �ش� ���� �߰������� �����ִ� �����󺸸� �ȴ�.

	lineClass[index].setNumberOfLinePoints(lineClass[index].getNumberOfLinePoints()+1);	//���ο� ���� �� ���� �ϳ� ����
	lineClass[index].setVectorSize(lineClass[index].getNumberOfLinePoints());	//�� �ϳ� ����������, �׸�ŭ ���� ��� ũ������������
	lineClass[index].setPointXYZ(lineClass[index].getNumberOfLinePoints()-1,x,y,z);	//array�̹Ƿ� -1�� ���־� �ε����� �ùٸ��� ������ �Ѵ�.
}

//delete �Լ�

void InformationLine::deleteLine(int ID){

	int i ;

	for(i = 0; i <= lastIndex ; i++){	//������ �ε��� ����
		if(lineID[i] == ID){		//ã������ ���� �ִٸ�
			lineID[i] = -1;		//-1�� �ٲ�. ���߿� ���� �� �� ���� ���ϸ� �׸�
			lineSize[i] = 0;	//ũ�⸦ 0���� �Ͽ� ������ �ʵ��� ��... ������ �̰� ���ص� ��. �׷��ٶ� ID�� -1 �ΰ� ��ŵ�ϸ� �Ǳ� ����. �ٸ�, ������ ���� ���
								//������ ID�� ���� -1 ���� �����Ϸ��� if ���� ���� ��.. ���� ���� �׷��ֵ� ����� ���� �Ⱥ��̵��� �ϴ°�. ��, ũ�Ⱑ 0�� ������ �غ��� �˵�.. 

		}
	}

}


//set �Լ�
void InformationLine::setVectorSize(int size){
	//���� ũ�� ����
	lineID.resize(size);
	lineClass.resize(size);				
	lineColorRed.resize(size);
	lineColorGreen.resize(size);
	lineColorBlue.resize(size); 
	lineSize.resize(size);
}
void InformationLine::setLineID(int index,int ID){
	lineID[index] = ID;	
}

void InformationLine::setLineColor(int index, float red, float green, float blue){
	lineColorRed[index] = red;
	lineColorGreen[index] = green;
	lineColorBlue[index] = blue;
}
void InformationLine::setLineSize(int index, float size){
	lineSize[index] = size;
}

void InformationLine::setNumberOfLine(int number){
	numberOfLine = number;
}
void InformationLine::setLastIndex(int number){
		lastIndex = number;
}

//get �Լ�  (-1, -2 �� 2���� ����� �����ϱ⿡ ����)
int InformationLine::getLineID(int index){
	return lineID[index];
}
int InformationLine::getNumberOfLine(void){
	return numberOfLine;
}
int InformationLine::getLastIndex(void){
	return lastIndex;
}
	//Line �� ���� -1
float InformationLine::getLineColorRed(int index){
	return lineColorRed[index];
}
float InformationLine::getLineColorGreen(int index){
	return lineColorGreen[index];
}
float InformationLine::getLineColorBlue(int index){
	return lineColorBlue[index];
}
float* InformationLine::getLineColor(int index){
	lineColorRGB[0] =  lineColorRed[index];
	lineColorRGB[1] =  lineColorGreen[index];
	lineColorRGB[2] =  lineColorBlue[index];
	return lineColorRGB;
}
float InformationLine::getLineSize(int index){
	return lineSize[index];
}