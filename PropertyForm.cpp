// PropertyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JoshuaGIS3.h"
#include "PropertyForm.h"


// CPropertyForm

IMPLEMENT_DYNCREATE(CPropertyForm, CFormView)

CPropertyForm::CPropertyForm()
	: CFormView(CPropertyForm::IDD)
	, m_valueName(_T(""))
	, m_valueSize(_T(""))
	, m_valueCha(_T(""))
	, m_valueTemp1(_T(""))
	, m_valueTemp2(_T(""))
	, m_valueTemp3(_T(""))
	, m_valueDesc(_T(""))
{

}

CPropertyForm::~CPropertyForm()
{
}

void CPropertyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROP_ID, m_controlID);

	DDX_Control(pDX, IDC_PROP_NAME, m_controlName);
	DDX_Text(pDX, IDC_PROP_NAME, m_valueName);
	DDX_Control(pDX, IDC_PROP_SIZE, m_controlSize);
	DDX_Text(pDX, IDC_PROP_SIZE, m_valueSize);
	DDX_Control(pDX, IDC_PROP_CHA, m_controlCha);
	DDX_Text(pDX, IDC_PROP_CHA, m_valueCha);
	DDX_Control(pDX, IDC_PROP_TEMP1, m_controlTemp1);
	DDX_Text(pDX, IDC_PROP_TEMP1, m_valueTemp1);
	DDX_Control(pDX, IDC_PROP_TEMP2, m_controlTemp2);
	DDX_Text(pDX, IDC_PROP_TEMP2, m_valueTemp2);
	DDX_Control(pDX, IDC_PROP_TEMP3, m_controlTemp3);
	DDX_Text(pDX, IDC_PROP_TEMP3, m_valueTemp3);
	DDX_Control(pDX, IDC_PROP_DESC, m_controlDesc);
	DDX_Text(pDX, IDC_PROP_DESC, m_valueDesc);
	DDX_Control(pDX, IDC_PROP_COLOR, m_controlColor);
}

BEGIN_MESSAGE_MAP(CPropertyForm, CFormView)
END_MESSAGE_MAP()


// CPropertyForm 진단입니다.

#ifdef _DEBUG
void CPropertyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPropertyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPropertyForm 메시지 처리기입니다.


void CPropertyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

}


void CPropertyForm::initialize(void)
{
	m_controlID.SetWindowTextW(_T(" "));
	m_controlName.SetWindowTextW(_T(" "));
	m_controlSize.SetWindowTextW(_T(" "));
	m_controlCha.SetWindowTextW(_T(" "));
	m_controlTemp1.SetWindowTextW(_T(" "));
	m_controlTemp2.SetWindowTextW(_T(" "));
	m_controlTemp3.SetWindowTextW(_T(" "));
	m_controlDesc.SetWindowTextW(_T(" "));
	m_controlColor.SetWindowTextW(_T(" "));
}
