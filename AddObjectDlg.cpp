// AddObjectDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "JoshuaGIS3.h"
#include "AddObjectDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "JoshuaGIS3View.h"

// CAddObjectDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddObjectDlg, CDialog)

CAddObjectDlg::CAddObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddObjectDlg::IDD, pParent)
	, m_valueName(_T(""))
	, m_valueCha(_T(""))
	, m_valueTemp1(_T(""))
	, m_valueTemp2(_T(""))
	, m_valueTemp3(_T(""))
	, m_valueDesc(_T(""))
{

}

CAddObjectDlg::~CAddObjectDlg()
{
}

void CAddObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROP_ID, m_controlID);
	DDX_Text(pDX, IDC_PROP_NAME, m_valueName);
	DDV_MaxChars(pDX, m_valueName, 15);

	DDX_Control(pDX, IDC_PROP_COLOR, m_controlColorCombo);
	DDX_Text(pDX, IDC_PROP_CHA, m_valueCha);
	DDX_Text(pDX, IDC_PROP_TEMP1, m_valueTemp1);
	DDX_Text(pDX, IDC_PROP_TEMP2, m_valueTemp2);
	DDX_Text(pDX, IDC_PROP_TEMP3, m_valueTemp3);
	DDX_Text(pDX, IDC_PROP_DESC, m_valueDesc);
	DDX_Control(pDX, IDC_PROP_SIZE, m_controlSize);
}


BEGIN_MESSAGE_MAP(CAddObjectDlg, CDialog)
END_MESSAGE_MAP()


// CAddObjectDlg �޽��� ó�����Դϴ�.



BOOL CAddObjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CJoshuaGIS3View* pView = (CJoshuaGIS3View*)pFrame->m_wndSplitter.GetPane(0, 0);
	
	m_controlID.SetWindowTextW(pView->ID);

	m_controlColorCombo.AddString(_T("Black"));
	m_controlColorCombo.AddString(_T("Red"));
	m_controlColorCombo.AddString(_T("Green"));
	m_controlColorCombo.AddString(_T("Blue"));
	m_controlColorCombo.AddString(_T("White"));

	m_controlSize.AddString(_T("0.001"));
	m_controlSize.AddString(_T("0.0005")); // ���� ��
	m_controlSize.AddString(_T("0.0015")); // ū ��

	Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CAddObjectDlg::OnOK()
{
	CString colorName;

	m_controlColorCombo.GetLBText(m_controlColorCombo.GetCurSel(), colorName);

	if(!colorName.Compare(_T("Black"))){
		colorCode[0] = "0"; colorCode[1] = "0"; colorCode[2] = "0";
		colorCodeInDouble[0] = 0; colorCodeInDouble[1] = 0; colorCodeInDouble[2] = 0;
	}

	else if(!colorName.Compare(_T("Red"))){
		colorCode[0] = "1"; colorCode[1] = "0"; colorCode[2] = "0";
		colorCodeInDouble[0] = 1; colorCodeInDouble[1] = 0; colorCodeInDouble[2] = 0;
	}

	else if(!colorName.Compare(_T("Green"))){
		colorCode[0] = "0"; colorCode[1] = "1"; colorCode[2] = "0";
		colorCodeInDouble[0] = 0; colorCodeInDouble[1] = 1; colorCodeInDouble[2] = 0;
	}

	else if(!colorName.Compare(_T("Blue"))){
		colorCode[0] = "0"; colorCode[1] = "0"; colorCode[2] = "1";
		colorCodeInDouble[0] = 0; colorCodeInDouble[1] = 0; colorCodeInDouble[2] = 1;
	}

	else if(!colorName.Compare(_T("White"))){
		colorCode[0] = "1"; colorCode[1] = "1"; colorCode[2] = "1";
		colorCodeInDouble[0] = 1; colorCodeInDouble[1] = 1; colorCodeInDouble[2] = 1;
	}

	m_controlSize.GetLBText(m_controlSize.GetCurSel(), size);

	if(!size.Compare(_T("0.001")))
		sizeInDouble = 0.001;

	else if(!size.Compare(_T("0.0005")))
		sizeInDouble = 0.0005;

	else if(!size.Compare(_T("0.0015")))
		sizeInDouble = 0.0015;

	CDialog::OnOK();
}
