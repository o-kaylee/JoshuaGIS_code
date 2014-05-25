

#include <vector>

using namespace std;


#ifndef _POLYGON_
#define _POLYGON_

class PolygonClass{

private:
	vector<float> polygonPointX, polygonPointY, polygonPointZ;	//해당 점의 x,y,z 좌표
	int numberOfPolygonPoints;	//이 클래스의 라인을 구성하는 점들의 갯수
	
	float polygonPoint[3]; //x,y,z 좌표값 한꺼번에 리턴할 시 필요한 배열

public:

	PolygonClass();

	void setPolygonVectorSize(int size); //벡터 사이즈 설정
	void setPolygonPointXYZ(int index, float x, float y, float z); //x,y,z 좌표 지정
	void setNumberOfPolygonPoints(int number);// 이 선분을 이루는 점의 갯수 지정

	float* getPolygonPointXYZ(int index);// 3점 리턴
	float getPolygonPointX(int index); //x만 리턴
	float getPolygonPointY(int index);	//Y만 리턴
	float getPolygonPointZ(int index); //Z만 리턴

	int getNumberOfPolygonPoints(void);// 이 다각형을 이루는 점의 갯수 리턴
};
	/*
	             i = 0 ; i <NumberOfLinePoints, i++
					float point[3]; 
					point = getPointXYZ(i)
					glVertex3f(point[0], point[1], point[2]);
	*/

#endif
