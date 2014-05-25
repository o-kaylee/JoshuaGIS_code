
// JoshuaGIS3View.h : CJoshuaGIS3View Ŭ������ �������̽�
//

#pragma once

#include "Camera.h"						//ī�޶� ���				
#include "NaktaVertex.h"				//���� �о��ִ� ���
#include "Face.h"						//���� ������ ����ϴ� ���			
#include "CalculateFace.h"				//�� ������ �����ϰ�, �������͸� ���ϴ� �Լ��� ���� ���
#include "CalculateVertex.h"			//������ ��ֺ��͸� �������ִ� �Լ�
#include "Texture.h"					//�ؽ��Ŀ� ������ ��ġ��Ű�� ����� �����ϴ� ���
#include "Coordinate.h"					//���콺�� Ŭ���� ������ ��ǥ�� ��� ����� �����ϴ� ���
#include "InformationPoint.h"			//�ܺη� ���� �о���� �� �ڷ� + ����ڰ� �߰�/���� �ϴ� ���ڷᰡ ����Ǵ� ��
#include "Information.h"				//��, ��, ��, �ٰ���, ���� �� ��� ������ �ٷ�� ���
#include "InformationDraw.h"			//������ �׷��ִ� ���
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
	NaktaVertex naktaVertex;			//NaktaVetex.obj ���Ϸ� ���� ��Ÿ�� ���� ���������� �о�帲. Vertex Ŭ���� ����
	Face NaktaFace;						//Face Ŭ���� ����
	Texture naktaTexture;				//texture Ŭ���� ����
	Coordinate naktaCoordinate;			//���콺 �Է¿� ���� ��ǥ�� ó��
	InformationDraw naktaDraw;

	//ī�޶� �ʱ����
	Point3 eye1; 
	Point3 look; 
	Vector3 up; 

	// �ؽ���
	GLuint textures[2];				// �ؽ��� 2��

	//���콺
	int MouseModeFlag;
	int MouseDrawFlag;

	//����, ������ �׷��� �� �ʿ���.
	bool isLineFirstStart;
	bool isPolygonFirstStart;

	NaktaVertex* vertexPointer ;		//vertex ���� ���� Ŭ������ ����Ű�� ������ ����
	Face* facePointer;					//face ���� ���� Ŭ������ ����Ű�� ������ ����.
	int numOfFace;
	int g_renderModeFlag;	//�Ϲ�, �ؽ���, wire-frame mode �� �����ҽ� �����Ǵ� ��.
	int g_mouseModeFalg;	//���콺 ��� �÷���

	// Ű ���� ����
	int pushedKey;

	// Display List
	GLuint displayBox1,displayBox2,displayBox3;

	// ȭ����� ����
	float ratio;	//ȭ�� ���� ���� �� ���

	float camX, camY,camZ ;
	float rollAngle;
	float angle;

	//��ü ������ ����
	float xAngle, yAngle, zAngle;		//�ʱ���ġ.. z�� 90 �� ������ |  �̷��� ���̴� ��Ÿ���� �� �̷��� ��������.
	float angleSpeed ;						//������ �ӵ�

	//ī�޶� ���ǵ�
	float cameraSpeed ;
	float lx,ly,lz;
	
	//ī�޶�� ���� �󸶳� ������ �ִ°��� �� ������
	float cameraNear;
	//ī�޶�� ���� �󸶳� �� ���� �� ������
	float cameraFar;

	//upvector
	float cameraUpX, cameraUpY, cameraUpZ; 

	CMainFrame* pFrame;
	CLeftTree* pTree;
	CPropertyForm* pForm;

	float precipitationSpeed;
	int isPrecipitation;

		//// ó�� ����� ���� �θ�(exel file)�� �ڽ�(sheet) ������ �о point, line, polygon ������ �־��ش�.
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

protected: // serialization������ ��������ϴ�.
	CJoshuaGIS3View();
	DECLARE_DYNCREATE(CJoshuaGIS3View)

// ����� ����
public:
	HDC m_hDC;				// GDI Device Context
	HGLRC m_hglRC;			// Rendering Context

	BOOL InitGL();
	void ReSizeGLScene(int width, int height);
	void CJoshuaGIS3View::DrawGLScene();
	BOOL SetPixelformat(HDC hdc);
	void CJoshuaGIS3View::BuildLists();

// Ư���Դϴ�.
public:
	CJoshuaGIS3Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CJoshuaGIS3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CPoint m_ptMouse;			// ���콺 �������� ��ǥ
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

#ifndef _DEBUG  // JoshuaGIS3View.cpp�� ����� ����
inline CJoshuaGIS3Doc* CJoshuaGIS3View::GetDocument() const
   { return reinterpret_cast<CJoshuaGIS3Doc*>(m_pDocument); }
#endif

