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

// CG2022112453������View.h: CCG2022112453������View ��Ľӿ�
//

#pragma once

#include "glIncludes.h"
#include "CCGRenderContext.h"
class CCG2022112453������View : public CView, public CCGRenderContext
{
// ���ݳ�Ա
protected:
	GLFWwindow* m_glfwWindow = nullptr;
	HWND m_hWndGL = nullptr;
	bool m_bGLInitialized = false;

// ��Ա����
protected:
	bool InitGLFW(); // ��ʼ��GLFW
	void  RenderScene(); // ��Ⱦ���� 

protected: // �������л�����
	CCG2022112453������View() noexcept;
	DECLARE_DYNCREATE(CCG2022112453������View)

// ����
public:
	CCG2022112453������Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CCG2022112453������View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // CG2022112453������View.cpp �еĵ��԰汾
inline CCG2022112453������Doc* CCG2022112453������View::GetDocument() const
   { return reinterpret_cast<CCG2022112453������Doc*>(m_pDocument); }
#endif

