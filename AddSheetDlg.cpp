// AddSheetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "JoshuaGIS3.h"
#include "AddSheetDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "LeftTree.h"
#include "RemoveConfirmDlg.h"

// CAddSheetDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddSheetDlg, CDialog)

CAddSheetDlg::CAddSheetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddSheetDlg::IDD, pParent)
	, new_sheetName(_T(""))
	, nIndex(0)
	, old_excelName(_T(""))
{

}

CAddSheetDlg::~CAddSheetDlg()
{
}

void CAddSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_excelFileCombo);
	DDX_Text(pDX, IDC_EDIT1, new_sheetName);
	DDV_MaxChars(pDX, new_sheetName, 50);
}


BEGIN_MESSAGE_MAP(CAddSheetDlg, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CAddSheetDlg �޽��� ó�����Դϴ�.

BOOL CAddSheetDlg::OnInitDialog()
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



void CAddSheetDlg::OnOK()
{
	CRemoveConfirmDlg* confirmRemoveDlg = new CRemoveConfirmDlg;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	nIndex = m_excelFileCombo.GetCurSel();
	m_excelFileCombo.GetLBText(nIndex, old_excelName);
	
	CDialog::OnOK();
}
