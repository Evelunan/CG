// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û�����
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο�����
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// CG2022112453������View.cpp: CCG2022112453������View ���ʵ��
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG2022112453������.h"
#endif

#include "CG2022112453������Doc.h"
#include "CG2022112453������View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG2022112453������View

IMPLEMENT_DYNCREATE(CCG2022112453������View, CView)

BEGIN_MESSAGE_MAP(CCG2022112453������View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CCG2022112453������View ����/����

bool CCG2022112453������View::InitGLFW()
{
	if (!glfwInit()) {
		AfxMessageBox(_T("GLFW��ʼ��ʧ��"));
		return false;
	}
	// ����GLFW�����ޱ߿�͸�������⸲��MFC�ؼ��� 
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	// ����OpenGL�汾 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //���ʹ��OpenGL����ģʽ 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //���ʹ��OpenGL����ģʽ 

	// �������ص�GLFW���� 
	m_glfwWindow = glfwCreateWindow(100, 100, "", NULL, NULL);
	if (!m_glfwWindow) {
		AfxMessageBox(_T("Failed to glfwCreateWindow"));
		glfwTerminate();
		return false;
	}
	// ��ȡGLFW���ڵ�HWND������ΪMFC��ͼ���Ӵ��� 
	m_hWndGL = glfwGetWin32Window(m_glfwWindow);
	SetWindowLong(m_hWndGL, GWL_STYLE, WS_VISIBLE);
	::SetParent(m_hWndGL, GetSafeHwnd());
	::ShowWindow(m_hWndGL, SW_SHOW);

	// ��ʼ��OpenGL������ 
	glfwMakeContextCurrent(m_glfwWindow);
#if defined(_USE_GLEW) 
		glewInit();
#else 
		//ʹ��GLAD������OpenGL�ĺ�����ַ
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		AfxMessageBox(_T("Failed to initialize GLAD"));
		return false;
	}
#endif 

	// �����ӿ� 
	CRect rect;
	GetClientRect(&rect);
	glViewport(0, 0, rect.Width(), rect.Height());

	m_bGLInitialized = true;

	return true;
}

void CCG2022112453������View::RenderScene()
{
	if (!m_bGLInitialized)
		return;
	//������Ⱦ���� 
	glfwMakeContextCurrent(m_glfwWindow);

	//�˴�����Զ���OpenGL��Ⱦ����... 

	//drawTest1();
	//draWTest2();
	 
	//testLine();

	//testCircle();
	testScanPloygon();
	testFill();
	//������ϣ��������� 
	glfwSwapBuffers(m_glfwWindow);
}

CCG2022112453������View::CCG2022112453������View() noexcept
{
	// TODO: �ڴ˴���ӹ������

}

CCG2022112453������View::~CCG2022112453������View()
{
	if (m_glfwWindow) {
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}
}

BOOL CCG2022112453������View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCG2022112453������View ��ͼ

void CCG2022112453������View::OnDraw(CDC* /*pDC*/)
{
	CCG2022112453������Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	RenderScene();
}

void CCG2022112453������View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG2022112453������View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG2022112453������View ���

#ifdef _DEBUG
void CCG2022112453������View::AssertValid() const
{
	CView::AssertValid();
}

void CCG2022112453������View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG2022112453������Doc* CCG2022112453������View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2022112453������Doc)));
	return (CCG2022112453������Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG2022112453������View ��Ϣ�������

int CCG2022112453������View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	if (!InitGLFW())
		return -1;
	return 0;
}

void CCG2022112453������View::OnDestroy()
{
	if (m_glfwWindow) {
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
		m_glfwWindow = nullptr;
	}
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

BOOL CCG2022112453������View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CCG2022112453������View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_hWndGL) {
		// ����GLFW�Ӵ��ڴ�С����ͼ�ͻ���ƥ�� 
		::SetWindowPos(m_hWndGL, NULL, 0, 0, cx, cy, SWP_NOZORDER);
		glfwMakeContextCurrent(m_glfwWindow);
		glViewport(0, 0, cx, cy);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//����ͼ�������㷨ʵ�鲿�֣��ٶ��۲촰�����ӿ�һ�¡������½�Ϊԭ�㣬���Ͻ�Ϊ(cx,cy)�� 
		//ʹ������ƽ��ͶӰ 
		glOrtho(0, cx,    //x��Χ 
			0, cy,     //y��Χ 
			-10000.0f, 10000.0f);  //z��Χ����ȣ� 

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}
