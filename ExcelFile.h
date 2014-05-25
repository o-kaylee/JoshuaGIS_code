#pragma once
#ifndef __EXCELFILE_H__
#define __EXCELFILE_H__

#include "Sheet.h"
#include <vector>

class ExcelFile
{
	char fileName[100];
	BasicExcel e;
	//vector<BasicExcel> e;
	unsigned int numSheets;
	vector<Sheet> sheets;

public:
	ExcelFile(char* filename);
	~ExcelFile(void);

	unsigned int getNumOfSheets();
	char* getFileName();
	Sheet* getSheet(char* sheetname);
	Sheet* getSheet(int i);

};

#endif __EXCELFILE_H__