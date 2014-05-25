
#include <vector>

using namespace std;


#ifndef _LINE_
#define _LINE_

class Line{

private:
	vector<float> pointX, pointY, pointZ;	//해당 점의 x,y,z 좌표
	int numberOfLinePoints;	//이 클래스의 라인을 구성하는 점들의 갯수
	
	float points[3]; //x,y,z 좌표값 한꺼번에 리턴할 시 필요한 배열

public:

	Line();

	void setVectorSize(int size); //벡터 사이즈 설정
	void setPointXYZ(int index, float x, float y, float z); //x,y,z 좌표 지정
	void setNumberOfLinePoints(int number);// 이 선분을 이루는 점의 갯수 지정

	float* getPointXYZ(int index);// 3점 리턴
	float getPointX(int index); //x만 리턴
	float getPointY(int index);	//Y만 리턴
	float getPointZ(int index); //Z만 리턴

	int getNumberOfLinePoints(void);// 이 선분을 이루는 점의 갯수 리턴
};
	/*
	             i = 0 ; i <NumberOfLinePoints, i++
					float point[3]; 
					point = getPointXYZ(i)
					glVertex3f(point[0], point[1], point[2]);
	*/

#endif
