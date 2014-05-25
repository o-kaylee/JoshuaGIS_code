
// JoshuaGIS3View.cpp : CJoshuaGIS3View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CJoshuaGIS3View 생성/소멸

CJoshuaGIS3View::CJoshuaGIS3View()
	: cubeZ(0)
{
	m_ptMouse = CPoint(0, 0);

	naktaVertex.init("NaktaVertex.obj");			//NaktaVetex.obj 파일로 부터 낙타섬 관련 정점정보를 읽어드림. Vertex 클래스 선언
	NaktaFace.init(9900);								//Face 클래스 선언
	naktaTexture.init(true);

	//카메라 초기셋팅
	eye1.setPoint3(25.698f, 85.0335f,0.24f);
	look.setPoint3(25.698f, 85.0335f, 0.24-0.00001f);
	up.set(0, 1, 0); 

	//마우스
	MouseModeFlag=0;
	MouseDrawFlag=0;

	//라인, 폴리곤 그려줄 시 필요함.
	isLineFirstStart=true;
	isPolygonFirstStart  = true;

	vertexPointer = &naktaVertex;							//vertex 관련 정보 클래스를 가리키는 포인터 변수
	facePointer = &NaktaFace;								//face 관련 정보 클래스를 가리키는 포인터 변수.
	numOfFace=0;

	g_renderModeFlag=1;	//일반, 텍스쳐, wire-frame mode 를 변경할시 참조되는 값.

	camX= 25.698f, camY= 85.0335f,camZ = 0.5f;
	xAngle=0, yAngle=0, zAngle=0;		//초기위치.. z가 90 인 이유는 |  이렇게 보이는 낙타섬을 ㅡ 이렇게 보기위함.
	angleSpeed = 0.04;						//돌리는 속도
	cameraSpeed  = 0.00004;
	lx=0.0f,ly=0.0f,lz=-1.0f;
	cameraNear = 0.005;
	cameraFar = 1000;

	



	//opengl 하기전에 계산해야 하는 것들 (정점 정보 불러오기, face 구성, 법선벡터 구성)
	CalculateFace calculateFace(true);
	CalculateVertex calculateVertex(true);
		//면관련
	calculateFace.vertexToFace(facePointer);//정점으로 부터 면정보 생성
	calculateFace.setFaceNormalVector(facePointer,vertexPointer);	//면의 법선벡터를 구한다

	numOfFace = facePointer->getNumOfFace();	//렌더링할때 면 갯수를 알아야 for 룹에서 i 는 0부터 어디까지 돌아야 하는지 알 수 있음.

		//vertex관련
	naktaVertex.setVertexNormalVectorSize(naktaVertex.getNumOfVertex());	//정점의 법선정보를 기록할 공간 할당 및 초기화
	calculateVertex.setVertexNormalVector(facePointer,vertexPointer);
	
	
	//물 차오르기
	precipitationSpeed = 0;
	isPrecipitation = false;
}

CJoshuaGIS3View::~CJoshuaGIS3View()
{
}

BOOL CJoshuaGIS3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CJoshuaGIS3View 그리기

void CJoshuaGIS3View::OnDraw(CDC* /*pDC*/)
{
	CJoshuaGIS3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawGLScene();
	
}


// CJoshuaGIS3View 진단

#ifdef _DEBUG
void CJoshuaGIS3View::AssertValid() const
{
	CView::AssertValid();
}

void CJoshuaGIS3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJoshuaGIS3Doc* CJoshuaGIS3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJoshuaGIS3Doc)));
	return (CJoshuaGIS3Doc*)m_pDocument;
}
#endif //_DEBUG


// CJoshuaGIS3View 메시지 처리기
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
	if(g_renderModeFlag == 0)	//일반 모드
		glCallList(displayBox2);
	else if(g_renderModeFlag == 1)	//텍스쳐
		glCallList(displayBox3);
	else if(g_renderModeFlag == 2)	//wire-frame {
		glCallList(displayBox1);
		
	glPopMatrix(); 
	glPopMatrix();


	if(isPrecipitation = true){
		//올라오는 함수 그려줌
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hglRC);
}


void CJoshuaGIS3View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ReSizeGLScene(cx, cy);
}

void CJoshuaGIS3View::BuildLists()
{
	int point1, point2, point3; //그릴때 사용됨

	displayBox1=glGenLists(2);				// 2개의 다른 리스트를 만듬

	///////////////////////////////////////////////////////////////////////////////////////////////리스트박스 1 시작
	glNewList(displayBox1,GL_COMPILE);		// 리스트박스 첫번째 것은 컴파일시 미리 실행됨
			
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);

	//리스트박스1 의 그려줄때 필요한 정보들
	glBegin(GL_TRIANGLES);{
	for(int i = 0; i < numOfFace; i++){
		//노멀벡터
		glNormal3f(facePointer->getNormalVectorX(i),facePointer->getNormalVectorY(i),facePointer->getNormalVectorZ(i));
		//정점
		glVertex3f(naktaVertex.getVertexX(facePointer->getPoint1(i)),naktaVertex.getVertexY(facePointer->getPoint1(i)),naktaVertex.getVertexZ(facePointer->getPoint1(i))/Z_DIVIDER);
		glVertex3f(naktaVertex.getVertexX(facePointer->getPoint2(i)),naktaVertex.getVertexY(facePointer->getPoint2(i)),naktaVertex.getVertexZ(facePointer->getPoint2(i))/Z_DIVIDER);
		glVertex3f(naktaVertex.getVertexX(facePointer->getPoint3(i)),naktaVertex.getVertexY(facePointer->getPoint3(i)),naktaVertex.getVertexZ(facePointer->getPoint3(i))/Z_DIVIDER);
	}

	}glEnd();
	glEndList();
	////////////////////////////////////////////////////////////////////////////////////////////////리스트박스 1 끝

	displayBox2 = displayBox1+1;	//두번째 리스트 박스 선언
	///////////////////////////////////////////////////////////////////////////////////////////////리스트박스 2 시작
	glNewList(displayBox2,GL_COMPILE);							// Start With The Box List
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);
		//리스트박스2 의 그려줄때 필요한 정보들
		glBegin(GL_TRIANGLES);{
		glColor3f(0.9, 0.9f, 0.9f);

		for(int i = 0; i < numOfFace; i++){
			point1 = facePointer->getPoint1(i);		//면 하나의 첫번째 점 vertex의 index
			point2 = facePointer->getPoint2(i);		//면 하나의 두번째 점 vertex의 index
			point3 = facePointer->getPoint3(i);		//면 하나의 세번째 점 vertex의 index
			
			//3점의 노멀벡터와 정점 셋팅
			glNormal3f(naktaVertex.getVertexNormalVectorX(point1),naktaVertex.getVertexNormalVectorY(point1),naktaVertex.getVertexNormalVectorZ(point1));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint1(i)),naktaVertex.getVertexY(facePointer->getPoint1(i)),naktaVertex.getVertexZ(facePointer->getPoint1(i))/Z_DIVIDER);
			
			glNormal3f(naktaVertex.getVertexNormalVectorX(point2),naktaVertex.getVertexNormalVectorY(point2),naktaVertex.getVertexNormalVectorZ(point2));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint2(i)),naktaVertex.getVertexY(facePointer->getPoint2(i)),naktaVertex.getVertexZ(facePointer->getPoint2(i))/Z_DIVIDER);
			
			glNormal3f(naktaVertex.getVertexNormalVectorX(point3),naktaVertex.getVertexNormalVectorY(point3),naktaVertex.getVertexNormalVectorZ(point3));
			glVertex3f(naktaVertex.getVertexX(facePointer->getPoint3(i)),naktaVertex.getVertexY(facePointer->getPoint3(i)),naktaVertex.getVertexZ(facePointer->getPoint3(i))/Z_DIVIDER);
		}
	}glEnd();
	glEndList();
	///////////////////////////////////////////////////////////////////////////////////////////////리스트박스 2 끝

	displayBox3 = displayBox1+2;	//세번째 리스트 박스 선언
	///////////////////////////////////////////////////////////////////////////////////////////////리스트박스 3 시작
	glNewList(displayBox3,GL_COMPILE);							// Start With The Box List
	glPolygonMode(GL_FRONT,GL_FILL);
	naktaTexture.setInformation(IMAGE_WIDTH_HEIGHT, IMAGE_BOUNDARY_WIDTH, IMAGE_BOUNDARY_HEIGHT);	//불러올 이미지 정보와 그 중 내가 원하는 너비 높이를 셋팅
	naktaTexture.initTexture("naktaImage.bmp", textures);
	naktaTexture.setRow(50);
	naktaTexture.setColumn(100);
	naktaTexture.setXYrate();
	glPolygonMode(GL_BACK,GL_FILL);
		//리스트박스3 의 그려줄때 필요한 정보들
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.9f, 0.9f, 0.9f);
	glBindTexture(GL_TEXTURE_2D,textures[0]);

		
		
		glBegin(GL_TRIANGLES);{
		
		for(int i = 0; i < numOfFace; i++){
			point1 = facePointer->getPoint1(i);		//면 하나의 첫번째 점 vertex의 index
			point2 = facePointer->getPoint2(i);		//면 하나의 두번째 점 vertex의 index
			point3 = facePointer->getPoint3(i);		//면 하나의 세번째 점 vertex의 index
			
			//텍스쳐 좌표, 3점의 노멀벡터와 정점 셋팅
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
	///////////////////////////////////////////////////////////////////////////////////////////////리스트박스 3 끝
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
			case 69: cam.set(eye1, look, up); // 초기상태로 바꿈 e
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
	// return CView::OnEraseBkgnd(pDC);
}


void CJoshuaGIS3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
		CMenu* Dmenu = menu.GetSubMenu(0); //맨 앞에 메뉴를 가져옴

		Dmenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON , p.x, p.y, this); 
	}

	CView::OnRButtonUp(nFlags, point);
}

// 메뉴 처리기 함수들의 정의
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

// Line Drawing Mode 메뉴 처리기의 정의
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


	// 0인경우 -> Titile: 클릭된 항목이 없습니다. 로 보내주기. 다른값 none 아니면 0 으로
	if(index[3] == 0){
		pForm->initialize();

		pForm->m_controlID.SetWindowTextW(_T("클릭된 object가 없습니다."));
		pForm->m_controlName.SetWindowTextW(_T("None"));
		
		pForm->Invalidate();
	}

	//0이 아닌경우 -> 엑셀에서 찾아서 데이터 값 가져오면 됨!!
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


	//클릭 되었을 시, 해당 도형의 색갈을 바꿔주면 될듯..
	//바꾸는 과정은, 클릭된 놈 컬러값 읽어들여서 해당 vector 어레이 컬러값 바꿔주고, clickedID color, clickedID 변수를 만들어서 넣는다.

	//클릭 되었을 떄 해당 아이디를 찾는다..
	

	//변수에다가 저장

//	int a = 3;
//	char* b = "으앙";


	//저장된 변수를 속성창에 넘겨준다.

	//속성창에 넘겨주는 함수 


	//그리고 정보를 뽑아내고,


	//넘긴다.

}

void CJoshuaGIS3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int* index;
	int parentIndex;
	int childIndex;;
	CString floatToStringPointX,floatToStringPointY,floatToStringPointZ ;
	int tempID;
	naktaCoordinate.leftClick(point.x, point.y); // 클릭한 지점의 월드 좌표 저장
	GLdouble* clickedXYZ;
	clickedXYZ = naktaCoordinate.getLeftClickedCoordinate();

	/* 예제다.
	//text용.
	index = pTree->getIndex();
	if(index[0] == index[1]);

	//text용 2
	test = pTree->getChildSheetName(index[0],index[1]);
	test = pTree->getParentName(index[0]);
	*/
		
	index = pTree->getIndex();

	if(index == NULL)
		return;
	

	parentIndex = index[0]; //부모인덱스
	childIndex = index[1]; //자식인덱스
	
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
			//ok 했을 경우
				//엑셀로 아까 받아왔던 데이터 넘겨준다.
				ExcelFile *eFile = pTree->fm.getFile(parentIndex);
				Sheet *_sheet = eFile->getSheet(childIndex);
				int lastLine = _sheet->getNumOfItem(); //끝줄 정보 받아와서, 끝줄 다음부터 넣어줌..
				//유저가 입력한 정보를 데이터에 string 으로 넣음.
				char* buffer = new char[ID.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,ID,-1,buffer,ID.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 0, buffer); //0번 컬럼은 ID

				buffer = new char[addObjectDlg->size.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->size,-1,buffer,addObjectDlg->size.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 1, buffer); //1번 Size

				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 2, addObjectDlg->colorCode[0]); //RBG-R 값

				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 3, addObjectDlg->colorCode[1]); //RBG-G 값

				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 4, addObjectDlg->colorCode[2]); //RBG-B 값

				buffer = new char[addObjectDlg->m_valueName.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueName,-1,buffer,addObjectDlg->m_valueName.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 5, buffer); //제목

				buffer = new char[addObjectDlg->m_valueCha.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueCha,-1,buffer,addObjectDlg->m_valueCha.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 6, buffer); //특성

				buffer = new char[addObjectDlg->m_valueDesc.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueDesc,-1,buffer,addObjectDlg->m_valueDesc.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 7, buffer); //설명

				buffer = new char[addObjectDlg->m_valueTemp1.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueTemp1,-1,buffer,addObjectDlg->m_valueTemp1.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 8, buffer); //temp1

				buffer = new char[addObjectDlg->m_valueTemp2.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueTemp2,-1,buffer,addObjectDlg->m_valueTemp2.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 9, buffer); //temp2

				buffer = new char[addObjectDlg->m_valueTemp3.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,addObjectDlg->m_valueTemp3,-1,buffer,addObjectDlg->m_valueTemp3.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 10, buffer); //temp3

				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 11,1); //점갯수

				buffer = new char[floatToStringPointX.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,floatToStringPointX,-1,buffer,floatToStringPointX.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 12, buffer); //x좌표

				buffer = new char[floatToStringPointY.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,floatToStringPointY,-1,buffer,floatToStringPointY.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 13, buffer); //y좌표

				buffer = new char[floatToStringPointZ.GetLength()+1];
				WideCharToMultiByte(CP_ACP,0,floatToStringPointZ,-1,buffer,floatToStringPointZ.GetLength()+1,NULL,NULL);
				pTree->fm.setData(pTree->getParentName(parentIndex),pTree->getChildSheetName(parentIndex,childIndex),lastLine+1, 14, buffer); //z좌표
				
				//변경된 내용을 opengl 에 알려줌(컬러, 사이즈)
					//컬러값 가지고 온다
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
			// 여기에 Cancel 눌렀을 때 실행할 내용들				
			//지워주면 됨 ㅋ...
				naktaDraw.informationClass[parentIndex].pointClass[childIndex].deleteRecentPoint();
			// 여기에 OK 눌렀을 때 실행할 내용들

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

			// 오류
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



	
	//[보충]  엑셀이나 시트 추가시 부모갯수, 해당 부모 자식의갯수도 늘려줘야.(벡터ㅡ 사이즈 크기)
	//1.   부모의 갯수를 가져온다.
	numberOfParentNode = pTree->fm.getNumOfFiles(); 
	
		//1-1. 부모의 노드 갯수 설정
	naktaDraw.setNumberOfParent(numberOfParentNode);
	
	
	//1-2. 부모의 벡터 크기 설정
	naktaDraw.setInformationSize(numberOfParentNode);	


		//2. for 문 돌려서 (부모의 노드 갯수 만큼)

		//2-1. 해당 부모의 자식 노드 사이즈 설정
		//2-2. 해당 부모의 자식 벡터 크기 설정
	
	for(int i = 0 ; i < numberOfParentNode; i++){
		
		ExcelFile* eFile = pTree->fm.getFile(i);
		numberOfChildNode = eFile->getNumOfSheets(); // 해당 부모의 자식노드 크기 받아옴

		naktaDraw.informationClass[i].setInformationSize(numberOfChildNode);	//자식노드 사이즈 설정
		naktaDraw.informationClass[i].setNumberOfChild(numberOfChildNode);	//자식노드 벡터 크기 설정
		
		for(int j = 0 ; j < numberOfChildNode ; j++) 
			naktaDraw.informationClass[i].setIsChildClicked(j,true);	//i번쨰 부모의 j번째 자식노드는 클릭 안되어 있음으로 default
	}



	for(int i = 0; i < numberOfParentNode ; i ++){
		ExcelFile* eFile = pTree->fm.getFile(i);

		for(int j= 0; j < eFile->getNumOfSheets(); j++){//해당 i번째 부모의 자식개수
			
			parentName = pTree->getParentName(i);
			childName = pTree->getChildSheetName(i,j);

			ExcelFile *eFile = pTree->fm.getFile(i);
			Sheet *_sheet = eFile->getSheet(j);
			_sheet->getNumOfItem();


			for(int k = 1 ; k <= _sheet->getNumOfItem(); k++){				//[수정]
				tempSwitchVariable = pTree->fm.getDataInt(parentName,childName,k,0);

				switch(tempSwitchVariable%100){
					case 1: numberOfPoint++;   break;
					case 2: numberOfLine++;    break;
					case 3: numberOfPolygon++; break;
					default: break;	//익셉션 넣으려면 넣을것		
				}
			}
			int tempTest;
			tempTest =numberOfPoint;
			//점, 선, 면 갯수 설정
			naktaDraw.informationClass[i].pointClass[j].setNumberOfPoint(numberOfPoint);
			
			tempTest = naktaDraw.informationClass[i].pointClass[j].getNumberOfPoint();
			naktaDraw.informationClass[i].linesClass[j].setNumberOfLine(numberOfLine);			//라인 몇개 있는지 설정
			naktaDraw.informationClass[i].polygonsClass[j].setNumberOfPolygon(numberOfPolygon);	//폴리곤 몇개 있는지 설정

			naktaDraw.informationClass[i].pointClass[j].setLastIndex(numberOfPoint-1);
			naktaDraw.informationClass[i].linesClass[j].setLastIndex(numberOfLine-1);			//라인 몇개 있는지 설정
			naktaDraw.informationClass[i].polygonsClass[j].setLastIndex(numberOfPolygon-1);	//폴리곤 몇개 있는지 설정

			//점, 선, 면 벡터 크기 설정
			naktaDraw.informationClass[i].pointClass[j].setVectorSize(numberOfPoint);
			naktaDraw.informationClass[i].linesClass[j].setVectorSize(numberOfLine);
			naktaDraw.informationClass[i].polygonsClass[j].setVectorSize(numberOfPolygon);

			//



			//
		

			//데이터를 exel  넣어줌
			for(int k = 1 ; k <= _sheet->getNumOfItem() /*해당 자식의 라인이 끝날때 까지*/; k++){
				tempSwitchVariable = pTree->fm.getDataInt(parentName,childName,k,0);//ID % 100 으로점,선,면 속성 구분하여 값 넣어줌
				
				switch(tempSwitchVariable%100){
					case 1:	//point 정보 넣어줌
						
						
						tempX = pTree->fm.getDataDouble(parentName,childName,k,12);//[잉여]행,렬 시작 index 질문. 지금은 1부터 시작한다고 생각
						tempY =  pTree->fm.getDataDouble(parentName,childName,k,13);//[잉여]행,렬 시작 index 질문
						tempZ = pTree->fm.getDataDouble(parentName,childName,k,14);//[잉여]행,렬 시작 index 질문
						tempSize = pTree->fm.getDataDouble(parentName,childName,k,1);
						tempID =  pTree->fm.getDataDouble(parentName,childName,k,0); //id값
						tempColorRed = pTree->fm.getDataDouble(parentName,childName,k,2);		//red
						tempColorBlue = pTree->fm.getDataDouble(parentName,childName,k,3);		//blue
						tempColorGreen = pTree->fm.getDataDouble(parentName,childName,k,4);		//green


						//i번째 부모, j번째 자식.
					//get(
						//아이디 생성
							//tempID = naktaDraw.IdGenerator(1,1,1, 1);//[보충]
							naktaDraw.informationClass[i].pointClass[j].setPointXYZ(tempPointIndex,tempX,tempY,tempZ);	//점좌표 : x,y,z
							naktaDraw.informationClass[i].pointClass[j].setPointSize(tempPointIndex,tempSize);	//점 크기
							naktaDraw.informationClass[i].pointClass[j].setPointID(tempPointIndex,tempID);		//아이디값 
							naktaDraw.informationClass[i].pointClass[j].setPointColor(tempPointIndex,tempColorRed,tempColorBlue,tempColorGreen);	//색상	
							tempPointIndex++;
						break;
					case 2:
							//line 정보 넣어줌
						for(int l = 0; l < naktaDraw.informationClass[i].linesClass[j].getNumberOfLine(); l++){		//라인 갯수가 끝날때 까지..
							naktaDraw.informationClass[i].linesClass[j].lineClass[l].setNumberOfLinePoints( pTree->fm.getDataDouble(parentName,childName,k,12));//이 라인은 몇개의 점으로 이루어 졌나
							naktaDraw.informationClass[i].linesClass[j].lineClass[l].setVectorSize(pTree->fm.getDataDouble(parentName,childName,k,12));	//벡터 공간 설정
							for(int m = 0; m < naktaDraw.informationClass[i].linesClass[j].lineClass[l].getNumberOfLinePoints() ; m++){	//라인을 이루는 점 정보 넣음

								tempX =  pTree->fm.getDataDouble(parentName,childName,k,12);
								tempY =  pTree->fm.getDataDouble(parentName,childName,k,13);
								tempZ =  pTree->fm.getDataDouble(parentName,childName,k,14);
								naktaDraw.informationClass[i].linesClass[j].lineClass[l].setPointXYZ(m,tempX,tempY,tempZ);// x,y,z 값 엑셀에서 받아와야함
							}
							
						}
							tempID   =  pTree->fm.getDataDouble(parentName,childName,k,0); //id값
							tempSize =  pTree->fm.getDataDouble(parentName,childName,k,1); //size
							tempColorRed = pTree->fm.getDataDouble(parentName,childName,k,2);		//red
							tempColorBlue = pTree->fm.getDataDouble(parentName,childName,k,3);		//blue
							tempColorGreen = pTree->fm.getDataDouble(parentName,childName,k,4);		//green

							naktaDraw.informationClass[i].linesClass[j].setLineID(tempLineIndex,tempID);			//ID 설정
							naktaDraw.informationClass[i].linesClass[j].setLineColor(tempLineIndex,tempColorRed,tempColorBlue,tempColorGreen);	//[보충]색상 설정
							naktaDraw.informationClass[i].linesClass[j].setLineSize(tempLineIndex,tempSize);		//[보충]굵기 설정
							tempLineIndex++;
						break;
					case 3: 
							//polygon 정보 넣어줌
						for(int l = 0; l < naktaDraw.informationClass[i].polygonsClass[j].getNumberOfPolygon(); l++){		//라인 갯수가 끝날때 까지..
							naktaDraw.informationClass[i].polygonsClass[j].polygonClass[l].setNumberOfPolygonPoints(pTree->fm.getDataDouble(parentName,childName,k,12));	//이  폴리곤은 몇개의 점으로 이루어 졌나
							naktaDraw.informationClass[i].polygonsClass[j].polygonClass[l].setPolygonVectorSize(pTree->fm.getDataDouble(parentName,childName,k,12));			//벡터 공간 설정
							for(int m = 0; m < naktaDraw.informationClass[i].polygonsClass[j].polygonClass[l].getNumberOfPolygonPoints() ; m++){	//라인을 이루는 점 정보 넣음
								tempX =  pTree->fm.getDataDouble(parentName,childName,k,12);
								tempY =  pTree->fm.getDataDouble(parentName,childName,k,13);
								tempZ =  pTree->fm.getDataDouble(parentName,childName,k,14);
								naktaDraw.informationClass[i].polygonsClass[j].polygonClass[l].setPolygonPointXYZ(m,tempX,tempY,tempZ);// x,y,z 값 엑셀에서 받아와야함
							}
							
						}
							tempID   =  pTree->fm.getDataDouble(parentName,childName,k,0); //id값
							//tempSize =  pTree->fm.getDataDouble(parentName,childName,k,2); //size
							tempColorRed = pTree->fm.getDataDouble(parentName,childName,k,2);		//red
							tempColorBlue = pTree->fm.getDataDouble(parentName,childName,k,3);		//blue
							tempColorGreen = pTree->fm.getDataDouble(parentName,childName,k,4);		//green

							naktaDraw.informationClass[i].polygonsClass[j].setPolygonID(tempPolygonIndex,tempID);	//[보충]ID 설정
							naktaDraw.informationClass[i].polygonsClass[j].setPolygonColor(tempPolygonIndex,tempColorRed,tempColorBlue,tempColorGreen);	//[보충]색상 설정
							tempPolygonIndex++;
						break;
					default: break;	//익셉션 넣으려면 넣을것		
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
