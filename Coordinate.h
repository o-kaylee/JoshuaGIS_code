
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <stdlib.h>
#include <iostream>

using namespace std;


#ifndef _COORDINATE_
#define _COORDINATE_

class Coordinate{

private:

	bool initFlag;



	//좌측 마우스 버튼이 눌렀을 때 저장되는 x,y,z 좌표
	GLdouble leftClickedCoordinate[3];

	//우측 마우스 버튼이 눌렸을 때 저장되는 x,y,z 좌표
	GLdouble rightClickedCoordinate[3];

	//마우스가 움직였을 때 저장되는 x,y,z 좌표
	GLdouble dragMovedCoordinate[3];


	//좌표 계산을 위한 메트릭스 저장 장소

	GLdouble projection[16];	//projection 매트릭스 저장공간
	GLdouble modelView[16];	//modelView 매트릭스 저장공간
	GLint viewPort[4];		//viewPort 저장 공간
	//윈도우에서 클릭한 곳이 어디진지 저장될 공간
	GLfloat zCursor,winX,winY;

	float viewDirX, viewDirY, viewDirZ ;

	//Private 함수.

	void viewToWorld(int xCursor, int yCursor);//leftClick, rightClick, dragMove 함수에 공통적으로 들어가는 부분을 가지고 있는 함수.


public:
	
	Coordinate();
	Coordinate(bool init);
	
	//void setViewToWorld(int xCursor, int yCursor);//화면좌표를 openGL 좌표로 변환해 주는 함수
	void SelectObjects(GLint x, GLint y, float* matrix);
	void ProcessSelect(GLuint index[64]);
	void leftClick(int xCursor, int yCursor);
	void rightClick(int xCursor, int yCursor);
	void dragMove(int xCursor, int yCursor);

	void setLeftClickedCoordinate(float x,float y,float z);
	void setRightClickedCoordinate(float x,float y,float z);
	void setDragMovedCoordinate(float x,float y, float z);

	GLdouble* getLeftClickedCoordinate(void);
	GLdouble* getRightClickedCoordinate(void);
	GLdouble* getdragMoveCoordinate(void);


};




#endif