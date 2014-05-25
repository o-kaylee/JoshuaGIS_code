
#ifndef _FACE_H
#define _FACE_H

#include <vector>

using namespace std;

class Face{
	
	
	
private:
	int numOfFace;
	vector<int> point1,point2, point3;	//이 면을 이루는 점 3개의 index 를 저장.
	vector<float> normalVectorX, normalVectorY, normalVectorZ;	//이 면의 노멀벡터 X,Y,Z 저장

public:
	~Face();
	Face();
	Face(int size);
	int getNumOfFace();

	void init(int size);
	void setPointInfo(int faceIndex, int pointOne, int pointTwo, int pointThree);
	void setNormalVector(int faceIndex, float x, float y, float z);
	void setNumOfFace(int number);


	//1,2,3   x,y,z 에 대한 함수를 따로 만든 이유는 , 최대한 연산을 줄이고자 함.

	int getPoint1(int faceIndex);	//해당 면의 1번쨰 정점 인덱스 받아옴
	int getPoint2(int faceIndex);	//해당 면의 2번쩨 정점 인덱스 받아옴
	int getPoint3(int faceIndex);	//해당 면의 3번째 정점 인덱스 받아옴

	float getNormalVectorX(int faceIndex); //해당 면의 X축의 좌표 얻어옴
	float getNormalVectorY(int faceIndex); //해당 면의 Y축의 좌표 얻어옴
	float getNormalVectorZ(int faceIndex); //해당 면의 Z축의 좌표 얻어옴

};

#endif