

/*
아이디 규칙:

xxx001 : 점
xxx002: 선
xxx003: 원
xxx004: 폴리곤

이렇게 하면 좋은점:  %1000을 하여 셀렉된 것의 속성을 빠르게 파악.

xxxxx[001]

 X00000[001]  : 00000 : 해당 속성(점,선, 원, 폴리곤) 의 아이디값  

z: 점, 선, 원, 폴리곤 을 나타냄
	//점

	레이어:
	집합: 0 -> none  1,2,3.. 유저 정의
	아이디:  -> 부여값
	좌표(x,y)
	특성:	(~지점) (~지점)		//점특성 파일에서 부터 읽어옴.  새로 추가하기 가능하도록.
	색상:
	점크기:
	제목:
	설명: (유저가 쓰고 싶은 말)
*/

//이 클래스는 vector 어레이로 어레이 형태로 됨.  0번쨰는 가장 처음부모의 것임을 말함..


#include <vector>
#include <string>
#include "Polygon.h"
using namespace std;


#ifndef _INFORMATION_POLYGON_
#define _INFORMATION_POLYGON_

class InformationPolygon{

public: vector<PolygonClass> polygonClass;				//라인 점 위치 (x,y,z) 저장되어 있는 곳
private:
	// 그려주는데 필요한 정보만 불러와서 저장하고, 기타 속성이나 특성등은 유저가 보고자 할 떄 마다 검색해서 보여주면 된다.
	vector<int>	polygonID;
	vector<float> polygonColorRed, polygonColorGreen, polygonColorBlue; //라인의 색
	vector<float> polygonSize; //라인 사이즈

	//그밖의 변수들

	bool initFlag;
	int lastIndex;//마지막 라인의 index
	int numberOfPolygon;//라인의 갯수

	float polygonColorRGB[3];	//해당 index 의 라인 색상값을 배열로 받길 원할때, 여기에 저장되었다가 lineColorRGB만 리턴한다.

	/*[나중에 추가구현] 삭제한후 취소할 경우를 대비할 임시공간.
		float tempPointXYZ;							//좌표
		float tempPointRGB[3];					   // 색상
		vector<string> tempPointAttribute;			//속성값.  vector 로 한 이유는 제목, 설명 특성 등의 값이 몇개가 되는지 모르기 떄문에..
	*/

public:
	
	
	
	//초기화자
	InformationPolygon();
	InformationPolygon(bool init);

	//add함수
	//일단 파일에서. 아이디는 읽어올겨.. 근데 문제는..라인을 어떻게 추가한다는거...
	//ID 클래스  라인 크기, 라인색갈, 속성 등등등...
	//마우스 우클릭-> Line 클릭 ->  처음 찍으면, ID...(지금 어느 창 기준인지.. 어느 시트인지..) 생성.. ID 발급이 된 상태 라면, recent ID
	void createPolygon(int ID, float x, float y, float z, float red, float green, float blue, float size); //ex) ID 부여, polygonClass 에 x,y,z 값 주고, 
	void addPolygon(int index,float x, float y, float z);	//몇번째 선분의 끝에 추가 되는지. ex) 한번 클릭해서 create 한 다음, 또 클릭시 추가 해 주면 됨../

	//delete 함수

	void deletePolygon(int ID);		//해당 ID 값을 -1 로 바꾸면 됨. 0보다 작거나 같은것은 드로우 안해주면 되기 떄문.


	//set 함수
	void setVectorSize(int size);	//몇개의 선분이 있는지, 또 색, 굵기등의 값이 들어가야 함.
	void setPolygonID(int index,int ID);		//ID 지정
	void setPolygonColor(int index, float red, float green, float blue);		//색상 지정
	void setPolygonSize(int index, float size); //점 크기 지정
	//void setPointNumberOfTempPolygontAttribute(int number);	//이 점이 속성값을 몇개나 지니고 있는지 셋팅
	void setNumberOfPolygon(int number);
	void setLastIndex(int number);

	//get 함수  (-1, -2 는 2가지 방법을 제공하기에 붙임)
	int getPolygonID(int index);	//해당 인덱스의 ID 값 리턴
	int getNumberOfPolygon(void);
	int getLastIndex(void);
		//Polygon 색 리턴 -1
	float getPolygonColorRed(int index);		//빨강
	float getPolygonColorGreen(int index);	//초록
	float getPolygonColorBlue(int index);	//파랑
		//Polygon 색 리턴
	float* getPolygonColor(int index); //해당 인덱스의 색상을 int 배열로 리턴
	float getPolygonSize(int index);
};

#endif
