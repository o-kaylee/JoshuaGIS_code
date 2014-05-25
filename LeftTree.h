#pragma once

#include "BasicExcel.hpp"
#include "FileManage.h"

// CLeftTree ���Դϴ�.

class CLeftTree : public CTreeView
{
	DECLARE_DYNCREATE(CLeftTree)

protected:
	CLeftTree();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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


