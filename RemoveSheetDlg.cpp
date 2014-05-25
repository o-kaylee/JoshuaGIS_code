// RemoveSheetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "JoshuaGIS3.h"
#include "RemoveSheetDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "LeftTree.h"
#include "RemoveConfirmDlg.h"

// CRemoveSheetDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRemoveSheetDlg, CDialog)

CRemoveSheetDlg::CRemoveSheetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoveSheetDlg::IDD, pParent)
	, nIndex(0)
	, excelFileName(_T(""))
	, sheetName(_T(""))
{

}

CRemoveSheetDlg::~CRemoveSheetDlg()
{
}

void CRemoveSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_excelFileCombo);
	DDX_Control(pDX, IDC_COMBO2, m_deleteSheetCombo);
}


BEGIN_MESSAGE_MAP(CRemoveSheetDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRemoveSheetDlg::OnSelchangeCombo1)
END_MESSAGE_MAP()


// CRemoveSheetDlg �޽��� ó�����Դϴ�.


BOOL CRemoveSheetDlg::OnInitDialog()
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

void CRemoveSheetDlg::OnSelchangeCombo1()
{
	m_deleteSheetCombo.ResetContent();

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CLeftTree* pTree = (CLeftTree*)pFrame->m_wndSplitter2.GetPane(0, 0);

	nIndex = m_excelFileCombo.GetCurSel();
	m_excelFileCombo.GetLBText(nIndex, excelFileName);

	char* buffer=new char[excelFileName.GetLength()+1];
	WideCharToMultiByte(CP_ACP,0,excelFileName,-1,buffer,excelFileName.GetLength()+1,NULL,NULL);

	ExcelFile *eFile = pTree->fm.getFile(buffer);
	Sheet *_sheet;
	for(int i = 0; i < eFile->getNumOfSheets(); i++){
		_sheet = eFile->getSheet(i);
		sheetName = _sheet->getSheetName();
		m_deleteSheetCombo.AddString(sheetName);
	}
}


void CRemoveSheetDlg::OnOK()
{
	CRemoveConfirmDlg* confirmRemoveDlg = new CRemoveConfirmDlg;
	nIndex = m_excelFileCombo.GetCurSel();
	m_excelFileCombo.GetLBText(nIndex, excelFileName);

	nIndex = m_deleteSheetCombo.GetCurSel();
	m_deleteSheetCombo.GetLBText(nIndex, sheetName);

	if(confirmRemoveDlg->DoModal() == IDOK)
		CDialog::OnOK();
	else
		Invalidate();
}
