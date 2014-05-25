#include "stdafx.h"
#include "InformationPolygon.h"


InformationPolygon::InformationPolygon(){

}
InformationPolygon::InformationPolygon(bool init){
	initFlag = init;
}
void InformationPolygon::createPolygon(int ID, float x, float y, float z, float red, float green, float blue, float size){
	
	numberOfPolygon++;	//라인 수 증가
	lastIndex ++;	//마지막 인덱스값 하나 증가
	setVectorSize(lastIndex+1);	//증가한 만큼 다시 사이즈 재정의

	polygonID[lastIndex] = ID;		//ID 값 넣어줌
	
								//색상정보 넣어줌
	polygonColorGreen[lastIndex] = red;
	polygonColorGreen[lastIndex] = green;
	polygonColorGreen[lastIndex] = blue;
		
	polygonSize[lastIndex] = size;	//사이즈값 넣어줌

	polygonClass[lastIndex].setNumberOfPolygonPoints(1);	//라인에 포함되는 점 갯수 1개 증가
	polygonClass[lastIndex].setPolygonVectorSize(polygonClass[lastIndex].getNumberOfPolygonPoints());// 라인에 포함되는 점 갯수 만큼 벡터 크기를 증가시켜줌 
	//lineClass[lastIndex].setVectorSize(1) 위 라인은 결국 이거랑 같음.
	polygonClass[lastIndex].setPolygonPointXYZ(0,x,y,z);	//해당 지점에 x,y,z 값 넣어줌

}
void InformationPolygon::addPolygon(int index,float x, float y, float z){	//이 함수는 위에 creatLine 에 이어서, 라인을 완성하기 위해 쓰인다. 즉, create  한 후에 쓰이는 함수로써, 이 함수 단독으론 쓰이지 않는다. 따라서 결국 여기서 index 난 lastIndex+1 로 쓰일 것이다. 다만 혹시모르기 때문에 이렇게 만들어 놓은 것.
																	//여기서 index는 몇번쨰 라인에 해당 점을 추가할지를 정해주는 변수라보면 된다.

	polygonClass[index].setNumberOfPolygonPoints(polygonClass[index].getNumberOfPolygonPoints()+1);	//라인에 들어가는 점 숫자 하나 증가
	polygonClass[index].setPolygonVectorSize(polygonClass[index].getNumberOfPolygonPoints());	//점 하나 증가됐으니, 그만큼 벡터 어레이 크기증가시켜줌
	polygonClass[index].setPolygonPointXYZ(polygonClass[index].getNumberOfPolygonPoints()-1,x,y,z);	//array이므로 -1을 해주어 인덱스가 올바르게 들어가도록 한다.
}

//delete 함수

void InformationPolygon::deletePolygon(int ID){

	int i ;

	for(i = 0; i <= lastIndex ; i++){	//마지막 인덱스 까지
		if(polygonID[i] == ID){		//찾으려는 것이 있다면
			polygonID[i] = -1;		//-1로 바꿈. 나중에 저장 할 때 저장 안하면 그만
			polygonSize[i] = 0;	//크기를 0으로 하여 보이지 않도록 함... 솔직히 이건 안해도 됨. 그려줄때 ID가 -1 인걸 스킵하면 되기 때문. 다만, 라인이 많을 경우
								//각각의 ID에 대해 -1 인지 조사하려면 if 문이 많이 들어감.. 따라서 차라리 그려주되 사용자 눈에 안보이도록 하는것. 단, 크기가 0이 될지는 해봐야 알듯.. 

		}
	}

}


//set 함수
void InformationPolygon::setVectorSize(int size){
	//벡터 크기 조정
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

//get 함수  (-1, -2 는 2가지 방법을 제공하기에 붙임)
int InformationPolygon::getPolygonID(int index){
	return polygonID[index];
}
int InformationPolygon::getNumberOfPolygon(void){
	return numberOfPolygon;
}
int InformationPolygon::getLastIndex(void){
	return lastIndex;
}
	//Line 색 리턴 -1
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