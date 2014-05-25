// DeleteExcelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JoshuaGIS3.h"
#include "DeleteExcelDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "LeftTree.h"
#include "RemoveConfirmDlg.h"

// CDeleteExcelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDeleteExcelDlg, CDialog)

CDeleteExcelDlg::CDeleteExcelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteExcelDlg::IDD, pParent)
	, nIndex(0)
	, delete_excelName(_T(""))
{

}

CDeleteExcelDlg::~CDeleteExcelDlg()
{
}

void CDeleteExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_excelFileCombo);
}


BEGIN_MESSAGE_MAP(CDeleteExcelDlg, CDialog)
END_MESSAGE_MAP()


// CDeleteExcelDlg 메시지 처리기입니다.


BOOL CDeleteExcelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CLeftTree* pTree = (CLeftTree*)pFrame->m_wndSplitter2.GetPane(0, 0);

	int numFiles = pTree->fm.getNumOfFiles();
	CString fileName;
	
	// TODO
	for(int i = 0; i < numFiles; i++){
		ExcelFile *eFile = pTree->fm.getFile(i);
		fileName = eFile->getFileName();

		m_excelFileCombo.AddString(fileName);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDeleteExcelDlg::OnOK()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CRemoveConfirmDlg* confirmRemoveDlg = new CRemoveConfirmDlg;
	nIndex = m_excelFileCombo.GetCurSel();
	m_excelFileCombo.GetLBText(nIndex, delete_excelName);

	if(confirmRemoveDlg->DoModal() == IDOK)
		CDialog::OnOK();
	else
		Invalidate();
	
}
