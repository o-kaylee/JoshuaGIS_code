// AddExcelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JoshuaGIS3.h"
#include "AddExcelDlg.h"
#include "afxdialogex.h"

// CAddExcelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddExcelDlg, CDialog)

CAddExcelDlg::CAddExcelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddExcelDlg::IDD, pParent)
	, new_excelName(_T(""))
	, new_sheetName(_T(""))

{

}

CAddExcelDlg::~CAddExcelDlg()
{
}

void CAddExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, new_excelName);
	DDX_Text(pDX, IDC_EDIT2, new_sheetName);
	DDV_MaxChars(pDX, new_sheetName, 50);
	DDV_MaxChars(pDX, new_excelName, 50);
}


BEGIN_MESSAGE_MAP(CAddExcelDlg, CDialog)
END_MESSAGE_MAP()


// CAddExcelDlg 메시지 처리기입니다.