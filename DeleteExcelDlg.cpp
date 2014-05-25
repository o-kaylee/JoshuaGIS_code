// DeleteExcelDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "JoshuaGIS3.h"
#include "DeleteExcelDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "LeftTree.h"
#include "RemoveConfirmDlg.h"

// CDeleteExcelDlg ��ȭ �����Դϴ�.

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


// CDeleteExcelDlg �޽��� ó�����Դϴ�.


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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
