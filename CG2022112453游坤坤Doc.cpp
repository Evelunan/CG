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

// CG2022112453������Doc.cpp: CCG2022112453������Doc ���ʵ��
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG2022112453������.h"
#endif

#include "CG2022112453������Doc.h"

#include <propkey.h>
#include "CG2022112453������View.h" 
#include "CGScene.h" 
#include "CGCamera.h" 
#include "CGTransform.h" 
#include "CGGeode.h" 
#include "CGLineSegment.h" 
#include "CGRenderContext.h" 
#include "UIEventHandler.h" 
#include "CGDraw2DLineSeg.h" 
#include "CGDraw2DLineStrip.h"
#include "CCGSceneGraphView.h" 
#include "CGModel2DTransform.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CCG2022112453������Doc

IMPLEMENT_DYNCREATE(CCG2022112453������Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2022112453������Doc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINESEG, &CCG2022112453������Doc::OnUpdateDraw2dLineseg)
	ON_COMMAND(ID_DRAW2D_LINESEG, &CCG2022112453������Doc::OnDraw2dLineseg)
	ON_COMMAND(ID_DRAW2D_LINE_STRIP, &CCG2022112453������Doc::OnDraw2dLineStrip)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINE_STRIP, &CCG2022112453������Doc::OnUpdateDraw2dLineStrip)
	ON_COMMAND(ID_TRANSLATE2D_LEFT, &CCG2022112453������Doc::OnTranslate2dLeft)
	ON_COMMAND(ID_TRANSLATE2D_RIGHT, &CCG2022112453������Doc::OnTranslate2dRight)
	ON_COMMAND(ID_TRANSLATE2D_UP, &CCG2022112453������Doc::OnTranslate2dUp)
	ON_COMMAND(ID_TRANSLATE2D_DOWN, &CCG2022112453������Doc::OnTranslate2dDown)
	ON_COMMAND(ID_ROTATE2D_COUNTERCLOCKWISE, &CCG2022112453������Doc::OnRotate2dCounterclockwise)
	ON_COMMAND(ID_ROTATE2D_CLOCKWISE, &CCG2022112453������Doc::OnRotate2dClockwise)
	ON_COMMAND(ID_SCALEX2D_UP, &CCG2022112453������Doc::OnScalex2dUp)
	ON_COMMAND(ID_SCALEX2D_DOWN, &CCG2022112453������Doc::OnScalex2dDown)
	ON_COMMAND(ID_SACLEY2D_UP, &CCG2022112453������Doc::OnSacley2dUp)
	ON_COMMAND(ID_SCALEY2D_DOWN, &CCG2022112453������Doc::OnScaley2dDown)
	ON_COMMAND(ID_SCALE2D_UP, &CCG2022112453������Doc::OnScale2dUp)
	ON_COMMAND(ID_SCALE2D_DOWN, &CCG2022112453������Doc::OnScale2dDown)
	ON_COMMAND(ID_SHEARX2D_POSITIVE, &CCG2022112453������Doc::OnShearx2dPositive)
	ON_COMMAND(ID_SHEARX2D_NEGATIVE, &CCG2022112453������Doc::OnShearx2dNegative)
	ON_COMMAND(ID_SHEARY2D_POSITIVE, &CCG2022112453������Doc::OnSheary2dPositive)
	ON_COMMAND(ID_SHEARY2D_NEGATIVE, &CCG2022112453������Doc::OnSheary2dNegative)
	ON_COMMAND(ID_MIRROR2D_ORIGIN, &CCG2022112453������Doc::OnMirror2dOrigin)
	ON_COMMAND(ID_MIRROR2D_YEQ_POS_X, &CCG2022112453������Doc::OnMirror2dYeqPosX)
	ON_COMMAND(ID_MIRROR2D_YEQ_NEG_X, &CCG2022112453������Doc::OnMirror2dYeqNegX)
	ON_COMMAND(ID_MIRRORX2D, &CCG2022112453������Doc::OnMirrorx2d)
	ON_COMMAND(ID_MIRRORY2D, &CCG2022112453������Doc::OnMirrory2d)
	ON_COMMAND(ID_BUTTON_TRANSFORM2D, &CCG2022112453������Doc::OnButtonTransform2d)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TRANSFORM2D, &CCG2022112453������Doc::OnUpdateButtonTransform2d)
END_MESSAGE_MAP()


// CCG2022112453������Doc ����/����

CCG2022112453������Doc::CCG2022112453������Doc() noexcept
{
	// TODO: �ڴ����һ���Թ������
	mScene = std::make_shared<CGScene>();
	mScene->SetMainCamera(std::make_shared<CGCamera>());
	auto e = std::make_shared<CGGeode>();
	//auto line = std::make_shared<CGLineSegment>(glm::dvec3(100, 100, 0), glm::dvec3(400, 300, 0));
	//e->AddChild(line);
	auto g = std::make_shared<CGTransform>();
	g->AddChild(e);
	mScene->SetSceneData(g);
}

CCG2022112453������Doc::~CCG2022112453������Doc()
{
}

CCGSceneGraphView* CCG2022112453������Doc::GetSceneGraphView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCGSceneGraphView))) {
			CCGSceneGraphView* view = dynamic_cast<CCGSceneGraphView*>(pView);
			return view;
		}
	}
	return nullptr;
}
void CCG2022112453������Doc::InstToSceneTree(CTreeCtrl* pTree)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hInst;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = NULL;// 
	CString str(_T("����"));
	tvinsert.item.pszText = str.GetBuffer();
	str.ReleaseBuffer();
	hInst = pTree->InsertItem(&tvinsert);
	pTree->SetItemData(hInst, DWORD_PTR(mScene.get()));

	InstToSceneTree(pTree, hInst, mScene->GetSceneData());

	pTree->Expand(hInst, TVE_EXPAND);
}
void CCG2022112453������Doc::InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hParent, CGNode* node)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hTree;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = LPARAM(&node);// 
	if (node->asGeode()) {
		CString str(_T("Geode"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		//Ҷ��ʵ���ڵ㲻����ʾģ�ͽڵ� 
	}
	else if (node->asTransform()) {
		CString str(_T("Trans"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asTransform()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asTransform()->GetChild(i));
		}
	}
	else if (node->asGroup()) {
		CString str(_T("Group"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asGroup()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asGroup()->GetChild(i));
		}

	}
}
void CCG2022112453������Doc::OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem)
{
	mSelectedItem = hItem;
	if (!mSelectedItem) {
		mSelectedGroup = nullptr;
		return;
	}
	HTREEITEM hRoot = pTree->GetRootItem();
	if (mSelectedItem == hRoot) {
		mSelectedGroup = nullptr;
	}
	else {
		CGGroup* node = (CGGroup*)(pTree->GetItemData(mSelectedItem));
		if (node && node->asGroup() && !(node->asGeode())) { //������Ҷ�ӽڵ����� 
			mSelectedGroup = dynamic_cast<CGGroup*>(node);
		}
		else {
			mSelectedGroup = nullptr;
		}
	}
}



bool CCG2022112453������Doc::RenderScene(CGRenderContext* pRC)
{
	if (pRC == nullptr)
		return false;
	if (mScene == nullptr)
		return false;
	CGCamera* pCamera = mScene->GetMainCamera();
	if (pCamera == nullptr)
		return false;

	return mScene->Render(pRC, pCamera);
}

bool CCG2022112453������Doc::AddRenderable(std::shared_ptr<CGNode> r)
{
	if (mSelectedGroup) { //��Ҫ��ѡ��һ����ڵ� 
		//ģ�ͼ���ʵ���ڵ����볡�� 
		auto ge = std::make_shared<CGGeode>();
		ge->AddChild(r);
		mSelectedGroup->AddChild(ge);
		CTreeCtrl& tree = GetSceneGraphView()->GetTreeCtrl();
		InstToSceneTree(&tree, mSelectedItem, ge.get());
		return true;
	}
	else {
		AfxMessageBox(_T("����ѡ������ӽڵ����ڵ㣡"));
	}
	return false;
}

BOOL CCG2022112453������Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCG2022112453������Doc ���л�

void CCG2022112453������Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CCG2022112453������Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CCG2022112453������Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CCG2022112453������Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCG2022112453������Doc ���

#ifdef _DEBUG
void CCG2022112453������Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2022112453������Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

CCG2022112453������View* CCG2022112453������Doc::getView()
{
	CCG2022112453������View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453������View))) {
			view = dynamic_cast<CCG2022112453������View*>(pView);
			break;
		}
	}
	return view;
}

void CCG2022112453������Doc::updateHandle(CCmdUI* pCmdUI, EventType type)
{
	// TODO: �ڴ������������û����洦�������� 
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		type);
}

void CCG2022112453������Doc::commandHandler()
{
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
}

void CCG2022112453������Doc::performTransformation(std::function<void(CGRenderable*)> transformFunc)
{
	CCG2022112453������View* view = getView();
	if (view == nullptr)
		return;
	commandHandler();

	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CTreeCtrl* pTree = &(pSceneGraphView->GetTreeCtrl());
	CGGeode* node = (CGGeode*)pTree->GetItemData(mSelectedItem);

	if (!node || node->GetNumRenderables() <= 0)
	{
		AfxMessageBox(_T("����ѡ����Ҫ�ƶ����ӽڵ㣡"));
		return;
	}
	CGRenderable* child = node->GetRenderable(0);
	if (!child)
	{
		AfxMessageBox(_T("����ѡ����Ҫ�ƶ����ӽڵ㣡"));
		return;
	}
	transformFunc(child);
	view->Invalidate(); // ǿ����ͼ�ػ�
}

void CCG2022112453������Doc::translate2d(double x, double y)
{
	performTransformation([x, y](CGRenderable* child) {
		child->Translate(x, y);
		});
}

void CCG2022112453������Doc::rotate2d(double angle, double cx, double cy)
{
	performTransformation([angle, cx, cy](CGRenderable* child) {
		child->Rotate(angle, cx, cy);
		});
}

void CCG2022112453������Doc::scale2d(double sx, double sy)
{
	performTransformation([sx, sy](CGRenderable* child) {
		child->Scale(sx, sy);
		});
}

void CCG2022112453������Doc::shear2d(double shx, double shy)
{
	performTransformation([shx, shy](CGRenderable* child) {
		child->ShearXYAxis(shx, shy);
		});
}


// CCG2022112453������Doc ����

void CCG2022112453������Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	updateHandle(pCmdUI, EventType::Draw2DLineSeg);
}

void CCG2022112453������Doc::OnDraw2dLineseg()
{
	CCG2022112453������View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453������View))) {
			view = dynamic_cast<CCG2022112453������View*>(pView);
			break;
		}
	}

	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineSeg(view->glfwWindow())); //��������ֱ�߶ε��������
	}
}

void CCG2022112453������Doc::OnDraw2dLineStrip()
{
	/*if (!mSelectedGroup) {
		AfxMessageBox(_T("����ѡ������ӽڵ����ڵ㣡"));
		return;
	}*/
	CCG2022112453������View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453������View))) {
			view = dynamic_cast<CCG2022112453������View*>(pView);
			break;
		}
	}

	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view == nullptr)
		return;
	UIEventHandler::SetCommand(new CGDraw2DLineStrip(view->glfwWindow(), view->DDA_Line)); //��������ֱ�߶ε��������
	//UIEventHandler::SetCommand(new CGDraw2DLineStrip(view->glfwWindow(), view->Bresenham_Line)); //��������ֱ�߶ε��������
	//UIEventHandler::SetCommand(new CGDraw2DLineStrip(view->glfwWindow(), view->Midpoint_Line)); //��������ֱ�߶ε��������
}

void CCG2022112453������Doc::OnUpdateDraw2dLineStrip(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦�������� 
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		EventType::Draw2DLineStrip);
}



void CCG2022112453������Doc::OnTranslate2dLeft()
{
	translate2d(-STEP, 0);
}

void CCG2022112453������Doc::OnTranslate2dRight()
{
	translate2d(STEP, 0);
}

void CCG2022112453������Doc::OnTranslate2dUp()
{
	translate2d(0, STEP);
}

void CCG2022112453������Doc::OnTranslate2dDown()
{
	translate2d(0, -STEP);
}

void CCG2022112453������Doc::OnRotate2dCounterclockwise()
{
	rotate2d(ANGLE, 0, 0);
}

void CCG2022112453������Doc::OnRotate2dClockwise()
{
	rotate2d(-ANGLE, 0, 0);
}

void CCG2022112453������Doc::OnScalex2dUp()
{
	scale2d(SCALE_UP, 1);
}

void CCG2022112453������Doc::OnScalex2dDown()
{
	scale2d(SCALE_DOWN, 1);
}

void CCG2022112453������Doc::OnSacley2dUp()
{
	scale2d(1, SCALE_UP);
}

void CCG2022112453������Doc::OnScaley2dDown()
{
	scale2d(1, SCALE_DOWN);
}

void CCG2022112453������Doc::OnScale2dUp()
{
	scale2d(SCALE_UP, SCALE_UP);
}

void CCG2022112453������Doc::OnScale2dDown()
{
	scale2d(SCALE_DOWN, SCALE_DOWN);
}

void CCG2022112453������Doc::OnShearx2dPositive()
{
	shear2d(ANGLE, 0);
}

void CCG2022112453������Doc::OnShearx2dNegative()
{
	shear2d(-ANGLE, 0);
}

void CCG2022112453������Doc::OnSheary2dPositive()
{
	shear2d(0, ANGLE);
}

void CCG2022112453������Doc::OnSheary2dNegative()
{
	shear2d(0, -ANGLE);
}

void CCG2022112453������Doc::OnMirror2dOrigin()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorOrigin();
		});
}

void CCG2022112453������Doc::OnMirror2dYeqPosX()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorYeqPosX();
		});
}

void CCG2022112453������Doc::OnMirror2dYeqNegX()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorYeNegPX();
		});
}

void CCG2022112453������Doc::OnMirrorx2d()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorXAxis();
		});
}

void CCG2022112453������Doc::OnMirrory2d()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorYAxis();
		});
}

void CCG2022112453������Doc::OnButtonTransform2d()
{
	CCG2022112453������View* view = getView();
	if (view == nullptr)
		return;
	commandHandler();

	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CTreeCtrl* pTree = &(pSceneGraphView->GetTreeCtrl());
	CGGeode* node = (CGGeode*)pTree->GetItemData(mSelectedItem);

	if (!node)
	{
		AfxMessageBox(_T("����ѡ����Ҫ�ƶ����ӽڵ㣡"));
		return;
	}
	if (node->GetNumRenderables() <= 0)
		return;
	CGRenderable* child = node->GetRenderable(0);
	if (!child)
	{
		AfxMessageBox(_T("����ѡ����Ҫ�ƶ����ӽڵ㣡"));
		return;
	}
	UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow()));
}

void CCG2022112453������Doc::OnUpdateButtonTransform2d(CCmdUI* pCmdUI)
{
	updateHandle(pCmdUI, EventType::Model2DTransform);
}
