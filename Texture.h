#include <GL/GLAUX.H>

#ifndef _TEXTURE_
#define _TEXTURE_

class Texture{

private:
	bool initFlag;
	bool xBigger, yBigger;			//불러온 텍스쳐가 x축이 더 큰지, y축이 더 큰지 나타내는 값.

	float squareSize, width, height;		//해당 이미지의 길이와 원하는 이미지의 너비와 높이.(정사각형 맞추기 위해 검은색 부분을 포함한 영역을 제외한 것)

	int row;
	int column;
	
	float startSizeX, startSizeY 	;		// xBigger 또는 yBigger를 통해 x축또는 y축 기준인지 구한다음,  1:정사각형 크기 = x : 해당 축의 크기(startSize) 를 통해   startx,y를 구한다
	
	float startX, startY;	//black face( 정사각형으로 맞추기 위해 채워넣은 검정색 면)을 감안하고 계산하였을 떄의 x,y 좌표 시작값. 
	
	float xRate, yRate;		//4개의 좌표를 일치시켰을때, x,y 의 증가율을 나타냄.  ex) 시작점이 0,0   그 다음점은 0,0+xrate*i (i는 몇번쨰 column 인지..)..이런식
	

public:
	Texture();			
	Texture(bool init);
	~Texture();
	void init(bool init);
	void setInformation(int squareImageWidthHeight,int imageWidth, int imageHeight);	//이미지의 너비와 높이를 입력받음
	void initTexture(char* fileName,GLuint *textures);
	void setRow(int number);		//row 설정
	void setColumn(int number);		//colum 설정
	
	void setXYrate();		//좌표 일치상에서 x,y 의 증가율을 구함
	
	//점의 index 를 입력해주면 알아서 몇번째 행, 열인지 계산해서 texture 상의 해당 x,y 의 좌표를 리턴한다.
	float getCoordinatedX(int index);	
	float getCoordinatedY(int index); 

};


#endif
