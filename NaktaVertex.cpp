#include "stdafx.h"
#include "NaktaVertex.h"
#include <math.h>


//�Ҹ���
NaktaVertex::~NaktaVertex(){

}

//������
NaktaVertex::NaktaVertex(){

}



void NaktaVertex::init(char* file){
		//Ŭ���� ������ ���ϱ� ���� �ּ�, �ִ� x,y,z���� ���Ѵ�
	float minX , minY , minZ ;
	float maxX , maxY , maxZ ;


	cout<<"[NaktaVertex::NaktaVertex] Loading vertexes ...."<<endl;

	fileName = file;
	numOfVertex = 0;
	

	ifstream myFile;
	myFile.open(fileName,ios::in);	//open file only for Input (cannot revise) 
	
	char buf[256];             //create buffer to read line
	char *token = NULL;

	if(!(myFile.is_open())){	//file open failure
		errorFlag = true; //error occured
		cout<<"Error"<<endl;
		system("pause");
		exit(1);		 //����.
	}

		

	while(!myFile.eof()){	//until the end of file.
		
		myFile.getline(buf,256);//read only one line.

		if(buf[0]==NULL)//prevent error form obj file that includes gap lines.
			continue;
		
			//push values
			token = strtok(buf," "); //split string.	
			VtX.push_back(atof(token));


			token = strtok(NULL," ");
			VtY.push_back(atof(token));

			token = strtok(NULL," ");
			VtZ.push_back(atof(token));

			
			//cout<<VtX[numOfVertex]<<" "<<VtY[numOfVertex]<<" "<<VtZ[numOfVertex]<<endl;
			//cout<<"Vertex Num: "<<numOfVertex+1<<endl;

			numOfVertex++;	//increase number of Vertex


	}

	VtX.resize(numOfVertex);
	VtY.resize(numOfVertex);
	VtZ.resize(numOfVertex);
	
	
		

	//set min,max value

	minX = VtX[0];	minY = VtY[0];	minZ = VtZ[0];
	maxX = VtX[0];	maxY = VtY[0];	maxZ = VtZ[0];

	for(int i = 0; i < 5000 ; i++){
		
		if(minX > VtX[i])	minX = VtX[i];	
		if(minY > VtY[i])	minY = VtY[i];
		if(minZ > VtZ[i])	minZ = VtZ[i];

		if(maxX < VtX[i]) maxX = VtX[i];
		if(maxY < VtY[i]) maxY = VtY[i];
		if(maxZ < VtZ[i]) maxZ = VtZ[i];
	}


	float maxSize;

	maxSize = sqrt(pow((minX-maxX),2)+pow((minY-maxY),2)+pow((minZ-maxZ),2));

	
	cout<<"�ּ� x: "<<minX<<"   �ּ� y: "<<minY<<"   �ּ� z: "<<minZ<<endl;
	cout<<"�ִ� x: "<<maxX<<"   �ִ� y: "<<maxY<<"   �ִ� z: "<<maxZ<<endl;
	cout<<"maxSize: "<<maxSize<<endl;
	
	cout<<"*********����*********"<<endl;
	cout<<VtX[0]<<" "<<VtY[0]<<" "<<VtZ[0]<<" "<<endl;
	cout<<VtX[99]<<" "<<VtY[99]<<" "<<VtZ[99]<<" "<<endl;
	cout<<VtX[4900]<<" "<<VtY[4900]<<" "<<VtZ[4900]<<" "<<endl;
	cout<<VtX[4999]<<" "<<VtY[4999]<<" "<<VtZ[4999]<<" "<<endl;
	cout<<"*********���� ��*********"<<endl;
	


	
	
	cout<<"[NaktaVertex::NaktaVertex] Loading vertexes finished!"<<endl;

	myFile.close();	//close file
	//system("pause");

}
float NaktaVertex::getVertex(char axis, int index){
	switch(axis){

	case 'x':
	case 'X':
		return  VtX[index]; 
	case 'y':
	case 'Y':
		return VtY[index];
	case'z':
	case'Z':
		return VtZ[index];
	default:
		cout<<"Error"<<endl;
		exit(1);

	}
}

float NaktaVertex::getVertexX(int index){

		return VtX[index];
}

float NaktaVertex::getVertexY(int index){

		return VtY[index];
}

float NaktaVertex::getVertexZ(int index){

		return VtZ[index];
}

int NaktaVertex::getNumOfVertex(){
	return numOfVertex;
}



void NaktaVertex::setVertexNormalVectorSize(int size){

	//���� ���� ��� x,y,z ������ ����
	VertexNnormalVectorX.resize(size);
	VertexNnormalVectorY.resize(size);
	VertexNnormalVectorZ.resize(size);



	//���� �������� ���ҽ� ��� �� �������Ͱ� ���������� �˷��ִ� ���� ����, 
	numOfRelatedFaceVector.resize(size);
	
	//�ʱⰪ ����
	for(int i = 0; i < size ; i++){
		VertexNnormalVectorX[i] = 0;
		VertexNnormalVectorY[i] = 0;
		VertexNnormalVectorZ[i] = 0;
		numOfRelatedFaceVector[i] = 0;
	}

}

void NaktaVertex::setVertexNormalVector(int index, float x, float y, float z){

	//������ ��ֺ��� �������Է�
	VertexNnormalVectorX[index] = x;
	VertexNnormalVectorZ[index] = y;
	VertexNnormalVectorY[index] = z;
}

	//�ش� index �� ���� ��ֹ��������� x,y,z �� ����
float NaktaVertex::getVertexNormalVectorX(int index){
	
	return VertexNnormalVectorX[index];
}

float NaktaVertex::getVertexNormalVectorY(int index){
	
	return VertexNnormalVectorY[index];
}

float NaktaVertex::getVertexNormalVectorZ(int index){
	
	return VertexNnormalVectorZ[index];
}
	//�ش� index �� ������ ������ face normal vector �� �� ����
int NaktaVertex::getVertexNormalVectorNumberOfRelatedFaceVector(int index){
		return numOfRelatedFaceVector[index];
}

void NaktaVertex::setVertexNormalVectorNumberOfRelatedFaceVector(int index, int count){
		//��� faceVector�� ���� �������͸� ���ҽ� ���������� �˾Ƴ��� �Լ�.
		numOfRelatedFaceVector[index] = count;
}