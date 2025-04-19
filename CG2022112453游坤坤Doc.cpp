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
END_MESSAGE_MAP()


// CCG2022112453������Doc ����/����

CCG2022112453������Doc::CCG2022112453������Doc() noexcept
{
	// TODO: �ڴ����һ���Թ������
	mScene = std::make_shared<CGScene>();
	mScene->SetMainCamera(std::make_shared<CGCamera>());
	auto e = std::make_shared<CGGeode>();
	auto line = std::make_shared<CGLineSegment>(glm::dvec3(100, 100, 0), glm::dvec3(400, 300, 0));
	e->AddChild(line);
	auto g = std::make_shared<CGTransform>();
	g->AddChild(e);
	mScene->SetSceneData(g);
}

CCG2022112453������Doc::~CCG2022112453������Doc()
{
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
	if (mScene == nullptr)
		return false;
	CGGroup* g = mScene->GetSceneData()->asGroup();
	if (g) {
		g->AddChild(r);
		return true;
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

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
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
		CMFCFilterChunkValueImpl *pChunk = nullptr;
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


// CCG2022112453������Doc ����

void CCG2022112453������Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦�������� 
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		EventType::Draw2DLineSeg);
}

void CCG2022112453������Doc::OnDraw2dLineseg()
{
	// TODO: �ڴ��������������� 
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
		UIEventHandler::SetCommand(new CGDraw2DLineStrip(view->glfwWindow(), view->DDA_Line)); //��������ֱ�߶ε��������
	}
}

void CCG2022112453������Doc::OnUpdateDraw2dLineStrip(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦�������� 
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		EventType::Draw2DLineStrip);
}


