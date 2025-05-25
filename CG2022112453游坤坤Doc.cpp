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
#include "TessellationHints.h"
#include "CGCube.h"
#include "CGSphere.h"
#include "MyDialog.h"
#include "RobotBodyTransform.h"
#include "CGBasicCameraControl.h"
#include "CGArcballCameraControl.h"
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
	ON_COMMAND(ID_BUTTON_DRAW3D_SPHERE, &CCG2022112453������Doc::OnButtonDraw3dSphere)
	ON_COMMAND(ID_BUTTON_CUBE, &CCG2022112453������Doc::OnButtonCube)
	ON_COMMAND(ID_BUTTON_TIMER, &CCG2022112453������Doc::OnButtonTimer)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TIMER, &CCG2022112453������Doc::OnUpdateButtonTimer)
	ON_COMMAND(ID_BUTTON_ROBOT, &CCG2022112453������Doc::OnButtonRobot)
	ON_COMMAND(ID_BUTTON_CAMERA_CONTROL, &CCG2022112453������Doc::OnButtonCameraControl)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CAMERA_CONTROL, &CCG2022112453������Doc::OnUpdateButtonCameraControl)
	ON_COMMAND(ID_BUTTON_ARCBALL_CONTROL, &CCG2022112453������Doc::OnButtonArcballControl)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ARCBALL_CONTROL, &CCG2022112453������Doc::OnUpdateButtonArcballControl)
END_MESSAGE_MAP()


// CCG2022112453������Doc ����/����

CCG2022112453������Doc::CCG2022112453������Doc() noexcept
{
	mScene = std::make_shared<CGScene>();


	//mScene->SetMainCamera(std::make_shared<CGCamera>());
	//auto e = std::make_shared<CGGeode>();
	////auto line = std::make_shared<CGLineSegment>(glm::dvec3(100, 100, 0), glm::dvec3(400, 300, 0));
	////e->AddChild(line);
	//auto g = std::make_shared<CGTransform>();
	//g->AddChild(e);
	//mScene->SetSceneData(g);
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
		if (node->Name())
			str = node->Name();
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		//Ҷ��ʵ���ڵ㲻����ʾģ�ͽڵ� 
	}
	else if (node->asTransform()) {
		CString str(_T("Trans"));
		if (node->Name())
			str = node->Name();
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
		if (node->Name())
			str = node->Name();
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

bool CCG2022112453������Doc::AddNode(std::shared_ptr<CGNode>  node)
{
	if (node.get() == nullptr)
		return false;
	if (mSelectedGroup) {
		mSelectedGroup->AddChild(node);
	}
	else{
		mScene->GetSceneData()->asGroup()->AddChild(node);
	}
	return true;
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


void CCG2022112453������Doc::draw3D(std::shared_ptr<CGRenderable> render, glm::vec3 center)
{
	using namespace std;
	auto tran1 = make_shared<CGTransform>();
	auto geode = make_shared<CGGeode>();
	auto color = make_shared<CGColor>();
	color->setValue(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	geode->gocRenderStateSet()->setRenderState(color, -1);
	tran1->translate(center.x, center.y, center.z);
	tran1->rotate(45, 1, 1, 1);
	tran1->scale(100, 100, 100);
	geode->AddChild(render);
	tran1->AddChild(geode);
	mScene->GetSceneData()->asGroup()->AddChild(tran1);

	color = make_shared<CGColor>();
	tran1 = make_shared<CGTransform>();
	geode = make_shared<CGGeode>();
	color->setValue((glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))); //��ɫ
	geode->gocRenderStateSet()->setRenderState(color, -1);
	auto mode = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE); //�����߿�ģʽ 
	geode->gocRenderStateSet()->setRenderState(mode, -1);
	tran1->translate(-center.x, center.y, center.z);
	tran1->rotate(45, 1, 1, 1);
	tran1->scale(100, 100, 100);
	geode->AddChild(render);
	tran1->AddChild(geode);
	mScene->GetSceneData()->asGroup()->AddChild(tran1);

	//std::shared_ptr<RobotBodyTransformParam> data = std::make_shared<RobotBodyTransformParam>();
	//std::shared_ptr<RobotBodyRotate> rc = std::make_shared<RobotBodyRotate>();
	//tran1->setUserData(data);
	//tran1->SetUpdateCallback(rc);
}


std::shared_ptr<CGTransform> CCG2022112453������Doc::createTransfrom(CString name)
{
	auto tran = std::make_shared<CGTransform>();
	tran->setName(name);
	return tran;
}

std::shared_ptr<CGTransform> CCG2022112453������Doc::createBoxPart(float len, float width, float height, const glm::vec4& color,const  CString name)
{
	using namespace std;
	auto cube = make_shared<CGCube>(len, width, height);
	auto hints = make_shared<TessellationHints>();

	cube->setTessellationHints(hints);
	cube->setDisplayListEnabled(true);

	auto geode = make_shared<CGGeode>();
	geode->AddChild(cube);
	geode->setName(name);

	// ������ɫ
	auto colorState = make_shared<CGColor>();
	colorState->setValue(color);
	geode->gocRenderStateSet()->setRenderState(colorState, -1);

	 //�����߿�ģʽ
	auto mode = make_shared<CGPolygonMode>(PM_LINE, PM_LINE);
	geode->gocRenderStateSet()->setRenderState(mode, -1);

	auto tran = make_shared<CGTransform>();
	tran->AddChild(geode);
	tran->setName(name);
	return tran;
}
void CCG2022112453������Doc::buildRobot() {
	using namespace std;
	using namespace glm;
	// ���峣����ɫ����
	auto red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // ��ɫ

	auto gray = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); // ��ɫ

	// �������ڵ�
	auto root = createTransfrom("root");

	// create trunk 
	auto trunk = createTransfrom("trunk");

	auto middleTrunk = createBoxPart(80, 30, 50, gray, "middleTrunk");
	auto upperTrunk = createBoxPart(100, 40, 50, gray, "upperTrunk");
	auto lowerTrunk = createBoxPart(60, 20, 50, gray, "lowerTrunk");

	upperTrunk->translate(0, 35, 0); 
	lowerTrunk->translate(0, -25, 0);

	trunk->AddChild(middleTrunk);
	trunk->AddChild(upperTrunk);
	trunk->AddChild(lowerTrunk);
	root->AddChild(trunk);


	//  head
	auto head = createBoxPart(40, 40, 40, red, "head");
	head->translate(0, 75, 0);
	//head->rotate(45, 1, 1, 0); 
	root->AddChild(head);

	// create rightArm
	auto rightArm = createTransfrom("rightArm");

	auto rightUpperArm = createBoxPart(20, 50, 20, gray, "rightUpperArm");
	auto rightLowerArm = createBoxPart(20, 50, 20, gray, "rightLowerArm");
	
	rightLowerArm->translate( 0, -40, 0);
	rightUpperArm->AddChild(rightLowerArm);

	rightArm->AddChild(rightUpperArm);
	rightArm->translate(60, 50, 0);
	rightArm->rotate(145, 0, 0, 1); // ���ֱ���ת45��
	root->AddChild(rightArm);

	// ����������
	auto rightPalm = createBoxPart(25, 10, 20, gray, "rightPalm");
	rightPalm->translate(0, -30, 0); // �����ֱ۳��ȵ���λ��
	rightLowerArm->AddChild(rightPalm);

	// ������ָ�Ļ�������
	float fingerWidth = 4.0f; // ��ָ���
	float fingerHeight = 20.0f; // ��ָ����
	float fingerSpacing = 6.0f; // ��ָ֮��ļ��

	// �������ֵ���ָ
	// Ĵָ
	auto thumb = createBoxPart(fingerWidth, fingerHeight, fingerWidth, gray, "thumb");
	thumb->translate(-8.0f, -15.0f, 10.0f); // ���������ʵ�λ��
	rightPalm->AddChild(thumb);

	// ʳָ
	auto indexFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, gray, "indexFinger");
	indexFinger->translate(-(fingerSpacing * 2), -15.0f, 0.0f);
	rightPalm->AddChild(indexFinger);

	// ��ָ
	auto middleFinger = createBoxPart(fingerWidth, fingerHeight + 5.0f, fingerWidth, gray, "middleFinger"); // ��ָ�Գ�һЩ
	middleFinger->translate(-(fingerSpacing), -15.0f, 0.0f);
	rightPalm->AddChild(middleFinger);

	// ����ָ
	auto ringFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, gray, "ringFinger");
	ringFinger->translate(0.0f, -15.0f, 0.0f);
	rightPalm->AddChild(ringFinger);

	// Сָ
	auto littleFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, gray, "littleFinger");
	littleFinger->translate((fingerSpacing), -15.0f, 0.0f);
	rightPalm->AddChild(littleFinger);


	// create leftArm
	auto leftArm = createTransfrom("leftArm");

	auto leftUpperArm = createBoxPart(20, 50, 20, gray, "leftUpperArm");
	auto leftLowerArm = createBoxPart(20, 50, 20, gray, "leftLowerArm");

	leftLowerArm->translate(0, -40, 0);
	leftUpperArm->AddChild(leftLowerArm);

	leftArm->AddChild(leftUpperArm);
	leftArm->translate(-60, 50, 0);
	leftArm->rotate(-145, 0, 0, 1); // ���ֱ���ת45��
	root->AddChild(leftArm);

	// ����������
	auto leftPalm = createBoxPart(25, 10, 20, gray, "leftPalm");
	leftPalm->translate(0, -30, 0); // �����ֱ۳��ȵ���λ��
	leftLowerArm->AddChild(leftPalm);

	// �������ֵ���ָ
	// Ĵָ
	auto leftThumb = createBoxPart(fingerWidth, fingerHeight, fingerWidth, gray, "leftThumb");
	leftThumb->translate(8.0f, -15.0f, 10.0f); // ���������ʵ�λ��
	leftPalm->AddChild(leftThumb);

	// ʳָ
	auto leftIndexFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, gray, "leftIndexFinger");
	leftIndexFinger->translate((fingerSpacing * 2), -15.0f, 0.0f);
	leftPalm->AddChild(leftIndexFinger);

	// ��ָ
	auto leftMiddleFinger = createBoxPart(fingerWidth, fingerHeight + 5.0f, fingerWidth, gray, "leftMiddleFinger");
	leftMiddleFinger->translate((fingerSpacing), -15.0f, 0.0f);
	leftPalm->AddChild(leftMiddleFinger);

	// ����ָ
	auto leftRingFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, gray, "leftRingFinger");
	leftRingFinger->translate(0.0f, -15.0f, 0.0f);
	leftPalm->AddChild(leftRingFinger);

	// Сָ
	auto leftLittleFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, gray, "leftLittleFinger");
	leftLittleFinger->translate(-(fingerSpacing), -15.0f, 0.0f);
	leftPalm->AddChild(leftLittleFinger);

	// right leg
	auto rightLeg = createTransfrom("rightLeg");
	auto rightUpperLeg = createBoxPart(20, 60, 20, gray, "rightUpperLeg");
	auto rightLowerLeg = createBoxPart(20, 60, 20, gray, "rightLowerLeg");

	rightLowerLeg->translate(-15, -55, 0);
	rightLowerLeg->rotate(-30, 0, 0, 1);

	rightUpperLeg->AddChild(rightLowerLeg);
	rightLeg->rotate(30, 0, 0, 1);

	rightLeg->translate(10, -70, 0);

	rightLeg->AddChild(rightUpperLeg);
	root->AddChild(rightLeg);


	// �����ҽ���
	auto rightFoot = createBoxPart(25, 10, 40, gray, "rightFoot"); // �ߴ��ʺϽ���
	rightFoot->translate(0, -35, 0); // ���������ʵ�λ��
	rightLowerLeg->AddChild(rightFoot);

	// left leg
	auto leftLeg = createTransfrom("leftLeg");
	auto leftUpperLeg = createBoxPart(20, 60, 20, gray, "leftUpperLeg");
	auto leftLowerLeg = createBoxPart(20, 60, 20, gray, "leftLowerLeg");

	leftLowerLeg->translate(15, -55, 0);
	leftLowerLeg->rotate(30, 0, 0, 1);

	leftUpperLeg->AddChild(leftLowerLeg);
	leftLeg->rotate(-30, 0, 0, 1);

	leftLeg->translate(-10, -70, 0);

	leftLeg->AddChild(leftUpperLeg);

	root->AddChild(leftLeg);

	// ���������
	auto leftFoot = createBoxPart(25, 10, 40, gray, "leftFoot");
	leftFoot->translate(0, -35, 0);
	leftLowerLeg->AddChild(leftFoot);

	AddNode(root);

	//// ���û���������ı任��������ת�ص�
	//std::shared_ptr<RobotBodyTransformParam> data = std::make_shared<RobotBodyTransformParam>();
	//std::shared_ptr<RobotBodyRotate> rc = std::make_shared<RobotBodyRotate>();
	//
	//root->setUserData(data);
	//root->SetUpdateCallback(rc);

	//// �����ֱۺ��ȵ���ת�����ͻص�
	//shared_ptr<RotateParam> leftParam = make_shared<RotateParam>();
	//shared_ptr<RotateParam> rightParam = make_shared< RotateParam>();
	//shared_ptr<RotateCallback> callback = make_shared<RotateCallback>();

	//rightParam->setMaxAngle(45);
	//rightParam->setAngle(45);
	//rightParam->setStep(-2);


	//leftArm->setUserData(leftParam);
	//leftArm->SetUpdateCallback(callback);

	//rightArm->setUserData(rightParam);
	//rightArm->SetUpdateCallback(callback);


	//leftLeg->setUserData(leftParam);
	//leftLeg->SetUpdateCallback(callback);

	//rightLeg->setUserData(rightParam);
	//rightLeg->SetUpdateCallback(callback);

	// ˢ����ͼ
	UpdateAllViews(NULL);
}

// CCG2022112453������Doc ����

void CCG2022112453������Doc::OnViewResize(int cx, int cy)
{
	//mScene->GetMainCamera()->viewport()->set(0, 0, cx, cy); 
	mScene->GetMainCamera()->viewport()->set(0, 0, cx, cy);
}

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

void CCG2022112453������Doc::OnButtonDraw3dSphere()
{
	using namespace std;
	MyDialog dialog;
	dialog.setDrawType(DrawType::SPHERE);
	if (dialog.DoModal() == IDOK)
	{
		glm::vec3 point;
		float radius = dialog.radius;
		int slice = dialog.slice;
		int stack = dialog.mstack;

		point.x = dialog.xpos;
		point.y = dialog.ypos;
		point.z = dialog.zpos;

		auto sphere = make_shared<CGSphere>();
		auto hints = make_shared< TessellationHints>();

		hints->setTargetSlices(slice);
		hints->setTargetStacks(stack);
		sphere->setRadius(radius);
		sphere->setTessellationHints(hints);
		sphere->setDisplayListEnabled(true);
		draw3D(sphere, point);
		UpdateAllViews(NULL);
	}
}

void CCG2022112453������Doc::OnButtonCube()
{
	using namespace std;
	MyDialog dialog;
	dialog.setDrawType(DrawType::CUBE);
	if (dialog.DoModal() == IDOK)
	{

		glm::vec3 point;
		float len = dialog.len;
		float width = dialog.width;
		float height = dialog.height;

		point.x = dialog.xpos;
		point.y = dialog.ypos;
		point.z = dialog.zpos;

		auto cube = make_shared<CGCube>(len, width, height);
		auto hints = make_shared< TessellationHints>();

		cube->setTessellationHints(hints);
		cube->setDisplayListEnabled(true);
		draw3D(cube, point);
		UpdateAllViews(NULL);
	}
}

void CCG2022112453������Doc::OnButtonTimer()
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
	if (view != nullptr) {
		mTimer = view->toggleFrameTimer();// ������ʱ�� 
	}
}

void CCG2022112453������Doc::OnUpdateButtonTimer(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mTimer != 0);
}

void CCG2022112453������Doc::OnButtonRobot()
{
	buildRobot();
	//auto tran1 = createBoxPart(100, 100, 100, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//mScene->GetSceneData()->asGroup()->AddChild(tran1);
	UpdateAllViews(NULL);
}

void CCG2022112453������Doc::OnButtonCameraControl()
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
	if (view == nullptr)
		return;
	auto window = view->glfwWindow();
	auto camera = mScene->GetMainCamera();
	UIEventHandler::SetCommand(new CGBasicCameraControl(window, camera)); //��������ֱ�߶ε��������
}

void CCG2022112453������Doc::OnUpdateButtonCameraControl(CCmdUI* pCmdUI)
{
	updateHandle(pCmdUI, EventType::CGBasicCameraControl);
}

void CCG2022112453������Doc::OnButtonArcballControl()
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
	if (view == nullptr)
		return;
	auto window = view->glfwWindow();
	auto camera = mScene->GetMainCamera();
	UIEventHandler::SetCommand(new CGArcballCameraControl(window, camera)); //��������ֱ�߶ε��������
}

void CCG2022112453������Doc::OnUpdateButtonArcballControl(CCmdUI* pCmdUI)
{
	updateHandle(pCmdUI, EventType::CGArcballCameraControl);
}
