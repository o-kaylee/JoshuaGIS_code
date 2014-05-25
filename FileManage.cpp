#include "stdafx.h"
#include "FileManage.h"
#include <string>

#define PROPERTY_COUNT 18
char* _property[PROPERTY_COUNT] = {"ID","point/line/polygon size","RGB-R","RGB-G","RGB-B","Title","Characteristic",
						"description","temporary1","temporary2","temporary3","1st.X","1st.Y","1st.Z",
						"2nd.X","2nd.Y","2nd.Z","..."};

FileManage::FileManage(void)
{

}

void FileManage::FileLoad(char* filename)
{
	BasicExcelCell *cell;
	BasicExcelWorksheet* sheet;
	int i = 0;
	numOfFiles = 0;
	fileName = filename;
	e.Load(filename);
	sheet = e.GetWorksheet("Sheet1");
	
	for(i = 0; i < sheet->GetTotalRows(); i++){
		cell = sheet->Cell(i,0);
		if(cell->Type() == cell->STRING){
			files.push_back(ExcelFile((char*)cell->GetString()));
			numOfFiles++;
		}
	}

	e.Close();
}

FileManage::~FileManage(void)
{

}

void FileManage::setData(char* filename, char* sheetname, Excel_Index row, Excel_Index col, int Data)
{
	
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;
	e.Load(filename);
	sheet = e.GetWorksheet(sheetname);
	cell = sheet->Cell(row,col);
	cell->SetInteger(Data);
	e.Save();
	e.Close();
}

void FileManage::setData(char* filename, char* sheetname, Excel_Index row, Excel_Index col, double Data)
{
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;
	e.Load(filename);
	sheet = e.GetWorksheet(sheetname);
	cell = sheet->Cell(row,col);
	cell->SetDouble(Data);
	e.Save();
	e.Close();
}

void FileManage::setData(char* filename, char* sheetname, Excel_Index row, Excel_Index col, char* Data)
{
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;
	e.Load(filename);
	sheet = e.GetWorksheet(sheetname);
	cell = sheet->Cell(row,col);
	cell->SetString(Data);
	e.Save();
	e.Close();
}

void FileManage::setId(char* filename, char* sheetname, Id_Value oldId, Id_Value newId)
{
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;
	e.Load(filename);
	sheet = e.GetWorksheet(sheetname);

	for(int i=0; i<sheet->GetTotalRows(); i++)
	{
		cell = sheet->Cell(i,ID_COL);
		if(cell->GetInteger() == oldId)
			cell->SetInteger(newId);
	}
	e.Save();
	e.Close();
}

int FileManage::getNumOfFiles()
{
	return numOfFiles;
}

int FileManage::getDataInt(char* filename, char* sheetname, Excel_Index row, Excel_Index col)
{
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;
	char* charInt;
	int variable;

	e.Load(filename);
	sheet = e.GetWorksheet(sheetname);
	cell = sheet->Cell(row,col);
	e.Close();
	charInt = (char*)cell->GetString();
	variable = atoi(charInt);

	return variable;
}

double FileManage::getDataDouble(char* filename, char* sheetname, Excel_Index row, Excel_Index col)
{
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;
	char* charDouble;
	double variable;

	e.Load(filename);
	sheet = e.GetWorksheet(sheetname);
	cell = sheet->Cell(row,col);
	e.Close();
	charDouble = (char*)cell->GetString();
	variable = atof(charDouble);
	
	return variable;
}

const char* FileManage::getDataString(char* filename, char* sheetname, Excel_Index row, Excel_Index col)
{
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;
	e.Load(filename);
	sheet = e.GetWorksheet(sheetname);
	cell = sheet->Cell(row,col);
	e.Close();

	return cell->GetString();
}

ExcelFile* FileManage::getFile(char *filename)
{
	for(int i=0; i<numOfFiles; i++)
	{
		if(!strcmp(files[i].getFileName(), filename))
			return &files[i];
	}

	return false;
}

ExcelFile* FileManage::getFile(int i)
{
	if(i>numOfFiles)
		return NULL;
	else
		return &files[i];
}

void FileManage::setSheetName(char* filename, char* oldSheetname, char* newSheetname)
{
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	e.Load(filename);

	sheet = e.GetWorksheet(oldSheetname);
	sheet->Rename(newSheetname);

	e.Save();
	e.Close();
}

void FileManage::addFile(CString filename, CString sheetname)
{
	int count=0;
	char _filename[100];
	char* buffer=new char[filename.GetLength()+1];
	char* buffer2=new char[sheetname.GetLength()+1];
	WideCharToMultiByte(CP_ACP,0,filename,-1,buffer,filename.GetLength()+1,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,sheetname,-1,buffer2,sheetname.GetLength()+1,NULL,NULL);

	BasicExcelCell *cell;
	strcpy(_filename,buffer);
	BasicExcel e;
	BasicExcelWorksheet* sheet; e.New(1);

	sheet = e.GetWorksheet("Sheet1");
	sheet->Rename(buffer2);
	
	for(count=0; count<PROPERTY_COUNT;count++){
		cell = sheet->Cell(0,count); cell->SetString(_property[count]);
	}

	e.SaveAs(strcat(_filename,".xls"));
	e.Close();

	e.Load("manageExcel.xls");
	sheet = e.GetWorksheet("Sheet1");
	cell = sheet->Cell(sheet->GetTotalRows(),0); numOfFiles++;
	cell->SetString(_filename);
	e.Save();
	e.Close();
}

void FileManage::addSheet(CString filename, CString sheetname)
{
char _filename[100];
	int count=0;
	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell *cell;
	char* buffer=new char[filename.GetLength()+1];
	char* buffer2=new char[sheetname.GetLength()+1];

	WideCharToMultiByte(CP_ACP,0,filename,-1,buffer,filename.GetLength()+1,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,sheetname,-1,buffer2,sheetname.GetLength()+1,NULL,NULL);
	strcpy(_filename,buffer);
	
	e.Load(filename);

	for(int i=0; i<e.GetTotalWorkSheets(); i++){
		sheet = e.GetWorksheet(i);
		cell = sheet->Cell(0,0);
		if(cell->Type() == cell->UNDEFINED){
			sheet->Rename(buffer2);
			break;
		}
		sheet = NULL;
	}
	if(sheet == NULL){
		e.AddWorksheet(buffer2);
		sheet = e.GetWorksheet(buffer2);
	}
	for(count=0; count<PROPERTY_COUNT;count++){
		cell = sheet->Cell(0,count); cell->SetString(_property[count]);
	}
	e.Save();
	e.Close();
}

void FileManage::deleteSheet(CString filename, CString sheetname)
{
char _filename[100];
	BasicExcelWorksheet* sheet;
	BasicExcelCell *cell;
	int MaxCol, MaxRow;
	char* buffer=new char[filename.GetLength()+1];
	char* buffer2=new char[sheetname.GetLength()+1];
	WideCharToMultiByte(CP_ACP,0,filename,-1,buffer,filename.GetLength()+1,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,sheetname,-1,buffer2,sheetname.GetLength()+1,NULL,NULL);
	strcpy(_filename,buffer);
	BasicExcel e;
	e.Load(_filename);
	sheet = e.GetWorksheet(buffer2);
	MaxCol = sheet->GetTotalCols();
	MaxRow = sheet->GetTotalRows();

	for(int i=0; i<MaxRow; i++){
		for(int j=0; j<MaxCol; j++){
			cell = sheet->Cell(i,j);
			cell->EraseContents();
		}
	}

	e.Save();
	e.Close();
}


void FileManage::intialize(int addFile)
{
	int fileNum = numOfFiles;
	
	switch(addFile){
	case 1:
		fileNum--;
		break;
	}

	for(int i=0; i<fileNum; i++){
		files.pop_back();
	}
	numOfFiles = 0;
}
	
void FileManage::deleteFile(CString filename)
{
int MaxCol = 0,MaxRow =0;
	char _filename[100];
	BasicExcelWorksheet* sheet;
	BasicExcelWorksheet* sheet2;
	int i=0,j=0;
	char* buffer=new char[filename.GetLength()+1];
	WideCharToMultiByte(CP_ACP,0,filename,-1,buffer,filename.GetLength()+1,NULL,NULL);
	BasicExcelCell *cell;
	BasicExcelCell *cell2;

	BasicExcel e;
	e.Load("manageExcel.xls");
	sheet = e.GetWorksheet("Sheet1");
	sheet2 = e.GetWorksheet("Sheet2");

	MaxCol = sheet->GetTotalCols();
	MaxRow = sheet->GetTotalRows();

	for(; i<sheet->GetTotalRows() ;i++){
		cell = sheet->Cell(i,0);
		cell2 =sheet2->Cell(j,0);

		if(strcmp(buffer,cell->GetString())){
			cell2->SetString(cell->GetString());
			j++;
		}
	}

	/*전부 지우기*/
	for(int i=0; i<MaxRow; i++){
		for(int j=0; j<MaxCol; j++){
			cell = sheet->Cell(i,j);
			cell->EraseContents();
		}
	}

	sheet->Rename("Sheet5");
	sheet2->Rename("Sheet1");
	sheet->Rename("Sheet2");
	e.Save();
	e.Close();

	DeleteFile(filename);
}
