
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#ifndef _VERTEX_FILE_READER_H_
#define _VERTEX_FILE_READER_H_


////////////////////////////////
class NaktaVertex{

private:
	
	//number of arrays
	int numOfVertex;
	
	//vertex 
	vector<float>  VtX, VtY, VtZ;
	
	
	//vertex normal vector  정점의 노멀벡터 정보가 들어갈 곳
	vector<float> VertexNnormalVectorX, VertexNnormalVectorY, VertexNnormalVectorZ;

	//정점의 법선벡터를 구할시, 인접한 면의 facevector를 더해주는데, 몇개의 vector가 더해졌는지 기록할 공간.
	vector<int> numOfRelatedFaceVector;

	//file name
	char* fileName;

	//error flag
	int errorFlag;

public:
	NaktaVertex();
	~NaktaVertex();
	void init(char* file);
	int getNumOfVertex();
	//int getNumofFace();
	float getVertex(char axis, int index);
	
	//x,y,z 에 대한 함수를 따로 만들어 속도를 높힘.
	
	//해당 index 의 x,y,z 리턴
	float getVertexX(int index);
	float getVertexY(int index);
	float getVertexZ(int index);

	//해당 index 의 정점 노멀법선벡터의 x,y,z 값 리턴
	float getVertexNormalVectorX(int index);
	float getVertexNormalVectorY(int index);
	float getVertexNormalVectorZ(int index);
	//해당 index 의 관련된 face normal vector 수 리턴
	int getVertexNormalVectorNumberOfRelatedFaceVector(int index);			//다 구하고 난 뒤에, 이 공간 반환하는 함수 만들어 볼 것..


	// 정점 법선벡터 크기, (x,y,z)셋팅, 관련된 face normal vector 수 설정하는 함수.
	void setVertexNormalVectorSize(int size);//초기화.
	void setVertexNormalVector(int index, float x, float y, float z);
	void setVertexNormalVectorNumberOfRelatedFaceVector(int index, int count);
	
};

#endif _VERTEX_FILE_READER_H_