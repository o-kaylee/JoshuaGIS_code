#include "stdafx.h"
#include "Line.h"


Line::Line(){

}
void Line::setVectorSize(int size){

	//사이즈 조정
	pointX.resize(size);
	pointY.resize(size);
	pointZ.resize(size);
}
void Line::setPointXYZ(int index, float x, float y, float z){
	pointX[index] = x;
	pointY[index] = y;
	pointZ[index] = z;
}

void Line::setNumberOfLinePoints(int number){
	numberOfLinePoints  = number;
}
float* Line::getPointXYZ(int index){
	points[0] = pointX[index];
	points[1] = pointY[index];
	points[2] = pointZ[index];
	return points;
}
float Line::getPointX(int index){
	return pointX[index];
}
float Line::getPointY(int index){
	return pointY[index];
}
float Line::getPointZ(int index){
	return pointZ[index];
}
int Line::getNumberOfLinePoints(void){
	return numberOfLinePoints;
}