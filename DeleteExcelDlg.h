#pragma once
#include "afxwin.h"


// CDeleteExcelDlg 대화 상자입니다.

class CDeleteExcelDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeleteExcelDlg)

public:
	CDeleteExcelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDeleteExcelDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DELETE_EXCEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_excelFileCombo;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	int nIndex;
	CString delete_excelName;
};
