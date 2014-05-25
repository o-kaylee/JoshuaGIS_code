#include "stdafx.h"
#include "InformationLine.h"


InformationLine::InformationLine(){

}
InformationLine::InformationLine(bool init){
	initFlag = init;
}
void InformationLine::createLine(int ID, float x, float y, float z, float red, float green, float blue, float size){
	
	numberOfLine++;	//라인 수 증가
	lastIndex ++;	//마지막 인덱스값 하나 증가
	setVectorSize(lastIndex+1);	//증가한 만큼 다시 사이즈 재정의

	lineID[lastIndex] = ID;		//ID 값 넣어줌
	
								//색상정보 넣어줌
	lineColorGreen[lastIndex] = red;
	lineColorGreen[lastIndex] = green;
	lineColorGreen[lastIndex] = blue;
		
	lineSize[lastIndex] = size;	//사이즈값 넣어줌

	lineClass[lastIndex].setNumberOfLinePoints(1);	//라인에 포함되는 점 갯수 1개 증가
	lineClass[lastIndex].setVectorSize(lineClass[lastIndex].getNumberOfLinePoints());// 라인에 포함되는 점 갯수 만큼 벡터 크기를 증가시켜줌 
	//lineClass[lastIndex].setVectorSize(1) 위 라인은 결국 이거랑 같음.
	lineClass[lastIndex].setPointXYZ(0,x,y,z);	//해당 지점에 x,y,z 값 넣어줌

}
void InformationLine::addLine(int index,float x, float y, float z){	//이 함수는 위에 creatLine 에 이어서, 라인을 완성하기 위해 쓰인다. 즉, create  한 후에 쓰이는 함수로써, 이 함수 단독으론 쓰이지 않는다. 따라서 결국 여기서 index 난 lastIndex+1 로 쓰일 것이다. 다만 혹시모르기 때문에 이렇게 만들어 놓은 것.
																	//여기서 index는 몇번쨰 라인에 해당 점을 추가할지를 정해주는 변수라보면 된다.

	lineClass[index].setNumberOfLinePoints(lineClass[index].getNumberOfLinePoints()+1);	//라인에 들어가는 점 숫자 하나 증가
	lineClass[index].setVectorSize(lineClass[index].getNumberOfLinePoints());	//점 하나 증가됐으니, 그만큼 벡터 어레이 크기증가시켜줌
	lineClass[index].setPointXYZ(lineClass[index].getNumberOfLinePoints()-1,x,y,z);	//array이므로 -1을 해주어 인덱스가 올바르게 들어가도록 한다.
}

//delete 함수

void InformationLine::deleteLine(int ID){

	int i ;

	for(i = 0; i <= lastIndex ; i++){	//마지막 인덱스 까지
		if(lineID[i] == ID){		//찾으려는 것이 있다면
			lineID[i] = -1;		//-1로 바꿈. 나중에 저장 할 때 저장 안하면 그만
			lineSize[i] = 0;	//크기를 0으로 하여 보이지 않도록 함... 솔직히 이건 안해도 됨. 그려줄때 ID가 -1 인걸 스킵하면 되기 때문. 다만, 라인이 많을 경우
								//각각의 ID에 대해 -1 인지 조사하려면 if 문이 많이 들어감.. 따라서 차라리 그려주되 사용자 눈에 안보이도록 하는것. 단, 크기가 0이 될지는 해봐야 알듯.. 

		}
	}

}


//set 함수
void InformationLine::setVectorSize(int size){
	//벡터 크기 조정
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

//get 함수  (-1, -2 는 2가지 방법을 제공하기에 붙임)
int InformationLine::getLineID(int index){
	return lineID[index];
}
int InformationLine::getNumberOfLine(void){
	return numberOfLine;
}
int InformationLine::getLastIndex(void){
	return lastIndex;
}
	//Line 색 리턴 -1
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