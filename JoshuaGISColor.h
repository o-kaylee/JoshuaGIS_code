#pragma once

#include <vector>

typedef struct JoshuaColor{
	CString name;
	int num;
	double code[3];
}JColor;

#define TOTAL_NUMBER_OF_COLOR 10

class JoshuaGISColor
{
public:
	JoshuaGISColor(void);
	~JoshuaGISColor(void);

	int NUM_OF_COLOR;

	std::vector<JColor> colorVector;

	JColor black;
	JColor red;
	JColor yellow;
	JColor blue;
	JColor green;

	int getNumofColor(void);
	CString getNameofColor(int index);
	double* getCodeofColor(int index);
	double* getCodeofColor(CString name);
};

