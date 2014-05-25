#include "StdAfx.h"
#include "JoshuaGISColor.h"

JoshuaGISColor::JoshuaGISColor(void)
{
	NUM_OF_COLOR = TOTAL_NUMBER_OF_COLOR;

	black.name = "Black";
	black.num = 0;
	black.code[0] = 0.0; black.code[1] = 0.0; black.code[2] = 0.0;
	colorVector[0] = black;

	red.name = "Red";
	red.num = 1;
	red.code[0] = 1.0; red.code[1] = 0.0; red.code[2] = 0.0;
	colorVector[1] = red;

	yellow.name = "Yellow";
	yellow.num = 2;
	yellow.code[0] = 1.0; yellow.code[1] = 1.0; yellow.code[2] = 0.0;
	colorVector[2] = yellow;

	blue.name = "Blue";
	blue.num = 3;
	blue.code[0] = 0.0; blue.code[1] = 0.0; blue.code[2] = 1.0;
	colorVector[3] = blue;

	green.name = "Green";
	green.num = 4;
	green.code[0] = 0.0; green.code[1] = 1.0; green.code[2] = 0.0;
	colorVector[4] = green;
}

JoshuaGISColor::~JoshuaGISColor(void)
{
}

int JoshuaGISColor::getNumofColor(void)
{
	return NUM_OF_COLOR;
}

CString JoshuaGISColor::getNameofColor(int index) // index는 0 ~ (n-1) 사이의 숫자가 들어갈 수 있다.
{		
	return colorVector[index].name;
}

double* JoshuaGISColor::getCodeofColor(int index)
{
	return colorVector[index].code;
}

double* JoshuaGISColor::getCodeofColor(CString name)
{
	int i = 0;

	for(i = 0; i < TOTAL_NUMBER_OF_COLOR; i++)
		if(name == colorVector[i].name)
			return colorVector[i].code;

	AfxMessageBox(_T("Can't find color!"));
	return false;
}
