#pragma once
#include "afxwin.h"


// CAddSheetDlg ��ȭ �����Դϴ�.

class CAddSheetDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddSheetDlg)

public:
	CAddSheetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddSheetDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_SHEET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_excelFileCombo;
	virtual BOOL OnInitDialog();
	CString new_sheetName;
	virtual void OnOK();
	int nIndex;
	CString old_excelName;
};
