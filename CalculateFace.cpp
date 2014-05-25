#include "stdafx.h"
#include "CalculateFace.h"

//9899개의 면...

//198 * row 수 +197 하면 마지막 index 나옴.. 9899가 마지막 인덱스 이므로, 크기는 9900으로.

//생성자
CalculateFace::CalculateFace(){

}
CalculateFace::CalculateFace(bool flag){
	initFlag  = flag;
}

//소멸자
CalculateFace::~CalculateFace(){

}

//vertex 정보를 가지고 face 정보를 구현
void CalculateFace::vertexToFace(Face* facePointer){

		int i, j, row;



		cout<<"[CalculateFace::vertexToFace] Loading"<<endl;

		//    |↘
		//    ---     모양 삼각형

		row = 0;

		for(j = 0; j < 4900 ; j+= 100){
			for(i = 0; i < 99 ; i++){
				facePointer->setPointInfo((198*row)+(i*2),i+j,i+j+1,i+j+100);
			}
			row++;
		}

		//   ---
		//   ↘ |   모양 삼각형   
		row = 0;
		for(j = 100; j < 5000 ; j+= 100){
			for(i = 0; i < 99 ; i++){
				facePointer->setPointInfo((198*row)+1+(i*2),i+j,i+j-99,i+j+1);
			}
			row++;
		}
		

		//cout<<"[CalculateFace::vertexToFace] Finished!"<<endl;

}


//법선 벡터 및 노멀라이즈 하여 Face(면)에 법선벡터 정보 입력하는 것
void CalculateFace::setFaceNormalVector(Face* facePointer, NaktaVertex* vertexPointer){

	int i=0;
	//면의 갯수
	int numOfFace = facePointer->getNumOfFace();

	//법선백터
	float x,y,z;
	//벡터 크기
	float vectorSize;

	//점 1, 점2, 점3 의 x,y,z
	float x1, y1, z1;
	float x2, y2, z2;
	float x3, y3, z3;

	//점 1,2,3 을 이용한 벡터.
		//v1:  점 1-> 점2 벡터
	float v1x, v1y, v1z;
		//v2: 점 1 -> 점3 벡터
	float v2x, v2y, v2z;


	//벡터 계산 및 노멀라이즈, 그리고 정보갱신

	
		cout<<"[CalculateFace::setFaceNormalVector] Loading"<<endl;


	for(i = 0 ; i < numOfFace ; i++){
		//점1
		x1 =  vertexPointer->getVertexX(facePointer->getPoint1(i));
		y1 =  vertexPointer->getVertexY(facePointer->getPoint1(i));
		z1 =  vertexPointer->getVertexZ(facePointer->getPoint1(i));
		//점2
		x2 =  vertexPointer->getVertexX(facePointer->getPoint2(i));
		y2 =  vertexPointer->getVertexY(facePointer->getPoint2(i));
		z2 =  vertexPointer->getVertexZ(facePointer->getPoint2(i));
		//점3
		x3 =  vertexPointer->getVertexX(facePointer->getPoint3(i));
		y3 =  vertexPointer->getVertexY(facePointer->getPoint3(i));
		z3 =  vertexPointer->getVertexZ(facePointer->getPoint3(i));
	
		//v1 구한다   p2 - p1
		v1x = x2 - x1;
		v1y = y2 - y1;
		v1z = z2 - z1;
		//v2 구한다  p3 - p1
		v2x = x3 - x1;
		v2y = y3 - z1;
		v2z = z3 - z1;

		//벡터 구한다
		x = v1y*v2z - v1z*v2y;
		y = v1z*v2x - v1x*v2z;
		z = v1x*v2y - v1y*v2x;

		//노멀라이즈 한다
		vectorSize = sqrt(x*x +y*y+z*z);
		x /= vectorSize;
		y /= vectorSize;
		z /= vectorSize;

		//정보 입력
		facePointer->setNormalVector(i,x,y,z);
	}

	
		cout<<"[CalculateFace::setFaceNormalVector] Finished!"<<endl;

}