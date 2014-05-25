#pragma once
#include "afxwin.h"


// CAddSheetDlg 대화 상자입니다.

class CAddSheetDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddSheetDlg)

public:
	CAddSheetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddSheetDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_SHEET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_excelFileCombo;
	virtual BOOL OnInitDialog();
	CString new_sheetName;
	virtual void OnOK();
	int nIndex;
	CString old_excelName;
};
