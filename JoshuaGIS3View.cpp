
// JoshuaGIS3View.cpp : CJoshuaGIS3View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "JoshuaGIS3.h"
#endif

#include "JoshuaGIS3Doc.h"
#include "JoshuaGIS3View.h"

#define Z_DIVIDER 2500

#define IMAGE_WIDTH_HEIGHT 4096
#define IMAGE_BOUNDARY_WIDTH 4096	 
#define IMAGE_BOUNDARY_HEIGHT 2762

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJoshuaGIS3View

IMPLEMENT_DYNCREATE(CJoshuaGIS3View, CView)

BEGIN_MESSAGE_MAP(CJoshuaGIS3View, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_RENDERMODE_NORMAL, &CJoshuaGIS3View::OnRendermodeNormal)
	ON_COMMAND(ID_RENDERMODE_TEXTURE, &CJoshuaGIS3View::OnRendermodeTexture)
	ON_COMMAND(ID_RENDERMODE_WIRE, &CJoshuaGIS3View::OnRendermodeWire)
	ON_COMMAND(ID_DRAWMODE_POINT, &CJoshuaGIS3View::OnDrawmodePoint)
	ON_COMMAND(ID_DRAWMODE_LINES, &CJoshuaGIS3View::OnDrawmodeLines)
	ON_COMMAND(ID_DRAWMODE_POLYGON, &CJoshuaGIS3View::OnDrawmodePolygon)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MOUSEMODE_SELECTMODE, &CJoshuaGIS3View::OnMousemodeSelectmode)
	ON_COMMAND(ID__RETURN_SELECTMODE, &CJoshuaGIS3View::OnReturnSelectmode)
	ON_COMMAND(ID__SAVE_LINE, &CJoshuaGIS3View::OnSaveLine)
	ON_COMMAND(ID_PRECIPITATIONMODE_X1, &CJoshuaGIS3View::OnPrecipitationmodeX1)
	ON_COMMAND(ID_PRECIPITATIONMODE_X2, &CJoshuaGIS3View::OnPrecipitationmodeX2)
	ON_COMMAND(ID_PRECIPITATIONMODE_X3, &CJoshuaGIS3View::OnPrecipitationmodeX3)
	ON_COMMAND(ID_PRECIPITATIONMODE_X4, &CJoshuaGIS3View::OnPrecipitationmodeX4)
	ON_COMMAND(ID_PRECIPITATIONMODE_X5, &CJoshuaGIS3View::OnPrecipitationmodeX5)
	ON_COMMAND(ID_PRECIPITATIONMODE_PRECIPITATIONMODEOFF, &CJoshuaGIS3View::OnPrecipitationmodePrecipitationmodeoff)
END_MESSAGE_MAP()

// CJoshuaGIS3View ����/�Ҹ�

CJoshuaGIS3View::CJoshuaGIS3View()
	: cubeZ(0)
{
	m_ptMouse = CPoint(0, 0);

	naktaVertex.init("NaktaVertex.obj");			//NaktaVetex.obj ���Ϸ� ���� ��Ÿ�� ���� ���������� �о�帲. Vertex Ŭ���� ����
	NaktaFace.init(9900);								//Face Ŭ���� ����
	naktaTexture.init(true);

	//ī�޶� �ʱ����
	eye1.setPoint3(25.698f, 85.0335f,0.24f);
	look.setPoint3(25.698f, 85.0335f, 0.24-0.00001f);
	up.set(0, 1, 0); 

	//���콺
	MouseModeFlag=0;
	MouseDrawFlag=0;

	//����, ������ �׷��� �� �ʿ���.
	isLineFirstStart=true;
	isPolygonFirstStart  = true;

	vertexPointer = &naktaVertex;							//vertex ���� ���� Ŭ������ ����Ű�� ������ ����
	facePointer = &NaktaFace;								//face ���� ���� Ŭ������ ����Ű�� ������ ����.
	numOfFace=0;

	g_renderModeFlag=1;	//�Ϲ�, �ؽ���, wire-frame mode �� �����ҽ� �����Ǵ� ��.

	camX= 25.698f, camY= 85.0335f,camZ = 0.5f;
	xAngle=0, yAngle=0, zAngle=0;		//�ʱ���ġ.. z�� 90 �� ������ |  �̷��� ���̴� ��Ÿ���� �� �̷��� ��������.
	angleSpeed = 0.04;						//������ �ӵ�
	cameraSpeed  = 0.00004;
	lx=0.0f,ly=0.0f,lz=-1.0f;
	cameraNear = 0.005;
	cameraFar = 1000;

	



	//opengl �ϱ����� ����ؾ� �ϴ� �͵� (���� ���� �ҷ�����, face ����, �������� ����)
	CalculateFace calculateFace(true);
	CalculateVertex calculateVertex(true);
		//�����
	calculateFace.vertexToFace(facePointer);//�������� ���� ������ ����
	calculateFace.setFaceNormalVector(facePointer,vertexPointer);	//���� �������͸� ���Ѵ�

	numOfFace = facePointer->getNumOfFace();	//�������Ҷ� �� ������ �˾ƾ� for �쿡�� i �� 0���� ������ ���ƾ� �ϴ��� �� �� ����.

		//vertex����
	naktaVertex.setVertexNormalVectorSize(naktaVertex.getNumOfVertex());	//������ ���������� ����� ���� �Ҵ� �� �ʱ�ȭ
	calculateVertex.setVertexNormalVector(facePointer,vertexPointer);
	
	
	//�� ��������
	precipitationSpeed = 0;
	isPrecipitation = false;
}

CJoshuaGIS3View::~CJoshuaGIS3View()
{
}

BOOL CJoshuaGIS3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CJoshuaGIS3View �׸���

void CJoshuaGIS3View::OnDraw(CDC* /*pDC*/)
{
	CJoshuaGIS3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	DrawGLScene();
	
}


// CJoshuaGIS3View ����

#ifdef _DEBUG
void CJoshuaGIS3View::AssertValid() const
{
	CView::AssertValid();
}

void CJoshuaGIS3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJoshuaGIS3Doc* CJoshuaGIS3View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJoshuaGIS3Doc)));
	return (CJoshuaGIS3Doc*)m_pDocument;
}
#endif //_DEBUG


// CJoshuaGIS3View �޽��� ó����
BOOL CJoshuaGIS3View::SetPixelformat(HDC hdc)
{
	int pixelformat;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
		1, // default version
		PFD_DRAW_TO_WINDOW | // support window
		PFD_SUPPORT_OPENGL | // support OpenGL
		PFD_GENERIC_FORMAT |
		PFD_DOUBLEBUFFER, // double buffered
		PFD_TYPE_RGBA, // RGBA type
		32, // 32-bit color depth
		0, 0, 0, 0, 0, 0, // color bits ignored
		8, // no alpha buffer
		0, // shift bit ignored
		8, // no accumulation buffer
		0, 0, 0, 0, // accum bits ignored
		16, // 16-bit z-buffer
		0, // no stencil buffer
		0, // no auxiliary buffer
		PFD_MAIN_PLANE, // main layer
		0, // reserved
		0, 0, 0 // layer masks ignored
	};

	// choose best matching pixel format
	if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE ) {
	//MessageBox( "ChoosePixelFormat failed", "Error", MB_OK);
	return FALSE;
	}
	// set pixel format to device context

	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE) {
	//MessageBox( "SetPixelFormat failed", "Error", MB_OK);
	return FALSE;
	}

	return TRUE;
}

BOOL CJoshuaGIS3View::InitGL(void)
{
	BuildLists();									// Jump To The Code That Creates Our Display Lists
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glEnable(GL_LIGHT0);								// Quick And Dirty Lighting (Assumes Light0 Is Set Up)
	//glEnable(GL_LIGHTING);								// Enable Lighting
	//glEnable(GL_COLOR_MATERIAL);						// Enable Material Coloring
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glShadeModel( GL_SMOOTH   );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	cam.set(eye1, look, up); // make the initial camera
	cam.roll(90);
	return true;
}

void CJoshuaGIS3View::ReSizeGLScene(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;	//[do]
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the clipping volume
	float size = 12.1;
	
	gluPerspective(45,ratio,0.00005,100);
	glMatrixMode(GL_MODELVIEW);
}

void CJoshuaGIS3View::DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	
	for(int i = 0; i < (pTree->fm.getNumOfFiles());  i++){
		naktaDraw.drawInformation(i);
	}
	
	glPushMatrix();
	if(g_renderModeFlag == 0)	//�Ϲ� ���
		glCallList(displayBox2);
	else if(g_renderModeFlag == 1)	//�ؽ���
		glCallList(displayBox3);
	else if(g_renderModeFlag == 2)	//wire-frame {
		glCallList(displayBox1);
		
	glPopMatrix(); 
	glPopMatrix();


	if(isPrecipitation = true){
		//�ö���� �Լ� �׷���
		drawCubePrecipitation();
	}


	SwapBuffers(m_hDC);
}

int CJoshuaGIS3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hDC = GetDC()->m_hDC;

	// set the pixel format
	if(!SetPixelformat(m_hDC))
		return -1;

	// create rendering context and make it current
	m_hglRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hglRC);

	InitGL();
	

	return 0;
}


void CJoshuaGIS3View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hglRC);
}


void CJoshuaGIS3View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	ReSizeGLScene(cx, cy);
}

void CJoshuaGIS3View::BuildLists()
{
	int point1, point2, point3; //�׸��� ����

	displayBox1=glGenLists(2);				// 2���� �ٸ� ����Ʈ�� ����

	///////////////////////////////////////////////////////////////////////////////////////////////����Ʈ�ڽ� 1 ����
	glNewList(displayBox1,GL_COMPILE);		// ����Ʈ�ڽ� ù��° ���� �����Ͻ� �̸� �����
			
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);

	//����Ʈ�ڽ�1 �� �׷��ٶ� �ʿ��� ������
	glBegin(GL_TRIANGLES);{
	for(int i = 0; i < numOfFace; i++){
		//��ֺ���
		glNormal3f(facePointer->getNormalVectorX(i),facePointer->getNormalVectorY(i),facePointer->getNormalVectorZ(i));
		//����
		glVertex3f(naktaVertex.getVertexX(facePointer->getPoint1(i)),naktaVertex.getVertexY(facePointer->getPoint1(i)),naktaVertex.getVertexZ(facePointer->getPoint1(i))/Z_DIVIDER);
		glVertex3f(naktaVertex.getVertexX(facePointer->getPoint2(i)),naktaVertex.getVertexY(facePointer->getPoint2(i)),naktaVertex.getVertexZ(facePointer->getPoint2(i))/Z_DIVIDER);
		glVertex3f(naktaVertex.getVertexX(facePointer->getPoint3(i)),naktaVertex.getVertexY(facePointer->getPoint3(i)),naktaVertex.getVertexZ(facePointer->getPoint3(i))/Z_DIVIDER);
	}

	}glEnd();
	glEndList();
	////////////////////////////////////////////////////////////////////////////////////////////////����Ʈ�ڽ� 1 ��

	displayBox2 = displayBox1+1;	//�ι�° ����Ʈ �ڽ� ����
	///////////////////////////////////////////////////////////////////////////////////////////////����Ʈ�ڽ� 2 ����
	glNewList(displayBox2,GL_COMPILE);							// Start With The Box List
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);
		//����Ʈ�ڽ�2 �� �׷��ٶ� �ʿ��� ������
		glBegin(GL_TRIANGLES);{
		glColor3f(0.9, 0.9f, 0.9f);

		for(int i = 0; i < numOfFace; i++){
			point1 = facePointer->getPoint1(i);		//�� �ϳ��� ù��° �� vertex�� index
			point2 = facePointer->getPoint2(i);		//�� �ϳ��� �ι�° �� vertex�� index
			point3 = facePointer->getPoint3(i);		//�� �ϳ��� ����° �� vertex�� index
			
			//3���� ��ֺ��Ϳ� ���� ����
			glNormal3f(naktaVertex.getVertexNormalVectorX(point1),naktaVertex.getVertexNormalVectorY(point1),naktaVertex.getVertexNormalVectorZ(point1));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint1(i)),naktaVertex.getVertexY(facePointer->getPoint1(i)),naktaVertex.getVertexZ(facePointer->getPoint1(i))/Z_DIVIDER);
			
			glNormal3f(naktaVertex.getVertexNormalVectorX(point2),naktaVertex.getVertexNormalVectorY(point2),naktaVertex.getVertexNormalVectorZ(point2));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint2(i)),naktaVertex.getVertexY(facePointer->getPoint2(i)),naktaVertex.getVertexZ(facePointer->getPoint2(i))/Z_DIVIDER);
			
			glNormal3f(naktaVertex.getVertexNormalVectorX(point3),naktaVertex.getVertexNormalVectorY(point3),naktaVertex.getVertexNormalVectorZ(point3));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint3(i)),naktaVertex.getVertexY(facePointer->getPoint3(i)),naktaVertex.getVertexZ(facePointer->getPoint3(i))/Z_DIVIDER);
		}
	}glEnd();
	glEndList();
	///////////////////////////////////////////////////////////////////////////////////////////////����Ʈ�ڽ� 2 ��

	displayBox3 = displayBox1+2;	//����° ����Ʈ �ڽ� ����
	///////////////////////////////////////////////////////////////////////////////////////////////����Ʈ�ڽ� 3 ����
	glNewList(displayBox3,GL_COMPILE);							// Start With The Box List
	glPolygonMode(GL_FRONT,GL_FILL);
	naktaTexture.setInformation(IMAGE_WIDTH_HEIGHT, IMAGE_BOUNDARY_WIDTH, IMAGE_BOUNDARY_HEIGHT);	//�ҷ��� �̹��� ������ �� �� ���� ���ϴ� �ʺ� ���̸� ����
	naktaTexture.initTexture("naktaImage.bmp", textures);
	naktaTexture.setRow(50);
	naktaTexture.setColumn(100);
	naktaTexture.setXYrate();
	glPolygonMode(GL_BACK,GL_FILL);
		//����Ʈ�ڽ�3 �� �׷��ٶ� �ʿ��� ������
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.9f, 0.9f, 0.9f);
	glBindTexture(GL_TEXTURE_2D,textures[0]);

		
		
		glBegin(GL_TRIANGLES);{
		
		for(int i = 0; i < numOfFace; i++){
			point1 = facePointer->getPoint1(i);		//�� �ϳ��� ù��° �� vertex�� index
			point2 = facePointer->getPoint2(i);		//�� �ϳ��� �ι�° �� vertex�� index
			point3 = facePointer->getPoint3(i);		//�� �ϳ��� ����° �� vertex�� index
			
			//�ؽ��� ��ǥ, 3���� ��ֺ��Ϳ� ���� ����
			glTexCoord2f(naktaTexture.getCoordinatedX(point1),naktaTexture.getCoordinatedY(point1));
			glNormal3f(naktaVertex.getVertexNormalVectorX(point1),naktaVertex.getVertexNormalVectorY(point1),naktaVertex.getVertexNormalVectorZ(point1));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint1(i)),naktaVertex.getVertexY(facePointer->getPoint1(i)),naktaVertex.getVertexZ(facePointer->getPoint1(i))/Z_DIVIDER);
			
			glTexCoord2f(naktaTexture.getCoordinatedX(point2),naktaTexture.getCoordinatedY(point2));
			glNormal3f(naktaVertex.getVertexNormalVectorX(point2),naktaVertex.getVertexNormalVectorY(point2),naktaVertex.getVertexNormalVectorZ(point2));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint2(i)),naktaVertex.getVertexY(facePointer->getPoint2(i)),naktaVertex.getVertexZ(facePointer->getPoint2(i))/Z_DIVIDER);
			
			glTexCoord2f(naktaTexture.getCoordinatedX(point3),naktaTexture.getCoordinatedY(point3));
			glNormal3f(naktaVertex.getVertexNormalVectorX(point3),naktaVertex.getVertexNormalVectorY(point3),naktaVertex.getVertexNormalVectorZ(point3));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint3(i)),naktaVertex.getVertexY(facePointer->getPoint3(i)),naktaVertex.getVertexZ(facePointer->getPoint3(i))/Z_DIVIDER);
		}

	}glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	///////////////////////////////////////////////////////////////////////////////////////////////����Ʈ�ڽ� 3 ��
}

void CJoshuaGIS3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar){
			//Camera move
				//x-axis move
			case 81: cam.yaw(-2.5);  break; // q
			case 87: cam.yaw(2.5);  break; // w
		
				//y- axis move
			case 65: cam.pitch(-2.5);	break; // a
			case 83: cam.pitch(2.5);	break; // s
			
				//z-axis move
			case 90: cam.slide(0,0, -0.006);break; // z
			case 88: cam.slide(0,0, 0.006); break; // x

			//Object Move
				//x-axis
			case 69: cam.set(eye1, look, up); // �ʱ���·� �ٲ� e
				 cam.roll(90);  break;
		
				//z-axis
			case 68: cam.roll( -2.17);break; // d
	
			case 70: cam.roll(2.17);	break; // f
	}

	DrawGLScene();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CJoshuaGIS3View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return true;
	// return CView::OnEraseBkgnd(pDC);
}


void CJoshuaGIS3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CPoint p;
	GetCursorPos(&p);

	CMenu menu;
	if(MouseModeFlag == 1 && MouseDrawFlag == 1){
		menu.LoadMenu(IDR_FLOATING_MENU_LINE);
		CMenu* Dmenu = menu.GetSubMenu(0);

		Dmenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
	}

	else{
		menu.LoadMenu(IDR_FLOATING_MENU);
		CMenu* Dmenu = menu.GetSubMenu(0); //�� �տ� �޴��� ������

		Dmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON , p.x, p.y, this); 
	}

	CView::OnRButtonUp(nFlags, point);
}

// �޴� ó���� �Լ����� ����
void CJoshuaGIS3View::OnRendermodeNormal()
{
	g_renderModeFlag = 0;
	isLineFirstStart = true;
	isPolygonFirstStart = true;

	DrawGLScene();
}

void CJoshuaGIS3View::OnRendermodeTexture()
{
	g_renderModeFlag = 1;
	isLineFirstStart = true;
	isPolygonFirstStart = true;

	DrawGLScene();
}

void CJoshuaGIS3View::OnRendermodeWire()
{
	g_renderModeFlag = 2;
	isLineFirstStart = true;
	isPolygonFirstStart = true;

	DrawGLScene();
}

void CJoshuaGIS3View::OnMousemodeSelectmode()
{
	MouseModeFlag = 0;
}

void CJoshuaGIS3View::OnDrawmodePoint()
{
	MouseModeFlag = 1;
	MouseDrawFlag = 0;
}

void CJoshuaGIS3View::OnDrawmodeLines()
{
	MouseModeFlag = 1;
	MouseDrawFlag = 1;
	isLineFirstStart = true;
	isPolygonFirstStart = true;

}

void CJoshuaGIS3View::OnDrawmodePolygon()
{
	MouseModeFlag = 1;
	MouseDrawFlag = 2;
	isLineFirstStart = true;
	isPolygonFirstStart = true;

}

// Line Drawing Mode �޴� ó������ ����
void CJoshuaGIS3View::OnReturnSelectmode()
{
	MouseModeFlag = 0;
}

void CJoshuaGIS3View::OnSaveLine()
{
	ID.Format(_T("%d"), tempID);
	if(addObjectDlg->DoModal() == IDOK);

	else;

}

void CJoshuaGIS3View::selectObjects(GLint x, GLint y)
{
	GLuint selectBuff[64]={};
    GLint hits, viewport[4];
    glSelectBuffer(64, selectBuff);
    glGetIntegerv(GL_VIEWPORT, viewport);
    glMatrixMode(GL_PROJECTION);                           
    glPushMatrix();                                         
    glRenderMode(GL_SELECT);                                
    glLoadIdentity();                                      
    gluPickMatrix(x, viewport[3]-y, 2, 2, viewport);      
	gluPerspective(45,ratio,0.00005,100);
    glMatrixMode(GL_MODELVIEW);                              
    //glLoadIdentity();                                     
    DrawGLScene();                                        
    hits = glRenderMode(GL_RENDER);                      
    if(hits>0) processSelect(selectBuff);                   
    glMatrixMode(GL_PROJECTION);                            
    glPopMatrix();                                           
    glMatrixMode(GL_MODELVIEW);
}

void CJoshuaGIS3View::processSelect(GLuint* index)
{

	CString ID, name, size, characteristic, temp1, temp2, temp3, description, colorR, colorG, colorB, color;
	int childIndex, parentIndex,rowIndex;
	char* parentName, *childName;
	char* buffer="";
	char* name2;

	BasicExcel e;
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;


	// 0�ΰ�� -> Titile: Ŭ���� �׸��� �����ϴ�. �� �����ֱ�. �ٸ��� none �ƴϸ� 0 ����
	if(index[3] == 0){
		pForm->initialize();

		pForm->m_controlID.SetWindowTextW(_T("Ŭ���� object�� �����ϴ�."));
		pForm->m_controlName.SetWindowTextW(_T("None"));
		
		pForm->Invalidate();
	}

	//0�� �ƴѰ�� -> �������� ã�Ƽ� ������ �� �������� ��!!
	else{
		ID.Format(_T("%d"), index[3]);

		//iD: index[3]
			//sheet index
		childIndex = (index[3] /100000) % 100;
			//parentIndex
		parentIndex = (index[3]/10000000)%100;
		
		rowIndex = (index[3]/100)%1000;

		parentName  = pTree->getParentName(parentIndex);
		childName =	pTree->getChildSheetName(parentIndex,childIndex);

		e.Load(parentName);
		sheet = e.GetWorksheet(childName);

		cell = sheet->Cell(rowIndex,5);
		name = (CString)cell->GetString();

		cell = sheet->Cell(rowIndex, 1);
		size =  (CString)cell->GetString();

		cell = sheet->Cell(rowIndex, 6);
		characteristic =  (CString)cell->GetString();

		cell = sheet->Cell(rowIndex, 8);
		temp1 =  (CString)cell->GetString();

		cell = sheet->Cell(rowIndex, 9);
		temp2 =  (CString)cell->GetString();

		cell = sheet->Cell(rowIndex, 10);
		temp3 =  (CString)cell->GetString();

		cell = sheet->Cell(rowIndex, 7);
		description =  (CString)cell->GetString();
		
		cell = sheet->Cell(rowIndex, 2);
		colorR =  (CString)cell->GetString();
		
		cell = sheet->Cell(rowIndex, 3);
		colorG =  (CString)cell->GetString();

		cell = sheet->Cell(rowIndex, 4);
		colorB =  (CString)cell->GetString();

		e.Close();

		if(!colorR.Compare(_T("0")) && !colorG.Compare(_T("0")) && !colorB.Compare(_T("0")))
			color = _T("Black");

		else if(!colorR.Compare(_T("1")) && !colorG.Compare(_T("0")) && !colorB.Compare(_T("0")))
			color = _T("Red");

		else if(!colorR.Compare(_T("0")) && !colorG.Compare(_T("1")) && !colorB.Compare(_T("0")))
			color = _T("Green");

		else if(!colorR.Compare(_T("0")) && !colorG.Compare(_T("0")) && !colorB.Compare(_T("1")))
			color = _T("Blue");

		else if(!colorR.Compare(_T("1")) && !colorG.Compare(_T("1")) && !colorB.Compare(_T("1")))
			color = _T("White");

		pForm->initialize();

		pForm->m_controlID.SetWindowTextW(ID);
		pForm->m_controlName.SetWindowTextW(name);
		pForm->m_controlSize.SetWindowTextW(size);
		pForm->m_controlCha.SetWindowTextW(characteristic);
		pForm->m_controlTemp1.SetWindowTextW(temp1);
		pForm->m_controlTemp2.SetWindowTextW(temp2);
		pForm->m_controlTemp3.SetWindowTextW(temp3);
		pForm->m_controlDesc.SetWindowTextW(description);
		pForm->m_controlColor.SetWindowTextW(color);

		pForm->Invalidate();
	}


	//Ŭ�� �Ǿ��� ��, �ش� ������ ������ �ٲ��ָ� �ɵ�..
	//�ٲٴ� ������, Ŭ���� �� �÷��� �о�鿩�� �ش� vector ��� �÷��� �ٲ��ְ�, clickedID color, clickedID ������ ���� �ִ´�.

	//Ŭ�� �Ǿ��� �� �ش� ���̵� ã�´�..
	

	//�������ٰ� ����

//	int a = 3;
//	char* b = "����";


	//����� ������ �Ӽ�â�� �Ѱ��ش�.

	//�Ӽ�â�� �Ѱ��ִ� �Լ� 


	//�׸��� ������ �̾Ƴ���,


	//�ѱ��.

}

void CJoshuaGIS3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int* index;
	int parentIndex;
	int childIndex;;
	CString floatToStringPointX,floatToStringPointY,floatToStringPointZ ;
	int tempID;
	naktaCoordinate.leftClick(point.x, point.y); // Ŭ���� ������ ���� ��ǥ ����
	GLdouble* clickedXYZ;
	clickedXYZ = naktaCoordinate.getLeftClickedCoordinate();

	/* ������.
	//text��.
	index = pTree->getIndex();
	if(index[0] == index[1]);

	//text�� 2
	test = pTree->getChildSheetName(index[0],index[1]);
	test = pTree->getParentName(index[0]);
	*/
		
	index = pTree->getIndex();

	if(index == NULL)
		return;
	

	parentIndex = index[0]; //�θ��ε���
	childIndex = index[1]; //�ڽ��ε���
	
	if(MouseModeFlag == 0) // select mode
		selectObjects(point.x, point.y);

	else if(MouseModeFlag == 1) // draw mode

		switch(MouseDrawFlag){
		case 0: // point
			//IDgenerator
			
			naktaDraw.informationClass[parentIndex].pointClass[childIndex].getNumberOfPoint();
			tempID = naktaDraw.IdGenerator(parentIndex,childIndex,naktaDraw.informationClass[parentIndex].pointClass[childIndex].getNumberOfPoint()+1,1);
			naktaDraw.informationClass[parentIndex].pointClass[childIndex].addPoint(tempID,clickedXYZ[0], clickedXYZ[1], clickedXYZ[2],0.0,0.1,0.0,0.001);//draw default point
	
			ID.Format(_T("%d"), tempID);
			floatToStringPointX.Format(_T("%f"),clickedXYZ[0]);
			floatToStringPointY.Format(_T("%f"),clickedXYZ[1]);
			floatToStringPointZ.Format(_T("%f"),clickedXYZ[2]);


			if(addObjectDlg->DoModal() == IDOK){
			//ok ���� ���
				//������ �Ʊ� �޾ƿԴ� ������ �Ѱ��ش�.
				ExcelFile *eFile = pTree->fm.getFile(parentIndex);
				Sheet *_sheet = eFile->getSheet(childIndex);
				int lastLine = _sheet->getNumOfItem(); //���� ���� �޾ƿͼ�, ���� �������� �־���..
				//������ �Է��� ������ �����Ϳ� string ���� ����.
				char* buffer = new char[ID.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,ID,-1,buffer,ID.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 0, buffer); //0�� �÷��� ID

				buffer = new char[addObjectDlg->size.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->size,-1,buffer,addObjectDlg->size.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 1, buffer); //1�� Size

				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 2, addObjectDlg->colorCode[0]); //RBG-R ��

				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 3, addObjectDlg->colorCode[1]); //RBG-G ��

				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 4, addObjectDlg->colorCode[2]); //RBG-B ��

				buffer = new char[addObjectDlg->m_valueName.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueName,-1,buffer,addObjectDlg->m_valueName.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 5, buffer); //����

				buffer = new char[addObjectDlg->m_valueCha.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueCha,-1,buffer,addObjectDlg->m_valueCha.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 6, buffer); //Ư��

				buffer = new char[addObjectDlg->m_valueDesc.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueDesc,-1,buffer,addObjectDlg->m_valueDesc.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 7, buffer); //����

				buffer = new char[addObjectDlg->m_valueTemp1.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueTemp1,-1,buffer,addObjectDlg->m_valueTemp1.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 8, buffer); //temp1

				buffer = new char[addObjectDlg->m_valueTemp2.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueTemp2,-1,buffer,addObjectDlg->m_valueTemp2.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 9, buffer); //temp2

				buffer = new char[addObjectDlg->m_valueTemp3.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueTemp3,-1,buffer,addObjectDlg->m_valueTemp3.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 10, buffer); //temp3

				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 11,1); //������

				buffer = new char[floatToStringPointX.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,floatToStringPointX,-1,buffer,floatToStringPointX.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 12, buffer); //x��ǥ

				buffer = new char[floatToStringPointY.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,floatToStringPointY,-1,buffer,floatToStringPointY.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 13, buffer); //y��ǥ

				buffer = new char[floatToStringPointZ.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,floatToStringPointZ,-1,buffer,floatToStringPointZ.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 14, buffer); //z��ǥ
				
				//����� ������ opengl �� �˷���(�÷�, ������)
					//�÷��� ������ �´�
				double RGBred, RGBgreen, RGBblue;
				char* sizeChar = (LPSTR)(LPCTSTR)addObjectDlg->size;

				RGBred = atof(addObjectDlg->colorCode[0]);
				RGBgreen = atof(addObjectDlg->colorCode[1]);
				RGBblue = atof(addObjectDlg->colorCode[2]);

					
					

				naktaDraw.informationClass[parentIndex].pointClass[childIndex].setPointColor(naktaDraw.informationClass[parentIndex].pointClass[childIndex].getLastIndex(),RGBred,RGBgreen,RGBblue);
				naktaDraw.informationClass[parentIndex].pointClass[childIndex].setPointSize(naktaDraw.informationClass[parentIndex].pointClass[childIndex].getLastIndex(), addObjectDlg->sizeInDouble);				
				pTree->fm.getFile(parentIndex)->getSheet(childIndex)->increaseItem();
			}


			else
			// ���⿡ Cancel ������ �� ������ �����				
			//�����ָ� �� ��...
				naktaDraw.informationClass[parentIndex].pointClass[childIndex].deleteRecentPoint();
			// ���⿡ OK ������ �� ������ �����

			break;

		case 1: // line

			if(isLineFirstStart){
				tempID = naktaDraw.IdGenerator(parentIndex,childIndex,naktaDraw.informationClass[parentIndex].linesClass[childIndex].getNumberOfLine()+1,2);
				naktaDraw.informationClass[parentIndex].linesClass[childIndex].createLine(tempID,clickedXYZ[0],clickedXYZ[1],clickedXYZ[2],0.0,0.1,0.0,3.0);//draw default line
						isLineFirstStart = false;
					}

			else
				naktaDraw.informationClass[parentIndex].linesClass[childIndex].addLine(naktaDraw.informationClass[parentIndex].linesClass[childIndex].getLastIndex(),clickedXYZ[0],clickedXYZ[1],clickedXYZ[2]);

			break;

		case 2: // polygon
				if(isPolygonFirstStart){
					tempID = naktaDraw.IdGenerator(parentIndex,childIndex,naktaDraw.informationClass[parentIndex].polygonsClass[childIndex].getNumberOfPolygon()+1,3);
						naktaDraw.informationClass[parentIndex].polygonsClass[childIndex].createPolygon(tempID,clickedXYZ[0],clickedXYZ[1],clickedXYZ[2],0.0,0.0,1.0,3.0);	//draw default polygon
						isPolygonFirstStart = false;
				}
					else{
						naktaDraw.informationClass[parentIndex].polygonsClass[childIndex].addPolygon(naktaDraw.informationClass[parentIndex].polygonsClass[childIndex].getLastIndex(),clickedXYZ[0],clickedXYZ[1],clickedXYZ[2]);
					
				}
					
			break;

		default: // error

			// ����
			break;
	}

	else if(MouseModeFlag == 2){ // object mode

		// TODO
		;
	}

	DrawGLScene();

	CTreeCtrl &List = pTree->GetTreeCtrl();
	
}


void CJoshuaGIS3View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
		
	pFrame = (CMainFrame*)AfxGetMainWnd();
	pTree = (CLeftTree*)pFrame->m_wndSplitter2.GetPane(0, 0);
	pForm = (CPropertyForm*)pFrame->m_wndSplitter2.GetPane(1, 0);

	addObjectDlg = new CAddObjectDlg;
	numberOfParentNode =0;
	 numberOfChildNode =0;

	 numberOfPoint=0;
	 numberOfLine=0;
	 numberOfPolygon=0;

	 tempPointIndex=0 ;
	 tempLineIndex=0 ;
	 tempPolygonIndex=0 ;

	 tempID=0;
	 tempX=0, tempY=0, tempZ=0, tempSize=0, tempColorRed=0,tempColorBlue=0,tempColorGreen=0;
	 tempSwitchVariable=0;

	 parentName=NULL;
	 childName=NULL;



	
	//[����]  �����̳� ��Ʈ �߰��� �θ𰹼�, �ش� �θ� �ڽ��ǰ����� �÷����.(���ͤ� ������ ũ��)
	//1.   �θ��� ������ �����´�.
	numberOfParentNode = pTree->fm.getNumOfFiles(); 
	
		//1-1. �θ��� ��� ���� ����
	naktaDraw.setNumberOfParent(numberOfParentNode);
	
	
	//1-2. �θ��� ���� ũ�� ����
	naktaDraw.setInformationSize(numberOfParentNode);	


		//2. for �� ������ (�θ��� ��� ���� ��ŭ)

		//2-1. �ش� �θ��� �ڽ� ��� ������ ����
		//2-2. �ش� �θ��� �ڽ� ���� ũ�� ����
	
	for(int i = 0 ; i < numberOfParentNode; i++){
		
		ExcelFile* eFile = pTree->fm.getFile(i);
		numberOfChildNode = eFile->getNumOfSheets(); // �ش� �θ��� �ڽĳ�� ũ�� �޾ƿ�

		naktaDraw.informationClass[i].setInformationSize(numberOfChildNode);	//�ڽĳ�� ������ ����
		naktaDraw.informationClass[i].setNumberOfChild(numberOfChildNode);	//�ڽĳ�� ���� ũ�� ����
		
		for(int j = 0 ; j < numberOfChildNode ; j++) 
			naktaDraw.informationClass[i].setIsChildClicked(j,true);	//i���� �θ��� j��° �ڽĳ��� Ŭ�� �ȵǾ� �������� default
	}



	for(int i = 0; i < numberOfParentNode ; i ++){
		ExcelFile* eFile = pTree->fm.getFile(i);

		for(int j= 0; j < eFile->getNumOfSheets(); j++){//�ش� i��° �θ��� �ڽİ���
			
			parentName = pTree->getParentName(i);
			childName = pTree->getChildSheetName(i,j);

			ExcelFile *eFile = pTree->fm.getFile(i);
			Sheet *_sheet = eFile->getSheet(j);
			_sheet->getNumOfItem();


			for(int k = 1 ; k <= _sheet->getNumOfItem(); k++){				//[����]
				tempSwitchVariable = pTree->fm.getDataInt(parentName,childName,k,0);

				switch(tempSwitchVariable%100){
					case 1: numberOfPoint++;   break;
					case 2: numberOfLine++;    break;
					case 3: numberOfPolygon++; break;
					default: break;	//�ͼ��� �������� ������		
				}
			}
			int tempTest;
			tempTest =numberOfPoint;
			//��, ��, �� ���� ����
			naktaDraw.informationClass[i].pointClass[j].setNumberOfPoint(numberOfPoint);
			
			tempTest = naktaDraw.informationClass[i].pointClass[j].getNumberOfPoint();
			naktaDraw.informationClass[i].linesClass[j].setNumberOfLine(numberOfLine);			//���� � �ִ��� ����
			naktaDraw.informationClass[i].polygonsClass[j].setNumberOfPolygon(numberOfPolygon);	//������ � �ִ��� ����

			naktaDraw.informationClass[i].pointClass[j].setLastIndex(numberOfPoint-1);
			naktaDraw.informationClass[i].linesClass[j].setLastIndex(numberOfLine-1);			//���� � �ִ��� ����
			naktaDraw.informationClass[i].polygonsClass[j].setLastIndex(numberOfPolygon-1);	//������ � �ִ��� ����

			//��, ��, �� ���� ũ�� ����
			naktaDraw.informationClass[i].pointClass[j].setVectorSize(numberOfPoint);
			naktaDraw.informationClass[i].linesClass[j].setVectorSize(numberOfLine);
			naktaDraw.informationClass[i].polygonsClass[j].setVectorSize(numberOfPolygon);

			//



			//
		

			//�����͸� exel  �־���
			for(int k = 1 ; k <= _sheet->getNumOfItem() /*�ش� �ڽ��� ������ ������ ����*/; k++){
				tempSwitchVariable = pTree->fm.getDataInt(parentName,childName,k,0);//ID % 100 ������,��,�� �Ӽ� �����Ͽ� �� �־���
				
				switch(tempSwitchVariable%100){
					case 1:	//point ���� �־���
						
						
						tempX = pTree->fm.getDataDouble(parentName,childName,k,12);//[�׿�]��,�� ���� index ����. ������ 1���� �����Ѵٰ� ����
						tempY =  pTree->fm.getDataDouble(parentName,childName,k,13);//[�׿�]��,�� ���� index ����
						tempZ = pTree->fm.getDataDouble(parentName,childName,k,14);//[�׿�]��,�� ���� index ����
						tempSize = pTree->fm.getDataDouble(parentName,childName,k,1);
						tempID =  pTree->fm.getDataDouble(parentName,childName,k,0); //id��
						tempColorRed = pTree->fm.getDataDouble(parentName,childName,k,2);		//red
						tempColorBlue = pTree->fm.getDataDouble(parentName,childName,k,3);		//blue
						tempColorGreen = pTree->fm.getDataDouble(parentName,childName,k,4);		//green


						//i��° �θ�, j��° �ڽ�.
					//get(
						//���̵� ����
							//tempID = naktaDraw.IdGenerator(1,1,1, 1);//[����]
							naktaDraw.informationClass[i].pointClass[j].setPointXYZ(tempPointIndex,tempX,tempY,tempZ);	//����ǥ : x,y,z
							naktaDraw.informationClass[i].pointClass[j].setPointSize(tempPointIndex,tempSize);	//�� ũ��
							naktaDraw.informationClass[i].pointClass[j].setPointID(tempPointIndex,tempID);		//���̵� 
							naktaDraw.informationClass[i].pointClass[j].setPointColor(tempPointIndex,tempColorRed,tempColorBlue,tempColorGreen);	//����	
							tempPointIndex++;
						break;
					case 2:
							//line ���� �־���
						for(int l = 0; l < naktaDraw.informationClass[i].linesClass[j].getNumberOfLine(); l++){		//���� ������ ������ ����..
							naktaDraw.informationClass[i].linesClass[j].lineClass[l].setNumberOfLinePoints( pTree->fm.getDataDouble(parentName,childName,k,12));//�� ������ ��� ������ �̷�� ����
							naktaDraw.informationClass[i].linesClass[j].lineClass[l].setVectorSize(pTree->fm.getDataDouble(parentName,childName,k,12));	//���� ���� ����
							for(int m = 0; m < naktaDraw.informationClass[i].linesClass[j].lineClass[l].getNumberOfLinePoints() ; m++){	//������ �̷�� �� ���� ����

								tempX =  pTree->fm.getDataDouble(parentName,childName,k,12);
								tempY =  pTree->fm.getDataDouble(parentName,childName,k,13);
								tempZ =  pTree->fm.getDataDouble(parentName,childName,k,14);
								naktaDraw.informationClass[i].linesClass[j].lineClass[l].setPointXYZ(m,tempX,tempY,tempZ);// x,y,z �� �������� �޾ƿ;���
							}
							
						}
							tempID   =  pTree->fm.getDataDouble(parentName,childName,k,0); //id��
							tempSize =  pTree->fm.getDataDouble(parentName,childName,k,1); //size
							tempColorRed = pTree->fm.getDataDouble(parentName,childName,k,2);		//red
							tempColorBlue = pTree->fm.getDataDouble(parentName,childName,k,3);		//blue
							tempColorGreen = pTree->fm.getDataDouble(parentName,childName,k,4);		//green

							naktaDraw.informationClass[i].linesClass[j].setLineID(tempLineIndex,tempID);			//ID ����
							naktaDraw.informationClass[i].linesClass[j].setLineColor(tempLineIndex,tempColorRed,tempColorBlue,tempColorGreen);	//[����]���� ����
							naktaDraw.informationClass[i].linesClass[j].setLineSize(tempLineIndex,tempSize);		//[����]���� ����
							tempLineIndex++;
						break;
					case 3: 
							//polygon ���� �־���
						for(int l = 0; l < naktaDraw.informationClass[i].polygonsClass[j].getNumberOfPolygon(); l++){		//���� ������ ������ ����..
							naktaDraw.informationClass[i].polygonsClass[j].polygonClass[l].setNumberOfPolygonPoints(pTree->fm.getDataDouble(parentName,childName,k,12));	//��  �������� ��� ������ �̷�� ����
							naktaDraw.informationClass[i].polygonsClass[j].polygonClass[l].setPolygonVectorSize(pTree->fm.getDataDouble(parentName,childName,k,12));			//���� ���� ����
							for(int m = 0; m < naktaDraw.informationClass[i].polygonsClass[j].polygonClass[l].getNumberOfPolygonPoints() ; m++){	//������ �̷�� �� ���� ����
								tempX =  pTree->fm.getDataDouble(parentName,childName,k,12);
								tempY =  pTree->fm.getDataDouble(parentName,childName,k,13);
								tempZ =  pTree->fm.getDataDouble(parentName,childName,k,14);
								naktaDraw.informationClass[i].polygonsClass[j].polygonClass[l].setPolygonPointXYZ(m,tempX,tempY,tempZ);// x,y,z �� �������� �޾ƿ;���
							}
							
						}
							tempID   =  pTree->fm.getDataDouble(parentName,childName,k,0); //id��
							//tempSize =  pTree->fm.getDataDouble(parentName,childName,k,2); //size
							tempColorRed = pTree->fm.getDataDouble(parentName,childName,k,2);		//red
							tempColorBlue = pTree->fm.getDataDouble(parentName,childName,k,3);		//blue
							tempColorGreen = pTree->fm.getDataDouble(parentName,childName,k,4);		//green

							naktaDraw.informationClass[i].polygonsClass[j].setPolygonID(tempPolygonIndex,tempID);	//[����]ID ����
							naktaDraw.informationClass[i].polygonsClass[j].setPolygonColor(tempPolygonIndex,tempColorRed,tempColorBlue,tempColorGreen);	//[����]���� ����
							tempPolygonIndex++;
						break;
					default: break;	//�ͼ��� �������� ������		
				}
			}
			tempPointIndex   = 0;
			tempLineIndex    = 0;
			tempPolygonIndex = 0;
			
		}
	}
	DrawGLScene();

}


void CJoshuaGIS3View::OnPrecipitationmodeX1()
{
	precipitationSpeed = 1.0;
	isPrecipitation = TRUE;
	drawPrecipitation(precipitationSpeed);
	
}


void CJoshuaGIS3View::OnPrecipitationmodeX2()
{
	precipitationSpeed = 1.5;
	isPrecipitation = TRUE;	
	drawPrecipitation(precipitationSpeed);
}


void CJoshuaGIS3View::OnPrecipitationmodeX3()
{
	precipitationSpeed = 2.0;
	isPrecipitation = TRUE;
	drawPrecipitation(precipitationSpeed);
		
}


void CJoshuaGIS3View::OnPrecipitationmodeX4()
{
	precipitationSpeed = 2.5;
	isPrecipitation = TRUE;
	drawPrecipitation(precipitationSpeed);
	
}


void CJoshuaGIS3View::OnPrecipitationmodeX5()
{
	precipitationSpeed = 3.0;
	isPrecipitation = TRUE;
	drawPrecipitation(precipitationSpeed);
	
}


void CJoshuaGIS3View::drawPrecipitation(float increaseRate)
{
	for(float i = 41.f/ 2500.f ; i <  50.43/2500.f ; i +=increaseRate/40000.f)
	{
		cubeZ = i;
		DrawGLScene();
	}
}


void CJoshuaGIS3View::drawCubePrecipitation(void)
{
	float v[8][3];
	float minz = 41/Z_DIVIDER, maxz = 62/Z_DIVIDER;
	float minx = 25.6, maxx = 25.7961;
	float maxy = 85.1967, miny = 84.87;
	
	v[0][0] = v[3][0] = v[4][0] = v[5][0] = minx;
	v[1][0] = v[2][0] = v[6][0] = v[7][0] = maxx;
	v[0][1] = v[1][1] = v[2][1] = v[3][1] = maxy;
	v[4][1] = v[5][1] = v[6][1] = v[7][1] = miny;
	v[0][2] = v[1][2] = v[7][2] = v[4][2] = minz;
	v[2][2] = v[3][2] = v[5][2] = v[6][2] = cubeZ;

	 
	glColor3f( 0.0, 0.0, 1.0 ); 
	//Multi-colored side - FRONT
	glBegin(GL_POLYGON);     
	glVertex3fv(v[0]);
	glVertex3fv(v[3]);
	glVertex3fv(v[2]);
	glVertex3fv(v[1]);
	glEnd();
 
	// White side - BACK
	//glBegin(GL_TRIANGLES);
	glBegin(GL_POLYGON);
	glVertex3fv(v[7]);
	glVertex3fv(v[6]);
	glVertex3fv(v[5]);
	glVertex3fv(v[4]);
	glEnd();
 
	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glVertex3fv(v[1]);
	glVertex3fv(v[2]);
	glVertex3fv(v[6]);
	glVertex3fv(v[7]);
	glEnd();
 
	// Green side - LEFT
	glBegin(GL_POLYGON);
	glVertex3fv(v[4]);
	glVertex3fv(v[5]);
	glVertex3fv(v[3]);
	glVertex3fv(v[0]);
	glEnd();
 
	// Blue side - TOP
	glBegin(GL_POLYGON);
	glVertex3fv(v[3]);
	glVertex3fv(v[5]);
	glVertex3fv(v[6]);
	glVertex3fv(v[2]);
	glEnd();
 
	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]);
	glVertex3fv(v[4]);
	glVertex3fv(v[7]);
	glVertex3fv(v[1]);
	glEnd();

}


void CJoshuaGIS3View::OnPrecipitationmodePrecipitationmodeoff()
{
	isPrecipitation = FALSE;
	cubeZ = 41/Z_DIVIDER;

	DrawGLScene();
}
