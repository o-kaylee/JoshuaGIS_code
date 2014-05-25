#include "stdafx.h"
#include "Coordinate.h"


//�ʱ�ȭ
Coordinate::Coordinate(){

}

Coordinate::Coordinate(bool init){
	initFlag = init;
}


//leftClick, rightClick, dragMove �Լ��� ���������� ���� �κ��� ������ �ִ� �Լ�.

void Coordinate::viewToWorld(int xCursor, int yCursor){
	//������ ������ ������ ������ ��Ʈ���� ������ �޾ƿ´�
	// glPushMatrix();
   glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
   glGetDoublev(GL_PROJECTION_MATRIX,projection);
   glGetIntegerv(GL_VIEWPORT,viewPort);
  //glPopMatrix();
   winX = (float)xCursor;
   winY = (float)viewPort[3]-(float)yCursor;
   glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor); //z ���۰��� ���ϴ� �Լ�
}


//��Ŭ��, ��Ŭ��, �巡�׿� ���� �Լ�

void Coordinate::leftClick(int xCursor, int yCursor){
   
   viewToWorld(xCursor, yCursor);
   gluUnProject(winX,winY,zCursor,modelView,projection,viewPort,&leftClickedCoordinate[0],&leftClickedCoordinate[1],&leftClickedCoordinate[2]);	//������� ���� �迭�� ����

   //testing
   cout<<"Clicked: [x]"<<leftClickedCoordinate[0]<<" [y] "<<leftClickedCoordinate[1]<<" [z] "<<leftClickedCoordinate[2]<<endl;
}



void Coordinate::rightClick(int xCursor, int yCursor){

   viewToWorld(xCursor, yCursor);
   gluUnProject(winX,winY,zCursor,modelView,projection,viewPort,&rightClickedCoordinate[0],&rightClickedCoordinate[1],&rightClickedCoordinate[2]);	//������� ���� �迭�� ����
}

void Coordinate::dragMove(int xCursor, int yCursor){

   viewToWorld(xCursor, yCursor);
   gluUnProject(winX,winY,zCursor,modelView,projection,viewPort,&dragMovedCoordinate[0],&dragMovedCoordinate[1],&dragMovedCoordinate[2]);	//������� ���� �迭�� ����
}




//set �Լ���

	//���� ��ư�� ���������� ��ǥ���� �������� ����
void Coordinate::setLeftClickedCoordinate(float x,float y,float z){

	leftClickedCoordinate[0] = x;
	leftClickedCoordinate[1] = y;
	leftClickedCoordinate[2] = z;
}

	//������ ��ư�� ���������� ��ǥ���� �������� ����
void Coordinate::setRightClickedCoordinate(float x,float y,float z){

	rightClickedCoordinate[0] = x;
	rightClickedCoordinate[1] = y;
	rightClickedCoordinate[2] = z;
}
	//�巡�׽� ��ǥ���� �������� ����
void Coordinate::setDragMovedCoordinate(float x,float y,float z){

	dragMovedCoordinate[0] = x;
	dragMovedCoordinate[1] = y;
	dragMovedCoordinate[2] = z;
}


//get �Լ���

	//���ʹ�ư ��ǥ�� ����� �迭 ����
GLdouble* Coordinate::getLeftClickedCoordinate(void){

	return leftClickedCoordinate;
}
	//�����ʹ�ư ��ǥ�� ����� �迭 ����
GLdouble* Coordinate::getRightClickedCoordinate(void){

	return rightClickedCoordinate;
}
	//�巡�׽� ��ǥ�� ����� �迭 ����
GLdouble* Coordinate::getdragMoveCoordinate(void){

	return dragMovedCoordinate;
}

void Coordinate::SelectObjects(GLint x, GLint y, float* m){
	GLuint selectBuff[64];                                // <1>   
    GLint hits, viewport[4];                              // <2>   
      
    glSelectBuffer(64, selectBuff);                       // <3>   
    glGetIntegerv(GL_VIEWPORT, viewport);                 // <4>   
    glMatrixMode(GL_PROJECTION);                          // <5>   
    glPushMatrix();                                       // <6>   
    glRenderMode(GL_SELECT);                              // <7>   
    glLoadIdentity();                                     // <8>   
    gluPickMatrix(x, viewport[3]-y, 2, 2, viewport);      // <9>      
    glMatrixMode(GL_MODELVIEW);                           // <11>  
	glLoadMatrixf(m);
    glLoadIdentity();                                     // <12>   
    hits = glRenderMode(GL_RENDER);                       // <14>   
    if(hits>0) ProcessSelect(selectBuff);                 // <15>   
    glMatrixMode(GL_PROJECTION);                          // <16>   
    glPopMatrix();                                        // <17>   
    glMatrixMode(GL_MODELVIEW);                           // <18>   
}  


void Coordinate::ProcessSelect(GLuint index[64])   
{   
		cout<<"Process ��"<<endl;
  switch(index[3]) {   
    case 22:cout<<"22"<<endl;  break;   
    case 23:cout<<"23"<<endl; break;   
    case 24:cout<<"24"<<endl; break;   
    case 25:cout<<"25"<<endl;  break;   
    case 26:cout<<"26"<<endl;  break;   
    case 27:cout<<"27"<<endl;  break;   
      
    default:break;   
  }   
}  
