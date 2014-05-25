#include "stdafx.h"
#include "Texture.h"
#include <iostream>

using namespace std;

Texture::Texture(void){
}

Texture::Texture(bool init){
	initFlag = init;
	xBigger = false;
	yBigger = false;
}

Texture::~Texture(){

}


void Texture::init(bool init){
	initFlag = init;
	xBigger = false;
	yBigger = false;



}

void Texture::initTexture(char* fileName,GLuint *textures){
	

	initFlag = true;

	glEnable(GL_TEXTURE_2D);	//2���� �ؽ��� ����ϰڴٰ� ������.

	AUX_RGBImageRec* tex;
	glGenTextures(1,textures);

	//�̹��� �ҷ���
	tex = auxDIBImageLoad(_T("naktaImage.bmp"));


	//int squareImageWidthHeight
	if(((tex->sizeX) != squareSize) || ((tex->sizeY) != squareSize))
		


	glBindTexture(GL_TEXTURE_2D,textures[0]);	//Ȱ��ȭ�� �ؽ��� ����

	//�ؽ��� Ư��
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);			//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);			//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	//�ؽ��� ���� �ҽ��� ũ�� < ���εǾ��� ��ü�� ũ���϶� Ȯ��ó��
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);    //�ؽ��� ���� �ҽ��� ũ�� > ���εǾ��� ��ü�� ũ���϶� Ȯ��ó��

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3, tex->sizeX,tex->sizeY,GL_RGB,GL_UNSIGNED_BYTE,tex->data);
	cout<<"         initTexture x,y"<<tex->sizeX<<" "<<tex->sizeY<<endl;

	delete tex->data;
	delete tex;
	tex = NULL;



	//�̹��� ��ǥ �ְ��� �����ϱ� ���� ���.  �̹��� ũ�Ⱑ 2�� ����ũ�� ��ŭ�� �����ϱ� ������, ����� �ȸ´� ��� ���̰� �� ���� �� �������� �̹����� ���߰�
	//���� �κ��� ���������� ó���Ͽ� �̹��� �����Ѵ�. �� �̹����� �׳� ����ҽ� ���������� �� �κ����� ���� �ؽ��� ��ǥ�� �����ϹǷ� ���� ���ϴ� ������ �̷�� ���� �ʴ´�.
	//���� ���������� �� �κ��� ���̸� ���Ͽ� x,y,��ǥ�� ���۰��� ���Ѵ�.
	


	
	//1. xBigger ���� yBigger ���� ����

			
	if(width > height)  //x���� �� �� �׸�
		xBigger = true;
	else if(width < height)		//y���� �� �� �׸�
		yBigger = true;
	else{
		xBigger = false; yBigger = false;
	}

	//1����. 2. startSize ���� ���� startX,Y ����.. ..  (start size�� �־��ִ� �Լ� �ʿ�. �������)
	
	if(xBigger){
		startSizeY = height / width;			// 1:���� = x: ����
		startSizeX = 1.0;
		startX = 0.0;
		startY = 1.0 -startSizeY;
	}

	else if(yBigger){			//�� ���� �������� ã�µ� ���Ǹ� �дٱ� ���ٴ� 
		startSizeX =  width / height;		//1:���� = x: ����
		startSizeY = 1.0;
		startX = 0.0;
		startY = 0.0;
	}

	else{
		startX = 0.0;
		startY = 0.0;
	}

	
	glDisable(GL_TEXTURE_2D);
	
}


//���簢���� �ȼ� ũ���, ���ϴ� �κ��� ũ�� �Է�
void Texture::setInformation(int squareImageWidthHeight,int imageWidth, int imageHeight){
	squareSize = squareImageWidthHeight;
	width = imageWidth;
	height = imageHeight;
}
//����¥������ �˾Ƴ�
void Texture::setRow(int number){
	row = number;
}

//������˾Ƴ�
void Texture::setColumn(int number){
	column = number;
}

// x,y ���� ������ ����
void Texture::setXYrate(){

	
	//xRate = 1.0 / (float)(row-1);
	//yRate=  1.0 / (float)(column-1);
	//xRate = startSizeX / (float)(row-1);
	//yRate=  startSizeY / (float)(column-1);
	
	xRate = startSizeX / (float)(column-1);
	yRate=  startSizeY / (float)(row-1);
}

	//���� index �� �Է����ָ� �˾Ƽ� ���° ��, ������ ����ؼ� texture ���� �ش� x,y �� ��ǥ�� �����Ѵ�.
float Texture::getCoordinatedX(int index){
	
	// (int)(index / column)  index �� �� col����
	//return  0.0+ ((int)(index / column))*xRate;  
	return  startX+ (index % column)*xRate;  
}
float Texture::getCoordinatedY(int index){

	// index % column index �� �� column ���� 

	//return  0.0 +(index % column)*yRate;
	
	//��Ī��ǥ 1.0-startSizeY/2.0

	
	return  startY +((int)(index / column))*yRate;
}