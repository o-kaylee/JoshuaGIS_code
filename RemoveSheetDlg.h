#pragma once
#include "afxwin.h"


// CRemoveSheetDlg ��ȭ �����Դϴ�.

class CRemoveSheetDlg : public CDialog
{
	DECLARE_DYNAMIC(CRemoveSheetDlg)

public:
	CRemoveSheetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRemoveSheetDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REMOVE_SHEET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
