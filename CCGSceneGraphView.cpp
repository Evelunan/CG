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

// CCGSceneGraphView.cpp: CCGSceneGraphView ���ʵ��
//

#include "pch.h"
#include "framework.h"
#include "CG2022112453������.h"

#include "CG2022112453������Doc.h"
#include "CCGSceneGraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGSceneGraphView

IMPLEMENT_DYNCREATE(CCGSceneGraphView, CTreeView)

BEGIN_MESSAGE_MAP(CCGSceneGraphView, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CCGSceneGraphView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CCGSceneGraphView ����/����

CCGSceneGraphView::CCGSceneGraphView()
{
	// TODO: �ڴ˴���ӹ������
}

CCGSceneGraphView::~CCGSceneGraphView()
{
	GetTreeCtrl().DeleteAllItems();
}

BOOL CCGSceneGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CTreeView::PreCreateWindow(cs);
}

void CCGSceneGraphView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: ���� GetTreeCtrl() ֱ�ӷ��� TreeView �����ؼ���
	//  �Ӷ������������ TreeView��
}


// CCGSceneGraphView ���

#ifdef _DEBUG
void CCGSceneGraphView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CCGSceneGraphView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCG2022112453������Doc* CCGSceneGraphView::GetDocument() // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2022112453������Doc)));
	return (CCG2022112453������Doc*)m_pDocument;
}
#endif //_DEBUG


// CCGSceneGraphView ��Ϣ�������

void CCGSceneGraphView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	CCG2022112453������Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	GetTreeCtrl().SetRedraw(TRUE);
}

int CCGSceneGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ������� 
	CTreeCtrl& tree = GetTreeCtrl();
	DWORD dwStyles = tree.GetStyle();
	dwStyles |= TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_HASLINES | TVS_LINESATROOT;// | TVS_CHECKBOXES
		tree.ModifyStyle(0, dwStyles);

	CCG2022112453������Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc) {
		pDoc->InstToSceneTree(&tree);
	}
	return 0;
}

void CCGSceneGraphView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	CCG2022112453������Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	mSelectedItem = GetTreeCtrl().GetSelectedItem();
	pDoc->OnSelectSceneTreeItem(&GetTreeCtrl(), mSelectedItem);
	*pResult = 0;
}
