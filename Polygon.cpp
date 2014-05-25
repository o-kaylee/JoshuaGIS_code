#include "stdafx.h"
#include "Polygon.h"


PolygonClass::PolygonClass(){

}
void PolygonClass::setPolygonVectorSize(int size){

	//사이즈 조정
	polygonPointX.resize(size);
	polygonPointY.resize(size);
	polygonPointZ.resize(size);
}
void PolygonClass::setPolygonPointXYZ(int index, float x, float y, float z){
	polygonPointX[index] = x;
	polygonPointY[index] = y;
	polygonPointZ[index] = z;
}

void PolygonClass::setNumberOfPolygonPoints(int number){
	numberOfPolygonPoints  = number;
}
float* PolygonClass::getPolygonPointXYZ(int index){
	polygonPoint[0] = polygonPointX[index];
	polygonPoint[1] = polygonPointY[index];
	polygonPoint[2] = polygonPointZ[index];
	return polygonPoint;
}
float PolygonClass::getPolygonPointX(int index){
	return polygonPointX[index];
}
float PolygonClass::getPolygonPointY(int index){
	return polygonPointY[index];
}
float PolygonClass::getPolygonPointZ(int index){
	return polygonPointZ[index];
}
int PolygonClass::getNumberOfPolygonPoints(void){
	return numberOfPolygonPoints;
}
