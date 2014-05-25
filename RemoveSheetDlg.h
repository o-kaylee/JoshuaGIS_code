#pragma once
#include "afxwin.h"


// CRemoveSheetDlg 대화 상자입니다.

class CRemoveSheetDlg : public CDialog
{
	DECLARE_DYNAMIC(CRemoveSheetDlg)

public:
	CRemoveSheetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRemoveSheetDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REMOVE_SHEET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_excelFileCombo;
	CComboBox m_deleteSheetCombo;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	int nIndex;
	CString excelFileName;
	CString sheetName;
	virtual void OnOK();
};
