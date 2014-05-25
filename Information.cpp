#include "stdafx.h"
#include "Information.h"

Information::Information(){

}
Information::Information(bool init){
	initFlag = init;
}

//set 함수 및 update 함수
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

//get함수 및 자식/ 부모가 클릭되었는지 나타내는 함수
int Information::getNumberOfChild(void){
	return numberOfChild;
}
bool Information::isChildClicked(int index){

	return clickedChild[index];
}
bool Information::isParentClicked(void){

	return parentClickedFlag;
}

//부모 이름 반환
char* Information::getParentName(void){
	return "thisIsNotAvailable";//사용하지 말것 사용안함.
}