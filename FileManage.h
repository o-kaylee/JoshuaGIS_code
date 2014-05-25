#pragma once
#ifndef __FILEMANAGE_H__
#define __FILEMANAGE_H__

#include "ExcelFile.h"

#define ID_COL 0

typedef unsigned int Excel_Index;
typedef int Id_Value;

class FileManage
{
	BasicExcel e;
	unsigned int numOfFiles;
	char* fileName;
	vector<ExcelFile> files;

public:
	FileManage(void);
	~FileManage(void);

	void FileLoad(char* filename);	//���⼭ filename�� ��ü file�̸��� ������ �ִ� ������ �̸��̴�.

	//���⼭�� filename�� ���� �����͸� ������ �ִ� ������ �̸��̴�.
	void setData(char* filename, char* sheetname, Excel_Index row, Excel_Index col, int Data);
	void setData(char* filename, char* sheetname, Excel_Index row, Excel_Index col, double Data);
	void setData(char* filename, char* sheetname, Excel_Index row, Excel_Index col, char* Data);
	void setId(char* filename, char* sheetname, Id_Value oldId, Id_Value newId);

	ExcelFile* getFile(char *filename);
	ExcelFile* getFile(int i);
	int getNumOfFiles();
	int getDataInt(char* filename, char* sheetname, Excel_Index row, Excel_Index col);
	double getDataDouble(char* filename, char* sheetname, Excel_Index row, Excel_Index col);
	const char* getDataString(char* filename, char* sheetname, Excel_Index row, Excel_Index col);
	void setSheetName(char* filename, char* oldSheetname, char* newSheetname);
	void addFile(CString filename, CString sheetname);

	void addSheet(CString filename, CString sheetname);
	void deleteSheet(CString filename, CString sheetname);
	void deleteFile(CString filename);

	void intialize(int addFile);
};

#endif __FILEMANAGE_H__