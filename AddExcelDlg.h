#pragma once


// CAddExcelDlg ��ȭ �����Դϴ�.

class CAddExcelDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddExcelDlg)

public:
	CAddExcelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddExcelDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_EXCEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CString new_excelName;
	CString new_sheetName;
};
