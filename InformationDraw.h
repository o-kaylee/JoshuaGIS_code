#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <vector>
#include "Information.h"

#define POLYGON_HEIGHT 65.0/2500//65.0/2500

extern float xAngle, yAngle, zAngle;

#ifndef _INFORMATION_DRAW_
#define _INFORMATION_DRAW_
class InformationDraw{

private:

	bool initFlag;
	int numberOfParent;//�θ� ����� ����
	
	
public:
	vector<Information> informationClass;		//�θ��� ��� ���·� ����.
	//�ʱ�ȭ��
	InformationDraw();
	InformationDraw(bool init);
	
	void setNumberOfParent(int number); //�θ����� ���� ����
	void setInformationSize(int size);	//�θ��� ��� ���� ����
	//Ư�� �θ��� �ڽ� �׸���
	void drawInformation(int parentIndex);	//childIndex �� �ʿ����� ���� ������, �ش� index �� clicked �� false �̸� ��¥�� �� �׸��Ƿ� ������.
	int IdGenerator(int parentNumber, int childNumber,int orderNumber, int identifier) ; //id ����
	int getNumberOfParent(void); //�θ����� ���� ����
};



#endif