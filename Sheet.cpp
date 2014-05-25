#include "stdafx.h"
#include "Sheet.h"
#include <string.h>

Sheet::Sheet(char* sheetname, unsigned int numItem, int i, BasicExcelWorksheet *_sheet)//,BasicExcel* _e)
{
	strcpy(sheetName, sheetname);
	numOfItem = numItem-1;
	sheet = _sheet;
	//e = _e;
}

Sheet::~Sheet(void)
{
}

char* Sheet::getSheetName()
{
	return sheetName;
}

int Sheet::getNumOfItem()
{
	return numOfItem;
}
void Sheet::increaseItem()
{
	numOfItem++;
}