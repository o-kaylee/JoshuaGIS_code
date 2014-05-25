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

	glEnable(GL_TEXTURE_2D);	//2차원 텍스쳐 사용하겠다고 말해줌.

	AUX_RGBImageRec* tex;
	glGenTextures(1,textures);

	//이미지 불러옴
	tex = auxDIBImageLoad(_T("naktaImage.bmp"));


	//int squareImageWidthHeight
	if(((tex->sizeX) != squareSize) || ((tex->sizeY) != squareSize))
		


	glBindTexture(GL_TEXTURE_2D,textures[0]);	//활성화할 텍스쳐 선언

	//텍스쳐 특성
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);			//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);			//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	//텍스쳐 매핑 소스의 크기 < 맵핑되어질 물체의 크기일때 확대처리
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);    //텍스쳐 매핑 소스의 크기 > 맵핑되어질 물체의 크기일때 확대처리

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3, tex->sizeX,tex->sizeY,GL_RGB,GL_UNSIGNED_BYTE,tex->data);
	cout<<"         initTexture x,y"<<tex->sizeX<<" "<<tex->sizeY<<endl;

	delete tex->data;
	delete tex;
	tex = NULL;



	//이미지 좌표 왜곡을 방지하기 위한 계산.  이미지 크기가 2의 제곱크기 만큼만 가능하기 떄문에, 사이즈가 안맞는 경우 길이가 긴 한쪽 축 기준으로 이미지를 맞추고
	//남는 부분은 검은색으로 처리하여 이미지 저장한다. 이 이미지를 그냥 사용할시 검은색으로 된 부분으로 부터 텍스쳐 좌표가 시작하므로 실제 원하는 맵핑이 이루어 지지 않는다.
	//따라서 검은색으로 된 부분의 길이를 구하여 x,y,좌표의 시작값을 구한다.
	


	
	//1. xBigger 인지 yBigger 인지 구함

			
	if(width > height)  //x축이 더 긴 그림
		xBigger = true;
	else if(width < height)		//y축이 더 긴 그림
		yBigger = true;
	else{
		xBigger = false; yBigger = false;
	}

	//1연관. 2. startSize 값을 통해 startX,Y 구함.. ..  (start size값 넣어주는 함수 필요. 만들었음)
	
	if(xBigger){
		startSizeY = height / width;			// 1:가로 = x: 세로
		startSizeX = 1.0;
		startX = 0.0;
		startY = 1.0 -startSizeY;
	}

	else if(yBigger){			//이 경우는 시작점을 찾는데 의의를 둔다기 보다는 
		startSizeX =  width / height;		//1:세로 = x: 가로
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


//정사각형의 픽셀 크기와, 원하는 부분의 크기 입력
void Texture::setInformation(int squareImageWidthHeight,int imageWidth, int imageHeight){
	squareSize = squareImageWidthHeight;
	width = imageWidth;
	height = imageHeight;
}
//몇행짜리인지 알아냄
void Texture::setRow(int number){
	row = number;
}

//몇열인지알아냄
void Texture::setColumn(int number){
	column = number;
}

// x,y 증가 비율을 설정
void Texture::setXYrate(){

	
	//xRate = 1.0 / (float)(row-1);
	//yRate=  1.0 / (float)(column-1);
	//xRate = startSizeX / (float)(row-1);
	//yRate=  startSizeY / (float)(column-1);
	
	xRate = startSizeX / (float)(column-1);
	yRate=  startSizeY / (float)(row-1);
}

	//점의 index 를 입력해주면 알아서 몇번째 행, 열인지 계산해서 texture 상의 해당 x,y 의 좌표를 리턴한다.
float Texture::getCoordinatedX(int index){
	
	// (int)(index / column)  index 가 몇 col인지
	//return  0.0+ ((int)(index / column))*xRate;  
	return  startX+ (index % column)*xRate;  
}
float Texture::getCoordinatedY(int index){

	// index % column index 가 몇 column 인지 

	//return  0.0 +(index % column)*yRate;
	
	//대칭좌표 1.0-startSizeY/2.0

	
	return  startY +((int)(index / column))*yRate;
}