#include "stdafx.h"
#include "Coordinate.h"


//초기화
Coordinate::Coordinate(){

}

Coordinate::Coordinate(bool init){
	initFlag = init;
}


//leftClick, rightClick, dragMove 함수에 공통적으로 들어가는 부분을 가지고 있는 함수.

void Coordinate::viewToWorld(int xCursor, int yCursor){
	//위에서 설정한 공간에 각각의 매트릭스 정보를 받아온다
	// glPushMatrix();
   glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
   glGetDoublev(GL_PROJECTION_MATRIX,projection);
   glGetIntegerv(GL_VIEWPORT,viewPort);
  //glPopMatrix();
   winX = (float)xCursor;
   winY = (float)viewPort[3]-(float)yCursor;
   glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor); //z 버퍼값을 구하는 함수
}


//좌클릭, 우클릭, 드래그에 대한 함수

void Coordinate::leftClick(int xCursor, int yCursor){
   
   viewToWorld(xCursor, yCursor);
   gluUnProject(winX,winY,zCursor,modelView,projection,viewPort,&leftClickedCoordinate[0],&leftClickedCoordinate[1],&leftClickedCoordinate[2]);	//결과값을 각각 배열에 저장

   //testing
   cout<<"Clicked: [x]"<<leftClickedCoordinate[0]<<" [y] "<<leftClickedCoordinate[1]<<" [z] "<<leftClickedCoordinate[2]<<endl;
}



void Coordinate::rightClick(int xCursor, int yCursor){

   viewToWorld(xCursor, yCursor);
   gluUnProject(winX,winY,zCursor,modelView,projection,viewPort,&rightClickedCoordinate[0],&rightClickedCoordinate[1],&rightClickedCoordinate[2]);	//결과값을 각각 배열에 저장
}

void Coordinate::dragMove(int xCursor, int yCursor){

   viewToWorld(xCursor, yCursor);
   gluUnProject(winX,winY,zCursor,modelView,projection,viewPort,&dragMovedCoordinate[0],&dragMovedCoordinate[1],&dragMovedCoordinate[2]);	//결과값을 각각 배열에 저장
}




//set 함수들

	//왼쪽 버튼이 눌렸을때의 좌표값을 수동으로 설정
void Coordinate::setLeftClickedCoordinate(float x,float y,float z){

	leftClickedCoordinate[0] = x;
	leftClickedCoordinate[1] = y;
	leftClickedCoordinate[2] = z;
}

	//오른쪽 버튼이 눌렸을때의 좌표값을 수동으로 설정
void Coordinate::setRightClickedCoordinate(float x,float y,float z){

	rightClickedCoordinate[0] = x;
	rightClickedCoordinate[1] = y;
	rightClickedCoordinate[2] = z;
}
	//드래그시 좌표값을 수동으로 설정
void Coordinate::setDragMovedCoordinate(float x,float y,float z){

	dragMovedCoordinate[0] = x;
	dragMovedCoordinate[1] = y;
	dragMovedCoordinate[2] = z;
}


//get 함수들

	//왼쪽버튼 좌표값 저장된 배열 리턴
GLdouble* Coordinate::getLeftClickedCoordinate(void){

	return leftClickedCoordinate;
}
	//오른쪽버튼 좌표값 저장된 배열 리턴
GLdouble* Coordinate::getRightClickedCoordinate(void){

	return rightClickedCoordinate;
}
	//드래그시 좌표값 저장된 배열 리턴
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
		cout<<"Process 들어감"<<endl;
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
