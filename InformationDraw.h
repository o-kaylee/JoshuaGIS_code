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
	int numberOfParent;//부모 노드의 숫자
	
	
public:
	vector<Information> informationClass;		//부모노드 어레이 형태로 만듬.
	//초기화자
	InformationDraw();
	InformationDraw(bool init);
	
	void setNumberOfParent(int number); //부모노드의 갯수 지정
	void setInformationSize(int size);	//부모노드 어레이 갯수 지정
	//특정 부모의 자식 그리기
	void drawInformation(int parentIndex);	//childIndex 가 필요하지 않은 이유는, 해당 index 의 clicked 가 false 이면 어짜피 안 그리므로 괜찮다.
	int IdGenerator(int parentNumber, int childNumber,int orderNumber, int identifier) ; //id 생성
	int getNumberOfParent(void); //부모노드의 갯수 리턴
};



#endif