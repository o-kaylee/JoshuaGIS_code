#include <GL/GLAUX.H>

#ifndef _TEXTURE_
#define _TEXTURE_

class Texture{

private:
	bool initFlag;
	bool xBigger, yBigger;			//�ҷ��� �ؽ��İ� x���� �� ū��, y���� �� ū�� ��Ÿ���� ��.

	float squareSize, width, height;		//�ش� �̹����� ���̿� ���ϴ� �̹����� �ʺ�� ����.(���簢�� ���߱� ���� ������ �κ��� ������ ������ ������ ��)

	int row;
	int column;
	
	float startSizeX, startSizeY 	;		// xBigger �Ǵ� yBigger�� ���� x��Ǵ� y�� �������� ���Ѵ���,  1:���簢�� ũ�� = x : �ش� ���� ũ��(startSize) �� ����   startx,y�� ���Ѵ�
	
	float startX, startY;	//black face( ���簢������ ���߱� ���� ä������ ������ ��)�� �����ϰ� ����Ͽ��� ���� x,y ��ǥ ���۰�. 
	
	float xRate, yRate;		//4���� ��ǥ�� ��ġ��������, x,y �� �������� ��Ÿ��.  ex) �������� 0,0   �� �������� 0,0+xrate*i (i�� ����� column ����..)..�̷���
	

public:
	Texture();			
	Texture(bool init);
	~Texture();
	void init(bool init);
	void setInformation(int squareImageWidthHeight,int imageWidth, int imageHeight);	//�̹����� �ʺ�� ���̸� �Է¹���
	void initTexture(char* fileName,GLuint *textures);
	void setRow(int number);		//row ����
	void setColumn(int number);		//colum ����
	
	void setXYrate();		//��ǥ ��ġ�󿡼� x,y �� �������� ����
	
	//���� index �� �Է����ָ� �˾Ƽ� ���° ��, ������ ����ؼ� texture ���� �ش� x,y �� ��ǥ�� �����Ѵ�.
	float getCoordinatedX(int index);	
	float getCoordinatedY(int index); 

};


#endif
