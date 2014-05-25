

#include <vector>

using namespace std;


#ifndef _POLYGON_
#define _POLYGON_

class PolygonClass{

private:
	vector<float> polygonPointX, polygonPointY, polygonPointZ;	//�ش� ���� x,y,z ��ǥ
	int numberOfPolygonPoints;	//�� Ŭ������ ������ �����ϴ� ������ ����
	
	float polygonPoint[3]; //x,y,z ��ǥ�� �Ѳ����� ������ �� �ʿ��� �迭

public:

	PolygonClass();

	void setPolygonVectorSize(int size); //���� ������ ����
	void setPolygonPointXYZ(int index, float x, float y, float z); //x,y,z ��ǥ ����
	void setNumberOfPolygonPoints(int number);// �� ������ �̷�� ���� ���� ����

	float* getPolygonPointXYZ(int index);// 3�� ����
	float getPolygonPointX(int index); //x�� ����
	float getPolygonPointY(int index);	//Y�� ����
	float getPolygonPointZ(int index); //Z�� ����

	int getNumberOfPolygonPoints(void);// �� �ٰ����� �̷�� ���� ���� ����
};
	/*
	             i = 0 ; i <NumberOfLinePoints, i++
					float point[3]; 
					point = getPointXYZ(i)
					glVertex3f(point[0], point[1], point[2]);
	*/

#endif
