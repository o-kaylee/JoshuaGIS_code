
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



	//���� ���콺 ��ư�� ������ �� ����Ǵ� x,y,z ��ǥ
	GLdouble leftClickedCoordinate[3];

	//���� ���콺 ��ư�� ������ �� ����Ǵ� x,y,z ��ǥ
	GLdouble rightClickedCoordinate[3];

	//���콺�� �������� �� ����Ǵ� x,y,z ��ǥ
	GLdouble dragMovedCoordinate[3];


	//��ǥ ����� ���� ��Ʈ���� ���� ���

	GLdouble projection[16];	//projection ��Ʈ���� �������
	GLdouble modelView[16];	//modelView ��Ʈ���� �������
	GLint viewPort[4];		//viewPort ���� ����
	//�����쿡�� Ŭ���� ���� ������� ����� ����
	GLfloat zCursor,winX,winY;

	float viewDirX, viewDirY, viewDirZ ;

	//Private �Լ�.

	void viewToWorld(int xCursor, int yCursor);//leftClick, rightClick, dragMove �Լ��� ���������� ���� �κ��� ������ �ִ� �Լ�.


public:
	
	Coordinate();
	Coordinate(bool init);
	
	//void setViewToWorld(int xCursor, int yCursor);//ȭ����ǥ�� openGL ��ǥ�� ��ȯ�� �ִ� �Լ�
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