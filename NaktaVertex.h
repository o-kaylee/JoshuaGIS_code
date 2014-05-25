
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
	
	
	//vertex normal vector  ������ ��ֺ��� ������ �� ��
	vector<float> VertexNnormalVectorX, VertexNnormalVectorY, VertexNnormalVectorZ;

	//������ �������͸� ���ҽ�, ������ ���� facevector�� �����ִµ�, ��� vector�� ���������� ����� ����.
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
	
	//x,y,z �� ���� �Լ��� ���� ����� �ӵ��� ����.
	
	//�ش� index �� x,y,z ����
	float getVertexX(int index);
	float getVertexY(int index);
	float getVertexZ(int index);

	//�ش� index �� ���� ��ֹ��������� x,y,z �� ����
	float getVertexNormalVectorX(int index);
	float getVertexNormalVectorY(int index);
	float getVertexNormalVectorZ(int index);
	//�ش� index �� ���õ� face normal vector �� ����
	int getVertexNormalVectorNumberOfRelatedFaceVector(int index);			//�� ���ϰ� �� �ڿ�, �� ���� ��ȯ�ϴ� �Լ� ����� �� ��..


	// ���� �������� ũ��, (x,y,z)����, ���õ� face normal vector �� �����ϴ� �Լ�.
	void setVertexNormalVectorSize(int size);//�ʱ�ȭ.
	void setVertexNormalVector(int index, float x, float y, float z);
	void setVertexNormalVectorNumberOfRelatedFaceVector(int index, int count);
	
};

#endif _VERTEX_FILE_READER_H_