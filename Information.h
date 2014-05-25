
#include "InformationPoint.h"
#include "InformationLine.h"
#include "InformationPolygon.h"

#ifndef _INFORMATION_
#define _INFORMATION_


#define NAME_SIZE 64

//�θ�

class Information{

private:
	
	bool initFlag;
	bool parentClickedFlag;
	//char parentName[NAME_SIZE];	//�θ��̸�
	int numberOfChild;			//�ڽ��� ����. �̰��� �˸� ��, ��, ��, �ٰ����� vector ��� �̿� ����

	
	
	vector<bool> clickedChild;							//Ŭ���� �ڽ� ��� ���� ������ ����


	//���⿡ ��0
	//���⿡ ��
	//���⿡ �ٰ���

public:
	vector<InformationPoint> pointClass;				//�迭ó�� ���.   0������ ù��° �ڽ��� ������ �ִ� ������ ����. 1�� �ι��� �ڽ�..
	vector<InformationLine> linesClass;
	vector<InformationPolygon> polygonsClass;			//������ Ŭ����

	//�ʱ�ȭ��
	Information();
	Information(bool init);

	//set �Լ� �� update �Լ�
	void setInformationFromFile(char* fileName);	//���ϸ����κ��� ���� �޾ƿ�..
	void setNumberOfChild(int number);
	void setInformationSize(int number);
	void updateInformationFile(char* fileName); //���� ������Ʈ
	void setIsChildClicked(int index, bool flag);
	void setIsParentClicked(bool flag);  

	int getNumberOfChild(void);		//�ڽĳ���� �� ��ȯ
	bool isChildClicked(int index);		//�ش� index �� �ڽĳ�尡 Ŭ�� �Ǿ����� ���� ����
	bool isParentClicked(void);		//�θ��� Ȱ��ȭ ������ ���� ����
	char* getParentName(void);		//�̸� ��ȯ


	//�׼��� ���� ������ �о����
	//���ο� ���� �����ϱ�		//���ο� ���� ���� �ε��� �ʿ� ex) ���ǰ�� ���̵� 123�������� ������ �����͸� �о����µ�, 124��° ���Ͷ��, 123�̶�� �ε����� ������ �־����..
								//								 ���࿡ ���� �����͸� ������ ���..�� ������ �ȵǰ� ������ ���, �ش� ���̵��� ������ �ְ�, �� ���¿��� ������ �߰��Ͽ��� ��
								//								 ������ �κп� ä�� �ִ� ���� �ƴ϶�, �׳� �ڿ��ٰ� ���� ��Ų��. �׸��� ������ �� ������ ���̵� ���� �����ϰ� ���ܼ� �����ϸ� �ɰ�!! 
	

};


#endif