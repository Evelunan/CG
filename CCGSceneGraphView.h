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

// CCGSceneGraphView.h: CCGSceneGraphView ��Ľӿ�
//


#pragma once

class CCG2022112453������Doc;

class CCGSceneGraphView : public CTreeView
{
protected: // �������л�����
	CCGSceneGraphView();
	DECLARE_DYNCREATE(CCGSceneGraphView)

protected:
	HTREEITEM mSelectedItem = nullptr;


// ����
public:
	CCG2022112453������Doc* GetDocument();

// ����
public:

// ��д
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CCGSceneGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG  // CCGSceneGraphView.cpp �еĵ��԰汾
inline CCG2022112453������Doc* CCGSceneGraphView::GetDocument()
   { return reinterpret_cast<CCG2022112453������Doc*>(m_pDocument); }
#endif

