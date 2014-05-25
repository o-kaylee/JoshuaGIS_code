
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "JoshuaGIS3.h"

#include "MainFrm.h"

#include "JoshuaGIS3Doc.h"
#include "JoshuaGIS3View.h"
#include "LeftTree.h"
#include "PropertyForm.h"

#include "AddExcelDlg.h"
#include "AddSheetDlg.h"
#include "DeleteExcelDlg.h"
#include "RemoveSheetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_ADD_EXCEL, &CMainFrame::OnAddExcel)
	ON_COMMAND(ID_ADD_SHEET, &CMainFrame::OnAddSheet)
	ON_COMMAND(ID_DELETE_EXCEL, &CMainFrame::OnDeleteExcel)
	ON_COMMAND(ID_DELETE_SHEET, &CMainFrame::OnDeleteSheet)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if(!m_wndSplitter.CreateStatic(this, 1, 2))
		return false;
	
	if(!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CJoshuaGIS3View), CSize(1600, 1000), pContext))
		return false;

	if(!m_wndSplitter2.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 1)))
		return false;

	if(!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CLeftTree), CSize(200, 600), pContext))
		return false;

	if(!m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(CPropertyForm), CSize(200, 400), pContext))
		return false;

	SetActiveView((CView*)m_wndSplitter.GetPane(0, 0));

	return TRUE;

	// return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnAddExcel()
{
	CAddExcelDlg* addExcelDlg = new CAddExcelDlg;
	CLeftTree* pTree = (CLeftTree*)this->m_wndSplitter2.GetPane(0, 0);
	CJoshuaGIS3View* pView = (CJoshuaGIS3View*)this->m_wndSplitter.GetPane(0, 0);

	CString new_excelName, new_sheetName;

	if(addExcelDlg->DoModal() == IDOK){
		pTree->addExcel(addExcelDlg->new_excelName, addExcelDlg->new_sheetName);
		//[추가] 
		
		pView->naktaDraw.setNumberOfParent((pView->naktaDraw.getNumberOfParent()+1));
		pView->naktaDraw.setInformationSize((pView->naktaDraw.getNumberOfParent()+1));	

		pView->naktaDraw.informationClass[pTree->fm.getNumOfFiles()].setInformationSize(1);	//자식노드 사이즈 설정
		pView->naktaDraw.informationClass[pTree->fm.getNumOfFiles()].setInformationSize(1);	//자식노드 벡터 크기 설정
	}
}

void CMainFrame::OnAddSheet()
{
	CAddSheetDlg* addSheetDlg = new CAddSheetDlg;
	CLeftTree* pTree = (CLeftTree*)this->m_wndSplitter2.GetPane(0, 0);
	CJoshuaGIS3View* pView = (CJoshuaGIS3View*)this->m_wndSplitter.GetPane(0, 0);

	ExcelFile *eFile;
	int i;

	if(addSheetDlg->DoModal() == IDOK){
		pTree->addSheet(addSheetDlg->old_excelName, addSheetDlg->new_sheetName);
		//[추가] 

		//유저가 어떤 파일에 시트를 추가하는지
		
			for( i = 0 ; i < pTree->fm.getNumOfFiles();i++){
				eFile = pTree->fm.getFile(i);
				if(strcmp(eFile->getFileName(), (LPSTR)(LPCTSTR)addSheetDlg->old_excelName))
					break;
			}

		//	i 가 말하는게 index
		pView->naktaDraw.informationClass[i].setInformationSize(pView->naktaDraw.informationClass[1].getNumberOfChild());
	}	
}

void CMainFrame::OnDeleteExcel()
{
	//복붙
	CDeleteExcelDlg* deleteExcelDlg = new CDeleteExcelDlg;
	CLeftTree* pTree = (CLeftTree*)this->m_wndSplitter2.GetPane(0, 0);


	if(deleteExcelDlg->DoModal() == IDOK)
		pTree->deleteExcel(deleteExcelDlg->delete_excelName);

}

void CMainFrame::OnDeleteSheet()
{
	CRemoveSheetDlg* removeSheetDlg = new CRemoveSheetDlg;
	CLeftTree* pTree = (CLeftTree*)this->m_wndSplitter2.GetPane(0, 0);

	if(removeSheetDlg->DoModal() == IDOK)
		pTree->deleteSheet(removeSheetDlg->excelFileName, removeSheetDlg->sheetName);

}
