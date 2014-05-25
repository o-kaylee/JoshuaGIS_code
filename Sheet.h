#pragma once

#ifndef __SHEET_H__
#define __SHEET_H__

#include "BasicExcel.hpp"
#define ID_COL 0

using namespace YExcel;
class Sheet
{
	char sheetName[100];
	unsigned int numOfItem;
	BasicExcelWorksheet* sheet;
	//BasicExcel *e;

public:
	Sheet(char* sheetname, unsigned int numItem, int i, BasicExcelWorksheet *_sheet);//, BasicExcel* _e);
	~Sheet(void);

	char* getSheetName();
	int getNumOfItem();
	void increaseItem();
	//void decreaseItem();
};

#endif __SHEET_H__
