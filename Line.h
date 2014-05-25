
#include <vector>

using namespace std;


#ifndef _LINE_
#define _LINE_

class Line{

private:
	vector<float> pointX, pointY, pointZ;	//�ش� ���� x,y,z ��ǥ
	int numberOfLinePoints;	//�� Ŭ������ ������ �����ϴ� ������ ����
	
	float points[3]; //x,y,z ��ǥ�� �Ѳ����� ������ �� �ʿ��� �迭

public:

	Line();

	void setVectorSize(int size); //���� ������ ����
	void setPointXYZ(int index, float x, float y, float z); //x,y,z ��ǥ ����
	void setNumberOfLinePoints(int number);// �� ������ �̷�� ���� ���� ����

	float* getPointXYZ(int index);// 3�� ����
	float getPointX(int index); //x�� ����
	float getPointY(int index);	//Y�� ����
	float getPointZ(int index); //Z�� ����

	int getNumberOfLinePoints(void);// �� ������ �̷�� ���� ���� ����
};
	/*
	             i = 0 ; i <NumberOfLinePoints, i++
					float point[3]; 
					point = getPointXYZ(i)
					glVertex3f(point[0], point[1], point[2]);
	*/

#endif
