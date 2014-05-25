

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
#include "Polygon.h"
using namespace std;


#ifndef _INFORMATION_POLYGON_
#define _INFORMATION_POLYGON_

class InformationPolygon{

public: vector<PolygonClass> polygonClass;				//���� �� ��ġ (x,y,z) ����Ǿ� �ִ� ��
private:
	// �׷��ִµ� �ʿ��� ������ �ҷ��ͼ� �����ϰ�, ��Ÿ �Ӽ��̳� Ư������ ������ ������ �� �� ���� �˻��ؼ� �����ָ� �ȴ�.
	vector<int>	polygonID;
	vector<float> polygonColorRed, polygonColorGreen, polygonColorBlue; //������ ��
	vector<float> polygonSize; //���� ������

	//�׹��� ������

	bool initFlag;
	int lastIndex;//������ ������ index
	int numberOfPolygon;//������ ����

	float polygonColorRGB[3];	//�ش� index �� ���� ������ �迭�� �ޱ� ���Ҷ�, ���⿡ ����Ǿ��ٰ� lineColorRGB�� �����Ѵ�.

	/*[���߿� �߰�����] �������� ����� ��츦 ����� �ӽð���.
		float tempPointXYZ;							//��ǥ
		float tempPointRGB[3];					   // ����
		vector<string> tempPointAttribute;			//�Ӽ���.  vector �� �� ������ ����, ���� Ư�� ���� ���� ��� �Ǵ��� �𸣱� ������..
	*/

public:
	
	
	
	//�ʱ�ȭ��
	InformationPolygon();
	InformationPolygon(bool init);

	//add�Լ�
	//�ϴ� ���Ͽ���. ���̵�� �о�ð�.. �ٵ� ������..������ ��� �߰��Ѵٴ°�...
	//ID Ŭ����  ���� ũ��, ���λ���, �Ӽ� ����...
	//���콺 ��Ŭ��-> Line Ŭ�� ->  ó�� ������, ID...(���� ��� â ��������.. ��� ��Ʈ����..) ����.. ID �߱��� �� ���� ���, recent ID
	void createPolygon(int ID, float x, float y, float z, float red, float green, float blue, float size); //ex) ID �ο�, polygonClass �� x,y,z �� �ְ�, 
	void addPolygon(int index,float x, float y, float z);	//���° ������ ���� �߰� �Ǵ���. ex) �ѹ� Ŭ���ؼ� create �� ����, �� Ŭ���� �߰� �� �ָ� ��../

	//delete �Լ�

	void deletePolygon(int ID);		//�ش� ID ���� -1 �� �ٲٸ� ��. 0���� �۰ų� �������� ��ο� �����ָ� �Ǳ� ����.


	//set �Լ�
	void setVectorSize(int size);	//��� ������ �ִ���, �� ��, ������� ���� ���� ��.
	void setPolygonID(int index,int ID);		//ID ����
	void setPolygonColor(int index, float red, float green, float blue);		//���� ����
	void setPolygonSize(int index, float size); //�� ũ�� ����
	//void setPointNumberOfTempPolygontAttribute(int number);	//�� ���� �Ӽ����� ��� ���ϰ� �ִ��� ����
	void setNumberOfPolygon(int number);
	void setLastIndex(int number);

	//get �Լ�  (-1, -2 �� 2���� ����� �����ϱ⿡ ����)
	int getPolygonID(int index);	//�ش� �ε����� ID �� ����
	int getNumberOfPolygon(void);
	int getLastIndex(void);
		//Polygon �� ���� -1
	float getPolygonColorRed(int index);		//����
	float getPolygonColorGreen(int index);	//�ʷ�
	float getPolygonColorBlue(int index);	//�Ķ�
		//Polygon �� ����
	float* getPolygonColor(int index); //�ش� �ε����� ������ int �迭�� ����
	float getPolygonSize(int index);
};

#endif
