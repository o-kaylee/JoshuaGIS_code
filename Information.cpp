#include "stdafx.h"
#include "Information.h"

Information::Information(){

}
Information::Information(bool init){
	initFlag = init;
}

//set �Լ� �� update �Լ�
void Information::setInformationFromFile(char* fileName){
	//ToDo:

}
void Information::setNumberOfChild(int number){
	numberOfChild = number;
}
void Information::setInformationSize(int size){
	clickedChild.resize(size);
	pointClass.resize(size);
	linesClass.resize(size);
	polygonsClass.resize(size);
}
void Information::updateInformationFile(char* fileName){
	//ToDo:
}

void Information::setIsChildClicked(int index, bool flag){
	clickedChild[index] = flag;
}
void Information::setIsParentClicked(bool flag){
	parentClickedFlag  = flag;
}

//get�Լ� �� �ڽ�/ �θ� Ŭ���Ǿ����� ��Ÿ���� �Լ�
int Information::getNumberOfChild(void){
	return numberOfChild;
}
bool Information::isChildClicked(int index){

	return clickedChild[index];
}
bool Information::isParentClicked(void){

	return parentClickedFlag;
}

//�θ� �̸� ��ȯ
char* Information::getParentName(void){
	return "thisIsNotAvailable";//������� ���� ������.
}