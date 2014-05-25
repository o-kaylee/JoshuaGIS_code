#pragma once

#include "BasicExcel.hpp"
#include "FileManage.h"

// CLeftTree 뷰입니다.

class CLeftTree : public CTreeView
{
	DECLARE_DYNCREATE(CLeftTree)

protected:
	CLeftTree();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CLeftTree();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void TreeDraw();

	FileManage fm;
	HTREEITEM child[100][100];
	HTREEITEM root[100];
	BasicExcelCell *cell;


	void addExcel(CString new_excelName, CString new_sheetName);
	void addSheet(CString filename, CString sheetname);
	void deleteSheet(CString filename, CString sheetname);
	void deleteExcel(CString filename);
	int* getIndex();
	char* getParentName(int index);
	char* getChildSheetName(int parentIndex, int sheetIndex);
	int numFiles;
	CString getChecked(void);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	int parentIndex;
	int childIndex;

};


