

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
using namespace std;


#ifndef _INFORMATION_POINT_
#define _INFORMATION_POINT_

class InformationPoint{

private:


	// 그려주는데 필요한 정보만 불러와서 저장하고, 기타 속성이나 특성등은 유저가 보고자 할 떄 마다 검색해서 보여주면 된다.
	vector<int> pointID;
	vector<float> pointX, pointY, pointZ;	//해당 점의 x,y,z 좌표
	vector<float> pointColorRed, pointColorGreen, pointColorBlue; //해당 점의 색
	vector<float> pointSize; //점의 크기

	//배열값으로 리턴할 때 잠시 값이 저장 되는 곳
	float pointXYZ[3];
	float	 pointColorRGB[3];


	//그밖의 변수들

	bool initFlag;
	int lastIndex;//마지막 점의 index
	int numberOfPoint;//점의 갯수

	 //삭제한후 취소할 경우를 대비할 임시공간.
	float tempPointXYZ;							//좌표
	float tempPointRGB[3];					   // 색상
	vector<string> tempPointAttribute;			//속성값.  vector 로 한 이유는 제목, 설명 특성 등의 값이 몇개가 되는지 모르기 떄문에..


public:
	
	//초기화자
	InformationPoint();
	InformationPoint(bool init);

	//add함수

	void addPoint(int ID,float x, float y, float z, float red, float green, float blue, float size);

	//delete 함수

	void deletePoint(int ID);
	void deleteRecentPoint(void);

	//set 함수
	void setVectorSize(int size);
	void setPointID(int index,int ID);		//ID 지정
	void setPointXYZ(int index, float x, float y, float z); //x,y,z 좌표 지정
	void setPointColor(int index, float red, float green, float blue);		//색상 지정
	void setPointSize(int index, float size); //점 크기 지정
	void setPointNumberOfTempPointAttribute(int number);	//이 점이 속성값을 몇개나 지니고 있는지 셋팅
	void setNumberOfPoint(int number);
	void setLastIndex(int number);

	//get 함수  (-1, -2 는 2가지 방법을 제공하기에 붙임)
	int getPointID(int index);	//해당 인덱스의 ID 값 리턴
	int getNumberOfPoint(void);
	int getLastIndex(void);
		//좌표 리턴 -1
	float getPointX(int index); //해당 인덱스의 x값 리턴
	float getPointY(int index); //해당 인덱스의 y값 리턴
	float getPointZ(int index); //해당 인덱스의 z값 리턴
		//좌표 리턴 -2
	float* getPointXYZ(int index); // 해당 인덱스의 x,y,z 값 float 배열로 리턴
		//point 색 리턴 -1
	float getPointColorRed(int index);		//빨강
	float getPointColorGreen(int index);	//초록
	float getPointColorBlue(int index);	//파랑
		//pint 색 리턴
	float* getPointColor(int index); //해당 인덱스의 색상을 int 배열로 리턴
	float getPointSize(int index);
};



#endif