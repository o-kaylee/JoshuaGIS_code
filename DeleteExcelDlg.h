#pragma once
#include "afxwin.h"


// CDeleteExcelDlg ��ȭ �����Դϴ�.

class CDeleteExcelDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeleteExcelDlg)

public:
	CDeleteExcelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDeleteExcelDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DELETE_EXCEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_excelFileCombo;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	int nIndex;
	CString delete_excelName;
};
