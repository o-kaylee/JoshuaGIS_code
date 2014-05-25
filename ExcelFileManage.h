#pragma once
#include "BasicExcel.hpp"

#include <vector>
#include <string>

using namespace YExcel;
class ExcelFileManage
{
	BasicExcel manage_file;
	//vector<BasicExcel> files;
	//vector<BasicExcelWorksheet*> sheets;
	vector<int> numOfSheets;	//각 파일이 가지고 있는 sheet의 수
	vector<char*> files_name;
	vector<char*> sheets_name;

	BasicExcelCell* cell;

public:
	ExcelFileManage(char* filename);
	~ExcelFileManage(void);
};

