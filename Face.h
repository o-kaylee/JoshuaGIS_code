
#ifndef _FACE_H
#define _FACE_H

#include <vector>

using namespace std;

class Face{
	
	
	
private:
	int numOfFace;
	vector<int> point1,point2, point3;	//�� ���� �̷�� �� 3���� index �� ����.
	vector<float> normalVectorX, normalVectorY, normalVectorZ;	//�� ���� ��ֺ��� X,Y,Z ����

public:
	~Face();
	Face();
	Face(int size);
	int getNumOfFace();

	void init(int size);
	void setPointInfo(int faceIndex, int pointOne, int pointTwo, int pointThree);
	void setNormalVector(int faceIndex, float x, float y, float z);
	void setNumOfFace(int number);


	//1,2,3   x,y,z �� ���� �Լ��� ���� ���� ������ , �ִ��� ������ ���̰��� ��.

	int getPoint1(int faceIndex);	//�ش� ���� 1���� ���� �ε��� �޾ƿ�
	int getPoint2(int faceIndex);	//�ش� ���� 2���� ���� �ε��� �޾ƿ�
	int getPoint3(int faceIndex);	//�ش� ���� 3��° ���� �ε��� �޾ƿ�

	float getNormalVectorX(int faceIndex); //�ش� ���� X���� ��ǥ ����
	float getNormalVectorY(int faceIndex); //�ش� ���� Y���� ��ǥ ����
	float getNormalVectorZ(int faceIndex); //�ش� ���� Z���� ��ǥ ����

};

#endif