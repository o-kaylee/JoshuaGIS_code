#include "stdafx.h"
#include "ExcelFile.h"
#include <stdlib.h>

ExcelFile::ExcelFile(char* filename)
{
	int i=0,j=0;
	BasicExcelWorksheet* sheet;
	BasicExcelCell *cell;
	unsigned int totalRows;
	strcpy(fileName, filename);
	
	e.Load(filename);
	//numSheets = e.GetTotalWorkSheets();
	for( ; j<e.GetTotalWorkSheets(); j++)
	{
		sheet = (BasicExcelWorksheet*)malloc(sizeof(BasicExcelWorksheet*));
		sheet = e.GetWorksheet(j);
		totalRows = sheet->GetTotalRows();
		cell = sheet->Cell(0,0);
		
		if(cell->Type() != BasicExcelCell::UNDEFINED)
			sheets.push_back(Sheet(sheet->GetAnsiSheetName(),totalRows,i++,sheet));//,&e)); 

	}
	numSheets = i;
	e.Close();
}

ExcelFile::~ExcelFile(void)
{
}

unsigned int ExcelFile::getNumOfSheets()
{
	return numSheets;
}

char* ExcelFile::getFileName()
{
	return fileName;
}

Sheet* ExcelFile::getSheet(char* sheetname)
{
	for(int i=0; i<numSheets; i++)
	{
		if(!strcmp(sheets[i].getSheetName(), sheetname))
			return &sheets[i];
	}
}
Sheet* ExcelFile::getSheet(int i)
{
	if(i>numSheets)
		return NULL;
	else
		return &sheets[i];
}



