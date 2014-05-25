#include "stdafx.h"
#include "ExcelFileManage.h"


ExcelFileManage::ExcelFileManage(char* filename)
{
	int numOfFiles;
	BasicExcelWorksheet* _sheet;

	manage_file.Load(filename);
	_sheet = manage_file.GetWorksheet(0);
	numOfFiles = _sheet->GetTotalRows();

	for(int i=0; i<numOfFiles; i++){
		BasicExcel e;
		int numSheet;
		int count=0;

		cell = _sheet->Cell(i,0);
		
		e.Load((char*)cell->GetString());
		files_name.push_back((char*)cell->GetString());//파일이름 벡터에

		numSheet = e.GetTotalWorkSheets();
		numOfSheets.push_back(numSheet);

		for(int j=0; j<numSheet; j++){
			BasicExcelWorksheet* sheet;
			sheet = e.GetWorksheet(j);
			//sheets.push_back(sheet);
			printf("%s\n",e.GetAnsiSheetName(j));
			sheets_name.push_back(e.GetAnsiSheetName(j));
		}
		e.Close();
		//files.push_back(e);
	}
}


ExcelFileManage::~ExcelFileManage(void)
{
}
