#pragma once


// CAddExcelDlg 대화 상자입니다.

class CAddExcelDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddExcelDlg)

public:
	CAddExcelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddExcelDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_EXCEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString new_excelName;
	CString new_sheetName;
};
