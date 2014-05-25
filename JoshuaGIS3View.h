
// JoshuaGIS3View.h : CJoshuaGIS3View 클래스의 인터페이스
//

#pragma once

#include "Camera.h"						//카메라 헤더				
#include "NaktaVertex.h"				//정점 읽어주는 헤더
#include "Face.h"						//면의 정보를 담당하는 헤더			
#include "CalculateFace.h"				//면 정보를 구성하고, 법선벡터를 구하는 함수를 가진 헤더
#include "CalculateVertex.h"			//정점의 노멀벡터를 셋팅해주는 함수
#include "Texture.h"					//텍스쳐와 정점을 일치시키는 기능을 제공하는 헤더
#include "Coordinate.h"					//마우스가 클릭한 지점의 좌표를 얻는 기능을 제공하는 헤더
#include "InformationPoint.h"			//외부로 부터 읽어들인 점 자료 + 사용자가 추가/삭제 하는 점자료가 저장되는 곳
#include "Information.h"				//점, 선, 원, 다각형, 나무 등 모든 정보를 다루는 헤더
#include "InformationDraw.h"			//정보를 그려주는 헤더
#include "atltypes.h"

#include "JoshuaGIS3Doc.h"
#include "MainFrm.h"
#include "LeftTree.h"
#include "PropertyForm.h"
#include "AddObjectDlg.h"

class CJoshuaGIS3View : public CView
{

public:
	Camera cam;							// global camera object 
	NaktaVertex naktaVertex;			//NaktaVetex.obj 파일로 부터 낙타섬 관련 정점정보를 읽어드림. Vertex 클래스 선언
	Face NaktaFace;						//Face 클래스 선언
	Texture naktaTexture;				//texture 클래스 선언
	Coordinate naktaCoordinate;			//마우스 입력에 따른 좌표값 처리
	InformationDraw naktaDraw;

	//카메라 초기셋팅
	Point3 eye1; 
	Point3 look; 
	Vector3 up; 

	// 텍스쳐
	GLuint textures[2];				// 텍스쳐 2개

	//마우스
	int MouseModeFlag;
	int MouseDrawFlag;

	//라인, 폴리곤 그려줄 시 필요함.
	bool isLineFirstStart;
	bool isPolygonFirstStart;

	NaktaVertex* vertexPointer ;		//vertex 관련 정보 클래스를 가리키는 포인터 변수
	Face* facePointer;					//face 관련 정보 클래스를 가리키는 포인터 변수.
	int numOfFace;
	int g_renderModeFlag;	//일반, 텍스쳐, wire-frame mode 를 변경할시 참조되는 값.
	int g_mouseModeFalg;	//마우스 모드 플래그

	// 키 조작 관련
	int pushedKey;

	// Display List
	GLuint displayBox1,displayBox2,displayBox3;

	// 화면관련 설정
	float ratio;	//화면 비율 맞출 시 사용

	float camX, camY,camZ ;
	float rollAngle;
	float angle;

	//물체 돌리는 각도
	float xAngle, yAngle, zAngle;		//초기위치.. z가 90 인 이유는 |  이렇게 보이는 낙타섬을 ㅡ 이렇게 보기위함.
	float angleSpeed ;						//돌리는 속도

	//카메라 스피드
	float cameraSpeed ;
	float lx,ly,lz;
	
	//카메라로 부터 얼마나 가까이 있는것을 볼 것인지
	float cameraNear;
	//카메라로 부터 얼마나 먼 것을 볼 것인지
	float cameraFar;

	//upvector
	float cameraUpX, cameraUpY, cameraUpZ; 

	CMainFrame* pFrame;
	CLeftTree* pTree;
	CPropertyForm* pForm;

	float precipitationSpeed;
	int isPrecipitation;

		//// 처음 실행시 각각 부모(exel file)과 자식(sheet) 정보를 읽어서 point, line, polygon 정보를 넣어준다.
	int numberOfParentNode ;
	int numberOfChildNode ;

	int numberOfPoint;
	int numberOfLine;
	int numberOfPolygon;

	int tempPointIndex ;
	int tempLineIndex ;
	int tempPolygonIndex ;

	int tempID;
	double tempX, tempY, tempZ, tempSize, tempColorRed,tempColorBlue,tempColorGreen;
	int tempSwitchVariable;

	char* parentName;
	char* childName;
	
	CAddObjectDlg* addObjectDlg;

	CString ID;

protected: // serialization에서만 만들어집니다.
	CJoshuaGIS3View();
	DECLARE_DYNCREATE(CJoshuaGIS3View)

// 사용자 정의
public:
	HDC m_hDC;				// GDI Device Context
	HGLRC m_hglRC;			// Rendering Context

	BOOL InitGL();
	void ReSizeGLScene(int width, int height);
	void CJoshuaGIS3View::DrawGLScene();
	BOOL SetPixelformat(HDC hdc);
	void CJoshuaGIS3View::BuildLists();

// 특성입니다.
public:
	CJoshuaGIS3Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CJoshuaGIS3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CPoint m_ptMouse;			// 마우스 포인터의 좌표
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRendermodeNormal();
	afx_msg void OnRendermodeTexture();
	afx_msg void OnRendermodeWire();
	afx_msg void OnDrawmodePoint();
	afx_msg void OnDrawmodeLines();
	afx_msg void OnDrawmodePolygon();
	void selectObjects(GLint x, GLint y);
	void processSelect(GLuint* index);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	afx_msg void OnMousemodeSelectmode();
	afx_msg void OnReturnSelectmode();
	afx_msg void OnSaveLine();
	afx_msg void OnPrecipitationmodeX1();
	afx_msg void OnPrecipitationmodeX2();
	afx_msg void OnPrecipitationmodeX3();
	afx_msg void OnPrecipitationmodeX4();
	afx_msg void OnPrecipitationmodeX5();
	void drawPrecipitation(float increaseRate);
	float cubeZ;
	void drawCubePrecipitation(void);
	afx_msg void OnPrecipitationmodePrecipitationmodeoff();
};

#ifndef _DEBUG  // JoshuaGIS3View.cpp의 디버그 버전
inline CJoshuaGIS3Doc* CJoshuaGIS3View::GetDocument() const
   { return reinterpret_cast<CJoshuaGIS3Doc*>(m_pDocument); }
#endif

