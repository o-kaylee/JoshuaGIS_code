

/*
���̵� ��Ģ:

xxx001 : ��
xxx002: ��
xxx003: ��
xxx004: ������

�̷��� �ϸ� ������:  %1000�� �Ͽ� ������ ���� �Ӽ��� ������ �ľ�.

xxxxx[001]

 X00000[001]  : 00000 : �ش� �Ӽ�(��,��, ��, ������) �� ���̵�  

z: ��, ��, ��, ������ �� ��Ÿ��
	//��

	���̾�:
	����: 0 -> none  1,2,3.. ���� ����
	���̵�:  -> �ο���
	��ǥ(x,y)
	Ư��:	(~����) (~����)		//��Ư�� ���Ͽ��� ���� �о��.  ���� �߰��ϱ� �����ϵ���.
	����:
	��ũ��:
	����:
	����: (������ ���� ���� ��)
*/

//�� Ŭ������ vector ��̷� ��� ���·� ��.  0������ ���� ó���θ��� ������ ����..


#include <vector>
#include <string>
using namespace std;


#ifndef _INFORMATION_POINT_
#define _INFORMATION_POINT_

class InformationPoint{

private:


	// �׷��ִµ� �ʿ��� ������ �ҷ��ͼ� �����ϰ�, ��Ÿ �Ӽ��̳� Ư������ ������ ������ �� �� ���� �˻��ؼ� �����ָ� �ȴ�.
	vector<int> pointID;
	vector<float> pointX, pointY, pointZ;	//�ش� ���� x,y,z ��ǥ
	vector<float> pointColorRed, pointColorGreen, pointColorBlue; //�ش� ���� ��
	vector<float> pointSize; //���� ũ��

	//�迭������ ������ �� ��� ���� ���� �Ǵ� ��
	float pointXYZ[3];
	float	 pointColorRGB[3];


	//�׹��� ������

	bool initFlag;
	int lastIndex;//������ ���� index
	int numberOfPoint;//���� ����

	 //�������� ����� ��츦 ����� �ӽð���.
	float tempPointXYZ;							//��ǥ
	float tempPointRGB[3];					   // ����
	vector<string> tempPointAttribute;			//�Ӽ���.  vector �� �� ������ ����, ���� Ư�� ���� ���� ��� �Ǵ��� �𸣱� ������..


public:
	
	//�ʱ�ȭ��
	InformationPoint();
	InformationPoint(bool init);

	//add�Լ�

	void addPoint(int ID,float x, float y, float z, float red, float green, float blue, float size);

	//delete �Լ�

	void deletePoint(int ID);
	void deleteRecentPoint(void);

	//set �Լ�
	void setVectorSize(int size);
	void setPointID(int index,int ID);		//ID ����
	void setPointXYZ(int index, float x, float y, float z); //x,y,z ��ǥ ����
	void setPointColor(int index, float red, float green, float blue);		//���� ����
	void setPointSize(int index, float size); //�� ũ�� ����
	void setPointNumberOfTempPointAttribute(int number);	//�� ���� �Ӽ����� ��� ���ϰ� �ִ��� ����
	void setNumberOfPoint(int number);
	void setLastIndex(int number);

	//get �Լ�  (-1, -2 �� 2���� ����� �����ϱ⿡ ����)
	int getPointID(int index);	//�ش� �ε����� ID �� ����
	int getNumberOfPoint(void);
	int getLastIndex(void);
		//��ǥ ���� -1
	float getPointX(int index); //�ش� �ε����� x�� ����
	float getPointY(int index); //�ش� �ε����� y�� ����
	float getPointZ(int index); //�ش� �ε����� z�� ����
		//��ǥ ���� -2
	float* getPointXYZ(int index); // �ش� �ε����� x,y,z �� float �迭�� ����
		//point �� ���� -1
	float getPointColorRed(int index);		//����
	float getPointColorGreen(int index);	//�ʷ�
	float getPointColorBlue(int index);	//�Ķ�
		//pint �� ����
	float* getPointColor(int index); //�ش� �ε����� ������ int �迭�� ����
	float getPointSize(int index);
};



#endif