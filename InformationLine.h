

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
#include "Line.h"
using namespace std;


#ifndef _INFORMATION_LINE_
#define _INFORMATION_LINE_

class InformationLine{

public: vector<Line> lineClass;				//���� �� ��ġ (x,y,z) ����Ǿ� �ִ� ��
private:
	// �׷��ִµ� �ʿ��� ������ �ҷ��ͼ� �����ϰ�, ��Ÿ �Ӽ��̳� Ư������ ������ ������ �� �� ���� �˻��ؼ� �����ָ� �ȴ�.
	vector<int>	lineID;
	vector<float> lineColorRed, lineColorGreen, lineColorBlue; //������ ��
	vector<float> lineSize; //���� ������

	//�׹��� ������

	bool initFlag;
	int lastIndex;//������ ������ index
	int numberOfLine;//������ ����

	float lineColorRGB[3];	//�ش� index �� ���� ������ �迭�� �ޱ� ���Ҷ�, ���⿡ ����Ǿ��ٰ� lineColorRGB�� �����Ѵ�.

	/*[���߿� �߰�����] �������� ����� ��츦 ����� �ӽð���.
		float tempPointXYZ;							//��ǥ
		float tempPointRGB[3];					   // ����
		vector<string> tempPointAttribute;			//�Ӽ���.  vector �� �� ������ ����, ���� Ư�� ���� ���� ��� �Ǵ��� �𸣱� ������..
	*/

public:
	
	
	
	//�ʱ�ȭ��
	InformationLine();
	InformationLine(bool init);

	//add�Լ�
	//�ϴ� ���Ͽ���. ���̵�� �о�ð�.. �ٵ� ������..������ ��� �߰��Ѵٴ°�...
	//ID Ŭ����  ���� ũ��, ���λ���, �Ӽ� ����...
	//���콺 ��Ŭ��-> Line Ŭ�� ->  ó�� ������, ID...(���� ��� â ��������.. ��� ��Ʈ����..) ����.. ID �߱��� �� ���� ���, recent ID
	void createLine(int ID, float x, float y, float z, float red, float green, float blue, float size); //ex) ID �ο�, lineClass �� x,y,z �� �ְ�, 
	void addLine(int index,float x, float y, float z);	//���° ������ ���� �߰� �Ǵ���. ex) �ѹ� Ŭ���ؼ� create �� ����, �� Ŭ���� �߰� �� �ָ� ��../

	//delete �Լ�

	void deleteLine(int ID);		//�ش� ID ���� -1 �� �ٲٸ� ��. 0���� �۰ų� �������� ��ο� �����ָ� �Ǳ� ����.


	//set �Լ�
	void setVectorSize(int size);	//��� ������ �ִ���, �� ��, ������� ���� ���� ��.
	void setLineID(int index,int ID);		//ID ����
	void setLineColor(int index, float red, float green, float blue);		//���� ����
	void setLineSize(int index, float size); //�� ũ�� ����
	//void setPointNumberOfTempLinetAttribute(int number);	//�� ���� �Ӽ����� ��� ���ϰ� �ִ��� ����
	void setNumberOfLine(int number);
	void setLastIndex(int number);

	//get �Լ�  (-1, -2 �� 2���� ����� �����ϱ⿡ ����)
	int getLineID(int index);	//�ش� �ε����� ID �� ����
	int getNumberOfLine(void);
	int getLastIndex(void);
		//Line �� ���� -1
	float getLineColorRed(int index);		//����
	float getLineColorGreen(int index);	//�ʷ�
	float getLineColorBlue(int index);	//�Ķ�
		//Line �� ����
	float* getLineColor(int index); //�ش� �ε����� ������ int �迭�� ����
	float getLineSize(int index);
};

#endif
