// LeftTree.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JoshuaGIS3.h"
#include "LeftTree.h"

#include "MainFrm.h"
#include"JoshuaGIS3View.h"

// CLeftTree

IMPLEMENT_DYNCREATE(CLeftTree, CTreeView)

CLeftTree::CLeftTree()
: parentIndex(0)
, childIndex(0)
{
}

CLeftTree::~CLeftTree()
{
}

BEGIN_MESSAGE_MAP(CLeftTree, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_CLICK, &CLeftTree::OnNMClick)
END_MESSAGE_MAP()


// CLeftTree 진단입니다.

#ifdef _DEBUG
void CLeftTree::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftTree 메시지 처리기입니다.


int CLeftTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CTreeCtrl &List = GetTreeCtrl();
	List.ModifyStyle(NULL, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_CHECKBOXES | TVS_SHOWSELALWAYS);
	TreeDraw();
	//root = List.InsertItem(_T("root"),0,0,TVI_ROOT,TVI_LAST);
	//child = List.InsertItem(_T("child"),0,0,root,TVI_LAST);
	return 0;
}


void CLeftTree::TreeDraw()
{
	CString fileName, sheetName;
	int numSheets;
	
	fm.FileLoad("manageExcel.xls");
	CTreeCtrl &List = GetTreeCtrl();
	List.DeleteAllItems();

	numFiles = fm.getNumOfFiles();

	for(int i=0; i<numFiles; i++)
	{
		ExcelFile *eFile = fm.getFile(i);
		fileName = eFile->getFileName();
		root[i] = List.InsertItem(fileName,0,0,TVI_ROOT,TVI_LAST);

		numSheets = eFile->getNumOfSheets();
		for(int j=0; j<numSheets; j++)
		{
			Sheet* sheet = eFile->getSheet(j);
			sheetName = sheet->getSheetName();
			child[i][j] = List.InsertItem(sheetName,0,0,root[i],TVI_LAST);
		}
		
	}
}

void CLeftTree::addExcel(CString new_excelName, CString new_sheetName)
{
	CTreeCtrl &List = GetTreeCtrl();
	List.DeleteAllItems();
	fm.addFile(new_excelName, new_sheetName);
	fm.intialize(TRUE);
	TreeDraw();
}

void CLeftTree::addSheet(CString filename, CString sheetname)
{
	CTreeCtrl &List = GetTreeCtrl();
	List.DeleteAllItems();
	fm.addSheet(filename, sheetname);
	fm.intialize(FALSE);
	TreeDraw();
}

void CLeftTree::deleteSheet(CString filename, CString sheetname)
{
	CTreeCtrl &List = GetTreeCtrl();
	List.DeleteAllItems();
	fm.deleteSheet(filename, sheetname);
	fm.intialize(0);
	TreeDraw();
}

void CLeftTree::deleteExcel(CString filename)
{
	CTreeCtrl &List = GetTreeCtrl();
	List.DeleteAllItems();
	fm.deleteFile(filename);
	fm.intialize(2);
	TreeDraw();
}

int* CLeftTree::getIndex()//현재 클릭된 거 인덱스 받아오기
{
	int index[2];
	int i=0,j=0;
	bool rootFind =FALSE,childFind=FALSE;
	CTreeCtrl &List = GetTreeCtrl();

	int childIndex =0;
	int parentIndex =0;

	HTREEITEM _root;
	HTREEITEM _child;

	_child = List.GetSelectedItem(); //현재 선택된 것의 THREETIEM을 리턴한다.
	_root = List.GetParentItem(_child);

	for(i=0; i<100; i++){
		if(root[i] == _root){
			for(j=0; j<100; j++){
				if(child[i][j] == _child){
					childFind = TRUE;
					break;
				}
			}
			rootFind = TRUE;
			break;
		}
	}

	//제대로 찾은게 아니면...
	if(!(rootFind || childFind))
	{
		AfxMessageBox(_T("Please select correct sheet"));
		return NULL;
	}

	index[0] = i;
	index[1] = j;

	return index;
}

char* CLeftTree::getParentName(int index)
{
	CTreeCtrl &List = GetTreeCtrl();
	CString itemText = List.GetItemText(root[index]);
	char* buffer=new char[itemText.GetLength()+1];
	WideCharToMultiByte(CP_ACP,0,itemText,-1,buffer,itemText.GetLength()+1,NULL,NULL);

	return buffer;
}
char* CLeftTree::getChildSheetName(int parentIndex, int sheetIndex)
{
	CTreeCtrl &List = GetTreeCtrl();
	CString itemText = List.GetItemText(child[parentIndex][sheetIndex]);
	char* buffer=new char[itemText.GetLength()+1];
	WideCharToMultiByte(CP_ACP,0,itemText,-1,buffer,itemText.GetLength()+1,NULL,NULL);

	return buffer;
}


CString CLeftTree::getChecked(void)
{
	CString sheetName;

	CTreeCtrl &List = GetTreeCtrl();

	return CString();
}


void CLeftTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CJoshuaGIS3View* pView = (CJoshuaGIS3View*)pFrame->m_wndSplitter.GetPane(0, 0);

	CTreeCtrl &List = GetTreeCtrl();
	CPoint point;
	UINT nFlags = 0;
	CString sheetName, fileName; 
	int index = 0;
	bool rootFind =FALSE,childFind=FALSE;
	int i = 0; int j = 0;

	GetCursorPos(&point);
	::ScreenToClient(List.m_hWnd, &point);

	HTREEITEM hItem = List.HitTest(point, &nFlags);
	HTREEITEM hParentItem = List.GetParentItem(hItem);

	// 아이템이 존재하고 체크박스에 이벤트가 발생했다면
	if(hItem != NULL && (nFlags & TVHT_ONITEMSTATEICON) != 0){
		if(!List.GetCheck(hItem)){
			if(!List.GetChildItem(hItem)){ // Child item이 있다면 이건 filename이므로 아무 일도 하지 않음.

				sheetName = List.GetItemText(hItem);
				fileName = List.GetItemText(hParentItem);
				HTREEITEM _child = hItem;
				HTREEITEM _root = hParentItem;

				for(i = 0; i < 100; i++){
					if(root[i] == _root){
						for(j = 0; j < 100; j++){
							if(child[i][j] == _child){
								childFind = TRUE;
								break;
							}
						}
			rootFind = TRUE;
			break;
					}
				}
				// 체크됨
				parentIndex = i;
				childIndex = j;

				pView->naktaDraw.informationClass[i].setIsChildClicked(j,true);
			}
		}

		else{
			HTREEITEM _child = hItem;
			HTREEITEM _root = hParentItem;

			for(i = 0; i < 100; i++){
				if(root[i] == _root){
					for(j = 0; j < 100; j++){
						if(child[i][j] == _child){
							childFind = TRUE;
							break;
						}
					}
			rootFind = TRUE;
			break;
				}
			}
			// 체크 해제됨
			parentIndex = i;
			childIndex = j;
			
			pView->naktaDraw.informationClass[i].setIsChildClicked(j,false);
		}

		pView->DrawGLScene();
	}

}